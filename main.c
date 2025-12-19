#include "file_handler.h"
#include "student.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DATA_FILE "students.dat"

static void print_main_menu(void) {
    printf("\n==== Student Management System ====\n");
    printf("1. Add student\n");
    printf("2. Edit student\n");
    printf("3. Delete student\n");
    printf("4. Display all students\n");
    printf("5. Search by ID\n");
    printf("6. Search by name\n");
    printf("7. Filter by department\n");
    printf("8. Filter by GPA range\n");
    printf("9. Sort students\n");
    printf("10. Show average GPA\n");
    printf("11. Save and exit\n");
}

static void sort_menu(StudentList *list) {
    printf("\n-- Sorting Options --\n");
    printf("1. By ID\n");
    printf("2. By name\n");
    printf("3. By GPA (ascending)\n");
    printf("4. By GPA (descending)\n");

    int choice = prompt_int("Choose an option: ", 1, 4);
    switch (choice) {
        case 1:
            sort_students_by_id(list);
            break;
        case 2:
            sort_students_by_name(list);
            break;
        case 3:
            sort_students_by_gpa(list, true);
            break;
        case 4:
            sort_students_by_gpa(list, false);
            break;
        default:
            break;
    }
}

static Student prompt_student_details(const StudentList *list, int existing_id, bool allow_existing_id) {
    Student student;

    if (allow_existing_id) {
        student.id = prompt_int("Enter student ID: ", 1, 1000000000);
        while (id_exists(list, student.id) && student.id != existing_id) {
            printf("A student with this ID already exists. Please enter a different ID.\n");
            student.id = prompt_int("Enter student ID: ", 1, 1000000000);
        }
    } else {
        student.id = existing_id;
    }

    prompt_string("Enter full name: ", student.name, sizeof(student.name));
    student.age = prompt_int("Enter age: ", 1, 150);
    prompt_string("Enter department/major: ", student.department, sizeof(student.department));
    student.gpa = prompt_float("Enter GPA (0.0 - 4.0): ", 0.0f, 4.0f);

    return student;
}

static void add_student_flow(StudentList *list) {
    Student student = prompt_student_details(list, -1, true);
    if (add_student(list, student)) {
        printf("Student added successfully.\n");
    } else {
        printf("Failed to add student. ID may already exist.\n");
    }
}

static void edit_student_flow(StudentList *list) {
    int id = prompt_int("Enter ID of student to edit: ", 1, 1000000000);
    if (!id_exists(list, id)) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    Student updated = prompt_student_details(list, id, false);
    if (edit_student(list, id, updated)) {
        printf("Student updated successfully.\n");
    } else {
        printf("Failed to update student.\n");
    }
}

static void delete_student_flow(StudentList *list) {
    int id = prompt_int("Enter ID of student to delete: ", 1, 1000000000);
    if (delete_student(list, id)) {
        printf("Student deleted successfully.\n");
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

static void search_by_id_flow(const StudentList *list) {
    int id = prompt_int("Enter ID to search: ", 1, 1000000000);
    search_students_by_id(list, id);
}

static void search_by_name_flow(const StudentList *list) {
    char name[MAX_NAME_LENGTH];
    prompt_string("Enter name or part of name to search: ", name, sizeof(name));
    search_students_by_name(list, name);
}

static void filter_department_flow(const StudentList *list) {
    char department[MAX_DEPARTMENT_LENGTH];
    prompt_string("Enter department to filter: ", department, sizeof(department));
    filter_by_department(list, department);
}

static void filter_gpa_flow(const StudentList *list) {
    float min = prompt_float("Enter minimum GPA: ", 0.0f, 4.0f);
    float max = prompt_float("Enter maximum GPA: ", min, 4.0f);
    filter_by_gpa_range(list, min, max);
}

int main(void) {
    StudentList list;
    init_student_list(&list);

    if (load_students(DATA_FILE, &list)) {
        printf("Loaded %zu students from %s.\n", list.count, DATA_FILE);
    } else {
        printf("No existing data found. Starting with an empty list.\n");
    }

    int choice;
    bool running = true;
    while (running) {
        print_main_menu();
        choice = prompt_int("Choose an option: ", 1, 11);

        switch (choice) {
            case 1:
                add_student_flow(&list);
                break;
            case 2:
                edit_student_flow(&list);
                break;
            case 3:
                delete_student_flow(&list);
                break;
            case 4:
                display_students(&list);
                break;
            case 5:
                search_by_id_flow(&list);
                break;
            case 6:
                search_by_name_flow(&list);
                break;
            case 7:
                filter_department_flow(&list);
                break;
            case 8:
                filter_gpa_flow(&list);
                break;
            case 9:
                sort_menu(&list);
                break;
            case 10:
                printf("Average GPA: %.2f\n", average_gpa(&list));
                break;
            case 11:
                running = false;
                break;
            default:
                break;
        }
    }

    if (save_students(DATA_FILE, &list)) {
        printf("Data saved to %s.\n", DATA_FILE);
    } else {
        printf("Failed to save data to %s.\n", DATA_FILE);
    }

    free_student_list(&list);
    return 0;
}

#include "student.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static bool ensure_capacity(StudentList *list) {
    if (list->count < list->capacity) {
        return true;
    }
    size_t new_capacity = (list->capacity == 0) ? INITIAL_CAPACITY : list->capacity * 2;
    Student *new_data = realloc(list->data, new_capacity * sizeof(Student));
    if (!new_data) {
        return false;
    }
    list->data = new_data;
    list->capacity = new_capacity;
    return true;
}

void init_student_list(StudentList *list) {
    if (!list) {
        return;
    }
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

void free_student_list(StudentList *list) {
    if (!list) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

int find_student_index_by_id(const StudentList *list, int id) {
    if (!list) {
        return -1;
    }
    for (size_t i = 0; i < list->count; ++i) {
        if (list->data[i].id == id) {
            return (int)i;
        }
    }
    return -1;
}

Student *get_student_by_id(StudentList *list, int id) {
    int index = find_student_index_by_id(list, id);
    if (index < 0) {
        return NULL;
    }
    return &list->data[index];
}

bool id_exists(const StudentList *list, int id) {
    return find_student_index_by_id(list, id) != -1;
}

bool add_student(StudentList *list, Student student) {
    if (!list || id_exists(list, student.id)) {
        return false;
    }
    if (!ensure_capacity(list)) {
        return false;
    }
    list->data[list->count++] = student;
    return true;
}

bool edit_student(StudentList *list, int id, Student updated) {
    int index = find_student_index_by_id(list, id);
    if (index < 0) {
        return false;
    }
    // Preserve the original ID to maintain uniqueness
    updated.id = id;
    list->data[index] = updated;
    return true;
}

bool delete_student(StudentList *list, int id) {
    int index = find_student_index_by_id(list, id);
    if (index < 0) {
        return false;
    }
    for (size_t i = (size_t)index; i + 1 < list->count; ++i) {
        list->data[i] = list->data[i + 1];
    }
    list->count--;
    return true;
}

static void print_header(void) {
    printf("\n%-8s %-25s %-5s %-20s %-5s\n", "ID", "Name", "Age", "Department", "GPA");
    printf("--------------------------------------------------------------------------------\n");
}

void display_student(const Student *student) {
    if (!student) {
        return;
    }
    printf("%-8d %-25s %-5d %-20s %-5.2f\n", student->id, student->name, student->age,
           student->department, student->gpa);
}

void display_students(const StudentList *list) {
    if (!list || list->count == 0) {
        printf("No students to display.\n");
        return;
    }
    print_header();
    for (size_t i = 0; i < list->count; ++i) {
        display_student(&list->data[i]);
    }
}

void search_students_by_id(const StudentList *list, int id) {
    const Student *student = NULL;
    if (list) {
        int index = find_student_index_by_id(list, id);
        if (index >= 0) {
            student = &list->data[index];
        }
    }
    if (student) {
        print_header();
        display_student(student);
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

void search_students_by_name(const StudentList *list, const char *name) {
    if (!list || !name || list->count == 0) {
        printf("No matching students found.\n");
        return;
    }

    bool found = false;
    print_header();
    for (size_t i = 0; i < list->count; ++i) {
        if (contains_case_insensitive(list->data[i].name, name)) {
            display_student(&list->data[i]);
            found = true;
        }
    }
    if (!found) {
        printf("No matching students found.\n");
    }
}

void filter_by_department(const StudentList *list, const char *department) {
    if (!list || !department || list->count == 0) {
        printf("No matching students found.\n");
        return;
    }

    bool found = false;
    print_header();
    for (size_t i = 0; i < list->count; ++i) {
        if (case_insensitive_cmp(list->data[i].department, department) == 0) {
            display_student(&list->data[i]);
            found = true;
        }
    }
    if (!found) {
        printf("No matching students found.\n");
    }
}

void filter_by_gpa_range(const StudentList *list, float min, float max) {
    if (!list || list->count == 0) {
        printf("No students available.\n");
        return;
    }
    bool found = false;
    print_header();
    for (size_t i = 0; i < list->count; ++i) {
        if (list->data[i].gpa >= min && list->data[i].gpa <= max) {
            display_student(&list->data[i]);
            found = true;
        }
    }
    if (!found) {
        printf("No students found in GPA range %.2f - %.2f.\n", min, max);
    }
}

static int compare_by_id(const void *a, const void *b) {
    const Student *sa = a;
    const Student *sb = b;
    return (sa->id > sb->id) - (sa->id < sb->id);
}

static int compare_by_name(const void *a, const void *b) {
    const Student *sa = a;
    const Student *sb = b;
    int cmp = case_insensitive_cmp(sa->name, sb->name);
    if (cmp != 0) {
        return cmp;
    }
    return compare_by_id(a, b);
}

static int compare_by_gpa_asc(const void *a, const void *b) {
    const Student *sa = a;
    const Student *sb = b;
    if (sa->gpa < sb->gpa) return -1;
    if (sa->gpa > sb->gpa) return 1;
    return compare_by_name(a, b);
}

static int compare_by_gpa_desc(const void *a, const void *b) {
    return -compare_by_gpa_asc(a, b);
}

void sort_students_by_id(StudentList *list) {
    if (!list || list->count == 0) {
        printf("No students to sort.\n");
        return;
    }
    qsort(list->data, list->count, sizeof(Student), compare_by_id);
    printf("Students sorted by ID.\n");
}

void sort_students_by_name(StudentList *list) {
    if (!list || list->count == 0) {
        printf("No students to sort.\n");
        return;
    }
    qsort(list->data, list->count, sizeof(Student), compare_by_name);
    printf("Students sorted by name.\n");
}

void sort_students_by_gpa(StudentList *list, bool ascending) {
    if (!list || list->count == 0) {
        printf("No students to sort.\n");
        return;
    }
    qsort(list->data, list->count, sizeof(Student),
          ascending ? compare_by_gpa_asc : compare_by_gpa_desc);
    printf("Students sorted by GPA (%s).\n", ascending ? "ascending" : "descending");
}

float average_gpa(const StudentList *list) {
    if (!list || list->count == 0) {
        return 0.0f;
    }
    float total = 0.0f;
    for (size_t i = 0; i < list->count; ++i) {
        total += list->data[i].gpa;
    }
    return total / (float)list->count;
}

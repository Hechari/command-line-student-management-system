#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_NAME_LENGTH 100
#define MAX_DEPARTMENT_LENGTH 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char department[MAX_DEPARTMENT_LENGTH];
    float gpa;
} Student;

typedef struct {
    Student *data;
    size_t count;
    size_t capacity;
} StudentList;

void init_student_list(StudentList *list);
void free_student_list(StudentList *list);
bool add_student(StudentList *list, Student student);
bool edit_student(StudentList *list, int id, Student updated);
bool delete_student(StudentList *list, int id);
int find_student_index_by_id(const StudentList *list, int id);
Student *get_student_by_id(StudentList *list, int id);
void display_student(const Student *student);
void display_students(const StudentList *list);
void search_students_by_name(const StudentList *list, const char *name);
void search_students_by_id(const StudentList *list, int id);
void filter_by_department(const StudentList *list, const char *department);
void filter_by_gpa_range(const StudentList *list, float min, float max);
void sort_students_by_id(StudentList *list);
void sort_students_by_name(StudentList *list);
void sort_students_by_gpa(StudentList *list, bool ascending);
bool id_exists(const StudentList *list, int id);
float average_gpa(const StudentList *list);

#endif // STUDENT_H

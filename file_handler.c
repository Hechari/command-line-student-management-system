#include "file_handler.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER 512
#define DELIMITER "|"

static bool parse_student_line(const char *line, Student *student) {
    if (!line || !student) {
        return false;
    }

    char buffer[LINE_BUFFER];
    strncpy(buffer, line, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, DELIMITER);
    if (!token) return false;
    student->id = (int)strtol(token, NULL, 10);

    token = strtok(NULL, DELIMITER);
    if (!token) return false;
    strncpy(student->name, token, MAX_NAME_LENGTH);
    student->name[MAX_NAME_LENGTH - 1] = '\0';

    token = strtok(NULL, DELIMITER);
    if (!token) return false;
    student->age = (int)strtol(token, NULL, 10);

    token = strtok(NULL, DELIMITER);
    if (!token) return false;
    strncpy(student->department, token, MAX_DEPARTMENT_LENGTH);
    student->department[MAX_DEPARTMENT_LENGTH - 1] = '\0';

    token = strtok(NULL, DELIMITER);
    if (!token) return false;
    student->gpa = strtof(token, NULL);

    return true;
}

bool load_students(const char *filename, StudentList *list) {
    if (!filename || !list) {
        return false;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        return false;
    }

    char line[LINE_BUFFER];
    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);
        Student student;
        if (parse_student_line(line, &student)) {
            add_student(list, student);
        }
    }

    fclose(file);
    return true;
}

bool save_students(const char *filename, const StudentList *list) {
    if (!filename || !list) {
        return false;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        const Student *s = &list->data[i];
        fprintf(file, "%d|%s|%d|%s|%.2f\n", s->id, s->name, s->age, s->department, s->gpa);
    }

    fclose(file);
    return true;
}

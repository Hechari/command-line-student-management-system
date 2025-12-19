#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdbool.h>

#include "student.h"

bool load_students(const char *filename, StudentList *list);
bool save_students(const char *filename, const StudentList *list);

#endif // FILE_HANDLER_H

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>

void trim_newline(char *str);
void read_line(char *buffer, size_t size);
int case_insensitive_cmp(const char *a, const char *b);
bool contains_case_insensitive(const char *haystack, const char *needle);
void to_lower_inplace(char *str);
void clear_input_buffer(void);
int prompt_int(const char *message, int min, int max);
float prompt_float(const char *message, float min, float max);
void prompt_string(const char *message, char *buffer, size_t size);
bool prompt_yes_no(const char *message);

#endif // UTILS_H

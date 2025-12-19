#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_newline(char *str) {
    if (!str) {
        return;
    }
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        continue;
    }
}

void read_line(char *buffer, size_t size) {
    if (!buffer || size == 0) {
        return;
    }
    if (!fgets(buffer, (int)size, stdin)) {
        buffer[0] = '\0';
        return;
    }
    if (strchr(buffer, '\n') == NULL) {
        clear_input_buffer();
    }
    trim_newline(buffer);
}

int case_insensitive_cmp(const char *a, const char *b) {
    while (*a && *b) {
        int diff = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (diff != 0) {
            return diff;
        }
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

void to_lower_inplace(char *str) {
    if (!str) {
        return;
    }
    for (; *str; ++str) {
        *str = (char)tolower((unsigned char)*str);
    }
}

bool contains_case_insensitive(const char *haystack, const char *needle) {
    if (!haystack || !needle) {
        return false;
    }
    size_t hay_len = strlen(haystack);
    size_t needle_len = strlen(needle);
    if (needle_len == 0 || needle_len > hay_len) {
        return false;
    }

    for (size_t i = 0; i <= hay_len - needle_len; ++i) {
        size_t j = 0;
        while (j < needle_len && tolower((unsigned char)haystack[i + j]) ==
                                    tolower((unsigned char)needle[j])) {
            j++;
        }
        if (j == needle_len) {
            return true;
        }
    }
    return false;
}

int prompt_int(const char *message, int min, int max) {
    char buffer[128];
    int value;
    char *endptr;

    while (1) {
        printf("%s", message);
        read_line(buffer, sizeof(buffer));

        value = (int)strtol(buffer, &endptr, 10);
        if (endptr == buffer || *endptr != '\0') {
            printf("Invalid integer. Please try again.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }
        return value;
    }
}

float prompt_float(const char *message, float min, float max) {
    char buffer[128];
    float value;
    char *endptr;

    while (1) {
        printf("%s", message);
        read_line(buffer, sizeof(buffer));

        value = strtof(buffer, &endptr);
        if (endptr == buffer || *endptr != '\0') {
            printf("Invalid number. Please try again.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("Please enter a value between %.2f and %.2f.\n", min, max);
            continue;
        }
        return value;
    }
}

void prompt_string(const char *message, char *buffer, size_t size) {
    while (1) {
        printf("%s", message);
        read_line(buffer, size);
        if (strlen(buffer) == 0) {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        return;
    }
}

bool prompt_yes_no(const char *message) {
    char buffer[16];
    while (1) {
        printf("%s (y/n): ", message);
        read_line(buffer, sizeof(buffer));
        if (buffer[0] == 'y' || buffer[0] == 'Y') {
            return true;
        }
        if (buffer[0] == 'n' || buffer[0] == 'N') {
            return false;
        }
        printf("Please enter 'y' or 'n'.\n");
    }
}

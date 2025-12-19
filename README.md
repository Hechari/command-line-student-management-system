# Command-Line Student Management System

A modular C (C99) command-line application for managing student records with persistent storage.

## Features
- Add, edit, delete, and display students
- Search by ID or partial name
- Filter by department or GPA range
- Sort by ID, name, or GPA (ascending/descending)
- Average GPA summary
- Data saved/loaded from `students.dat`

## Build
Compile with GCC:

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c student.c file_handler.c utils.c -o sms
```

## Usage
Run the executable and follow the menu prompts:

```bash
./sms
```

Data is persisted between runs via `students.dat` in the working directory.

## Data Format
Records are stored as pipe-delimited lines: `id|name|age|department|gpa`.

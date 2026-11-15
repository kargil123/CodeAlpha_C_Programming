# Student Management System (C)

## Objective
A menu-driven application to add, display, search, update and delete student records. Records are stored in a binary file so they remain available after the program closes.

## Compile and run
```bash
gcc student_management.c -o student_management
./student_management
```
Windows PowerShell:
```powershell
gcc student_management.c -o student_management.exe
.\student_management.exe
```

## Features
1. Add a student with ID, name, age, department and mark.
2. Display all saved student records.
3. Search for a student by ID.
4. Update an existing student's details.
5. Delete a student record by ID.
6. Store records in `students.dat`.

## Concepts used
Structures, functions, binary file handling (`fopen`, `fread`, `fwrite`, `fseek`, `fclose`), strings, loops, conditions and menu-driven programming.

## Test checklist
- Add two students with different IDs.
- Display all records.
- Search for an existing ID and a non-existing ID.
- Update one student's details and display again.
- Delete one student and confirm it no longer appears.
- Close and reopen the application; confirm remaining records persist.

## Data file
The program creates `students.dat` in the current working directory. Do not delete this file if you want to keep the records. The file stores C structure records in binary format and is intended to be read by this program.

## Explanation
A `Student` structure groups each student's fields. Functions perform individual operations. The application reads and writes records in a binary data file. For deletion, it copies all records except the selected ID into a temporary file and then replaces the original file.

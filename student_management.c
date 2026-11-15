#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define TEMP_FILE "students_temp.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char department[40];
    float mark;
} Student;

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

void readLine(const char *prompt, char *buffer, size_t size)
{
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

int idExists(int id)
{
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;

    if (fp == NULL) return 0;

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addStudent(void)
{
    FILE *fp;
    Student s;

    printf("\n--- Add Student ---\n");
    printf("Enter student ID: ");
    if (scanf("%d", &s.id) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (idExists(s.id)) {
        printf("A student with this ID already exists.\n");
        return;
    }

    readLine("Enter name: ", s.name, sizeof(s.name));

    printf("Enter age: ");
    if (scanf("%d", &s.age) != 1 || s.age <= 0) {
        printf("Invalid age.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    readLine("Enter department: ", s.department, sizeof(s.department));

    printf("Enter mark (0-100): ");
    if (scanf("%f", &s.mark) != 1 || s.mark < 0 || s.mark > 100) {
        printf("Invalid mark.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        perror("Unable to open student file");
        return;
    }

    if (fwrite(&s, sizeof(Student), 1, fp) == 1)
        printf("Student record added successfully.\n");
    else
        printf("Error saving student record.\n");

    fclose(fp);
}

void displayStudents(void)
{
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    int count = 0;

    printf("\n--- Student Records ---\n");
    if (fp == NULL) {
        printf("No records found yet.\n");
        return;
    }

    printf("%-8s %-24s %-6s %-20s %-8s\n",
           "ID", "Name", "Age", "Department", "Mark");
    printf("---------------------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%-8d %-24s %-6d %-20s %-8.2f\n",
               s.id, s.name, s.age, s.department, s.mark);
        count++;
    }

    if (count == 0) printf("No records found.\n");
    fclose(fp);
}

void searchStudent(void)
{
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    int id, found = 0;

    printf("Enter student ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (fp == NULL) {
        printf("No student records available.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            printf("\nID: %d\nName: %s\nAge: %d\nDepartment: %s\nMark: %.2f\n",
                   s.id, s.name, s.age, s.department, s.mark);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student with ID %d was not found.\n", id);
    fclose(fp);
}

void updateStudent(void)
{
    FILE *fp = fopen(FILE_NAME, "r+b");
    Student s;
    int id, found = 0;

    printf("Enter student ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (fp == NULL) {
        printf("No student records available.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            printf("Updating record for %s.\n", s.name);
            readLine("Enter new name: ", s.name, sizeof(s.name));

            printf("Enter new age: ");
            if (scanf("%d", &s.age) != 1 || s.age <= 0) {
                printf("Invalid age. Update cancelled.\n");
                clearInputBuffer();
                fclose(fp);
                return;
            }
            clearInputBuffer();

            readLine("Enter new department: ", s.department, sizeof(s.department));

            printf("Enter new mark (0-100): ");
            if (scanf("%f", &s.mark) != 1 || s.mark < 0 || s.mark > 100) {
                printf("Invalid mark. Update cancelled.\n");
                clearInputBuffer();
                fclose(fp);
                return;
            }
            clearInputBuffer();

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            if (fwrite(&s, sizeof(Student), 1, fp) == 1)
                printf("Student record updated successfully.\n");
            else
                printf("Error updating record.\n");

            found = 1;
            break;
        }
    }

    if (!found) printf("Student with ID %d was not found.\n", id);
    fclose(fp);
}

void deleteStudent(void)
{
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen(TEMP_FILE, "wb");
    Student s;
    int id, found = 0;

    printf("Enter student ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clearInputBuffer();
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }
    clearInputBuffer();

    if (fp == NULL) {
        printf("No student records available.\n");
        if (temp) fclose(temp);
        remove(TEMP_FILE);
        return;
    }
    if (temp == NULL) {
        printf("Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        if (remove(FILE_NAME) == 0 && rename(TEMP_FILE, FILE_NAME) == 0)
            printf("Student record deleted successfully.\n");
        else
            printf("Could not replace the original data file. Keep %s as backup.\n", TEMP_FILE);
    } else {
        remove(TEMP_FILE);
        printf("Student with ID %d was not found.\n", id);
    }
}

int main(void)
{
    int choice;

    do {
        printf("\n====================================\n");
        printf("     STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid menu input. Exiting.\n");
            clearInputBuffer();
            break;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 0: printf("Exiting Student Management System.\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

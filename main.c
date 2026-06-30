#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
struct Student {
    int rollNo;
    char name[50];
    float marks;
};

// Function declarations
void addStudent();
void updateData();
void deleteStudent();
void searchStudent();
void generateReport();
void generateHTML();
void clearBuffer();

int main() {
    char password[20];
    char key;

    // Simple admin login
    printf("Enter Admin Password: ");
    scanf("%s", password);
    clearBuffer();

    if (strcmp(password, "admin123") != 0) {
        printf("Access Denied!\n");
        return 0;
    }

    // Main dashboard loop
    while (1) {
        printf("\n========================================");
        printf("\n      STUDENT MANAGEMENT SYSTEM");
        printf("\n========================================");
        printf("\n [A] - Add New Record");
        printf("\n [U] - Update Record");
        printf("\n [D] - Delete Record");
        printf("\n [S] - Search Student");
        printf("\n [R] - Analytics Report");
        printf("\n [W] - Refresh Website");
        printf("\n [E] - Exit");
        printf("\n----------------------------------------");
        printf("\nPress a key: ");

        scanf(" %c", &key);
        clearBuffer();

        switch (key) {
            case 'a':
            case 'A':
                addStudent();
                break;

            case 'u':
            case 'U':
                updateData();
                break;

            case 'd':
            case 'D':
                deleteStudent();
                break;

            case 's':
            case 'S':
                searchStudent();
                break;

            case 'r':
            case 'R':
                generateReport();
                break;

            case 'w':
            case 'W':
                generateHTML();
                break;

            case 'e':
            case 'E':
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid key!\n");
        }
    }

    return 0;
}

// Clears leftover input from keyboard buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Add new student record
void addStudent() {
    FILE *fp = fopen("students.dat", "ab+");
    struct Student s, temp;
    int exists = 0;

    printf("\n[ADD MODE]");
    printf("\nEnter Roll No: ");
    scanf("%d", &s.rollNo);
    clearBuffer();

    // Check if roll number already exists
    rewind(fp);
    while (fread(&temp, sizeof(struct Student), 1, fp)) {
        if (temp.rollNo == s.rollNo) {
            exists = 1;
            break;
        }
    }

    if (exists) {
        printf("Error: Roll number already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name);
    clearBuffer();

    // Validate marks
    do {
        printf("Enter Marks (0-100): ");
        scanf("%f", &s.marks);
        clearBuffer();

        if (s.marks < 0 || s.marks > 100)
            printf("Invalid marks! Try again.\n");

    } while (s.marks < 0 || s.marks > 100);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Record Saved Successfully!\n");
}


// Delete student record
void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct Student s;
    int roll;
    int found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n[DELETE MODE]");
    printf("\nEnter Roll No to delete: ");
    scanf("%d", &roll);
    clearBuffer();

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo != roll) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student not found!\n");
}


// Update student data
void updateData() {
    FILE *fp = fopen("students.dat", "rb+");

    struct Student s;
    int roll;
    int found = 0;
    char choice;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n[UPDATE MODE]");
    printf("\nEnter Roll No to update: ");
    scanf("%d", &roll);
    clearBuffer();

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {
            printf("Update [N]ame or [M]arks? ");
            scanf(" %c", &choice);
            clearBuffer();

            if (choice == 'n' || choice == 'N') {
                printf("Enter New Name: ");
                scanf(" %[^\n]s", s.name);
                clearBuffer();
            }
            else if (choice == 'm' || choice == 'M') {
                do {
                    printf("Enter New Marks (0-100): ");
                    scanf("%f", &s.marks);
                    clearBuffer();

                    if (s.marks < 0 || s.marks > 100)
                        printf("Invalid marks! Try again.\n");

                } while (s.marks < 0 || s.marks > 100);
            }
            else {
                printf("Invalid choice!\n");
                fclose(fp);
                return;
            }

            fseek(fp, -sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("Record Updated Successfully!\n");
    else
        printf("Student not found!\n");
}

// Search student by roll number
void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int roll;
    int found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n[SEARCH MODE]");
    printf("\nEnter Roll No: ");
    scanf("%d", &roll);
    clearBuffer();

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {
            printf("\nStudent Found");
            printf("\n----------------------");
            printf("\nRoll No : %d", s.rollNo);
            printf("\nName    : %s", s.name);
            printf("\nMarks   : %.2f", s.marks);
            printf("\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Student not found!\n");
}


// Generate analytics report
void generateReport() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    int totalStudents = 0;
    int passed = 0;
    int failed = 0;

    float totalMarks = 0;
    float highest = -1;
    char topper[50] = "N/A";

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        totalStudents++;
        totalMarks += s.marks;

        if (s.marks >= 40)
            passed++;
        else
            failed++;

        if (s.marks > highest) {
            highest = s.marks;
            strcpy(topper, s.name);
        }
    }

    fclose(fp);

    float average = 0;
    if (totalStudents > 0)
        average = totalMarks / totalStudents;

    printf("\n========== ANALYTICS REPORT ==========");
    printf("\nTotal Students : %d", totalStudents);
    printf("\nAverage Marks  : %.2f", average);
    printf("\nTopper         : %s (%.2f)", topper, highest);
    printf("\nPassed         : %d", passed);
    printf("\nFailed         : %d", failed);
    printf("\n======================================\n");
}


// Generate HTML dashboard
void generateHTML() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *web = fopen("index.html", "w");
    struct Student s;

    int totalStudents = 0;
    float totalMarks = 0;
    float highest = -1;
    char topper[50] = "N/A";

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        totalStudents++;
        totalMarks += s.marks;

        if (s.marks > highest) {
            highest = s.marks;
            strcpy(topper, s.name);
        }
    }

    float average = 0;
    if (totalStudents > 0)
        average = totalMarks / totalStudents;

    rewind(fp);

    fprintf(web, "<html><head><style>");
    fprintf(web, "body{font-family:Arial;background:#f4f7f6;text-align:center;margin:0;padding:20px;}");
    fprintf(web, ".card{display:inline-block;background:white;padding:20px;margin:10px;border-radius:10px;box-shadow:0 0 15px rgba(0,0,0,0.1);min-width:180px;}");
    fprintf(web, "table{width:85%%;margin:30px auto;border-collapse:collapse;background:white;box-shadow:0 0 20px rgba(0,0,0,0.1);}");
    fprintf(web, "th{background:#007bff;color:white;padding:15px;}");
    fprintf(web, "td{padding:12px;border-bottom:1px solid #ddd;}");
    fprintf(web, "</style></head><body>");

    fprintf(web, "<h1>Student Management Dashboard</h1>");

    fprintf(web, "<div class='card'><h3>Total Students</h3><p>%d</p></div>", totalStudents);
    fprintf(web, "<div class='card'><h3>Average Marks</h3><p>%.2f</p></div>", average);
    fprintf(web, "<div class='card'><h3>Topper</h3><p>%s</p></div>", topper);

    fprintf(web, "<table>");
    fprintf(web, "<tr><th>Roll No</th><th>Name</th><th>Marks</th></tr>");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        fprintf(
            web,
            "<tr><td>%d</td><td>%s</td><td>%.2f%%</td></tr>",
            s.rollNo,
            s.name,
            s.marks
        );
    }

    fprintf(web, "</table>");
    fprintf(web, "<p>Database Status: Active</p>");
    fprintf(web, "</body></html>");

    fclose(fp);
    fclose(web);

    printf("\n[SYNC] Dashboard updated successfully!\n");
}
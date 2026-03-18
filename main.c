
/*A secure, keyboard-driven Administrative System 
built in C that manages persistent student records 
using binary file I/O and random-access memory 
navigation. Key features include a password-protected
login, robust input validation, and an automated generator
that synchronizes terminal data with a styled HTML/CSS web dashboard.*/

#include <stdio.h>   // For standard input and output like printf and scanf
#include <stdlib.h>  // For system-level functions like exit()
#include <string.h>  // For string functions like strcmp (comparing text)

// Creating a structure: This acts like a digital 'container' for student info
struct Student {
    int rollNo;      // Integer variable to store the Roll ID
    char name[50];   // Character array to store the Name (up to 50 letters)
    float marks;     // Float variable to store marks with decimal points
};

// Function Prototypes: Telling the compiler these functions exist later in the code
void addStudent();
void updateData();
void deleteStudent();
void generateHTML();
void clearBuffer(); 

int main() {
    char password[20]; // Character array to hold the password input
    char key;          // Character variable to hold the menu key (A, U, D, etc.)

    // --- SECURITY LOGIN ---
    printf("Enter Admin Password: "); // Asking the user for the password
    scanf("%s", password);           // Reading the text typed by the user
    clearBuffer();                   // Cleaning the keyboard memory after input

    // Comparing user input to the secret string "admin123"
    if (strcmp(password, "admin123") != 0) { 
        printf("Access Denied!\n");   // If they don't match, print error
        return 0;                     // Stop the program completely
    }

    // --- MAIN INTERFACE LOOP ---
    while (1) { // 1 means 'True', so this menu keeps repeating
        printf("\n===================================="); // Visual border
        printf("\n   KEYBOARD CONTROLLED DASHBOARD");      // Title
        printf("\n===================================="); // Visual border
        printf("\n [A] - Add New Record");               // Option A
        printf("\n [U] - Update Marks/Name");             // Option U
        printf("\n [D] - Delete a Record");               // Option D
        printf("\n [W] - Refresh Website (Web)");         // Option W
        printf("\n [E] - Exit System");                   // Option E
        printf("\n------------------------------------"); // Visual border
        printf("\nPRESS A KEY: ");                        // Instruction

        scanf(" %c", &key); // Reading the key (the space before %c is a pro trick to skip white space)
        clearBuffer();      // Emptying the input buffer to prevent errors

        // Switch case handles the keys (handles both Small and Capital letters)
        switch (key) {
            case 'a': case 'A': addStudent(); break;      // Jump to Add function
            case 'u': case 'U': updateData(); break;      // Jump to Update function
            case 'd': case 'D': deleteStudent(); break;   // Jump to Delete function
            case 'w': case 'W': generateHTML(); break;    // Jump to HTML function
            case 'e': case 'E': 
                printf("Exiting...\n");                   // Print exit message
                exit(0);                                  // Close program
            default: 
                printf("Error: Key '%c' not valid.\n", key); // Handle wrong keys
        }
    }
    return 0; // Return 0 to indicate successful run
}

// Function to clean the "Input Buffer" (prevents infinite loops and skips)
void clearBuffer() {
    int c; // Temporary integer to hold characters
    // Keep reading every character in the buffer until we hit 'Enter' (\n) or the end
    while ((c = getchar()) != '\n' && c != EOF); 
}

// Function to Add a Record
void addStudent() {
    // fopen opens 'students.dat'. 'ab' means Append Binary (adds data to the end)
    FILE *fp = fopen("students.dat", "ab"); 
    struct Student s; // Create a temporary variable 's' of type Student

    printf("\n[ADD MODE]");                       // Title for this mode
    printf("\nEnter Roll No: "); scanf("%d", &s.rollNo); // Save input to rollNo
    clearBuffer();                                // Clear 'Enter' key from buffer

    printf("Enter Name: "); scanf(" %[^\n]s", s.name); // Read name including spaces
    clearBuffer();                                      // Clear 'Enter' key from buffer

    // VALIDATION LOOP: Makes sure the user doesn't enter impossible marks
    do {
        printf("Enter Marks (0-100): ");          // Ask for marks
        scanf("%f", &s.marks);                    // Read marks
        clearBuffer();                            // Clear buffer
        if (s.marks < 0 || s.marks > 100) printf("Error: Invalid Marks!\n");
    } while (s.marks < 0 || s.marks > 100);       // Repeat if marks are wrong

    fwrite(&s, sizeof(struct Student), 1, fp);    // Write the whole 's' block into the file
    fclose(fp);                                   // Close file to save it
    printf("Record Saved!\n");                    // Success message
}

// Function to Delete a Record
void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");   // Open existing file for reading
    FILE *temp = fopen("temp.dat", "wb");    // Create a new empty temporary file
    struct Student s;                         // Temp student variable
    int roll, found = 0;                      // Search variable and flag

    if (fp == NULL) { printf("No file found!\n"); return; } // Check if file exists

    printf("\n[DELETE MODE]");                // Title
    printf("\nRoll No to delete: "); scanf("%d", &roll); // Get target Roll No
    clearBuffer();                            // Clear buffer

    // Read every record from the old file
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo != roll) {               // If this is NOT the student to delete...
            fwrite(&s, sizeof(struct Student), 1, temp); // ...copy them to the temp file
        } else {
            found = 1;                        // If it IS the student, skip them (delete)
        }
    }

    fclose(fp);                               // Close original file
    fclose(temp);                             // Close temp file
    remove("students.dat");                   // Delete the old file
    rename("temp.dat", "students.dat");        // Rename the new 'clean' file to the original name

    if (found) printf("Student Deleted.\n");   // Print result
    else printf("Not Found.\n");
}

// Function to Update Record
void updateData() {
    // 'rb+' opens the file for both reading and writing (overwriting)
    FILE *fp = fopen("students.dat", "rb+"); 
    struct Student s;                        // Temp student variable
    int roll, found = 0;                     // Search variables
    char subKey;                             // For choosing Name or Marks update

    if (fp == NULL) return;                  // Error check

    printf("\n[UPDATE MODE]");               // Title
    printf("\nRoll No to update: "); scanf("%d", &roll); // Get roll no
    clearBuffer();                           // Clear buffer

    // Searching through the file
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {              // If we find a match...
            printf("Update [N]ame or [M]arks? "); // Ask what to change
            scanf(" %c", &subKey);           // Read choice key
            clearBuffer();                   // Clear buffer

            if (subKey == 'n' || subKey == 'N') { // If user wants to change Name
                printf("New Name: "); scanf(" %[^\n]s", s.name);
            } else {                             // If user wants to change Marks
                printf("New Marks: "); scanf("%f", &s.marks);
            }

            // fseek moves the 'file cursor' back so we overwrite the specific record
            fseek(fp, -sizeof(struct Student), SEEK_CUR); 
            fwrite(&s, sizeof(struct Student), 1, fp); // Write updated info
            found = 1;                       // Mark as found
            break;                           // Stop looking
        }
    }
    fclose(fp);                              // Close file
    if(found) printf("Record Updated!\n");   // Final message
    else printf("Not Found.\n");
}

// Function to generate the Web Dashboard
void generateHTML() {
    FILE *fp = fopen("students.dat", "rb");  // Open binary data file
    FILE *web = fopen("index.html", "w");    // Create the HTML website file
    struct Student s;                        // Temp variable

    if (fp == NULL) return;                  // Error check

    // Writing HTML and CSS code directly into the index.html file
    fprintf(web, "<html><head><style>");     // Start of HTML
    fprintf(web, "body { font-family: Arial; background: #f4f7f6; text-align: center; }"); // CSS Body
    fprintf(web, "table { width: 80%%; margin: 40px auto; border-collapse: collapse; background: white; box-shadow: 0 0 20px rgba(0,0,0,0.1); }"); // CSS Table
    fprintf(web, "th { background: #007bff; color: white; padding: 15px; }"); // CSS Header
    fprintf(web, "td { padding: 12px; border-bottom: 1px solid #ddd; }"); // CSS Rows
    fprintf(web, "</style></head><body>");    // End of Style, start of Body
    fprintf(web, "<h1>Student Management Dashboard</h1>"); // Title
    fprintf(web, "<table><tr><th>Roll No</th><th>Full Name</th><th>Marks</th></tr>"); // Table Headers

    // Loop through every student in the file and write a table row for each
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        fprintf(web, "<tr><td>%d</td><td>%s</td><td>%.2f%%</td></tr>", s.rollNo, s.name, s.marks);
    }

    fprintf(web, "</table><p>Database Status: Active</p></body></html>"); // End tags
    fclose(fp);                              // Close database
    fclose(web);                             // Close website file
    printf("\n[SYNC] Website updated successfully!\n"); // Success message
}
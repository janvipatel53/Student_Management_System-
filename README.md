# Student Record Management System

A menu-driven Student Record Management System built in C for managing academic records using binary file storage. The application supports secure admin login, student record management, persistent data storage, and automatic generation of an analytics dashboard for performance visualization.

---

## Features

- Admin authentication for secure access
- Add new student records
- View all student records
- Search student records by roll number
- Update existing student records
- Delete student records
- Persistent binary file storage
- Automatic analytics dashboard generation
- Student performance insights and statistics

---

## Technical Features

This project uses core C programming concepts and file handling techniques to efficiently manage student data.

- **Binary File Storage**  
  Student records are stored in `students.dat` using `fwrite()` and `fread()` for persistent storage.

- **Random Access Record Updates**  
  Uses `fseek()` to directly modify specific records without rewriting the entire file.

- **CRUD Operations**  
  Supports Create, Read, Update, and Delete operations for complete student record management.

- **Analytics Dashboard**  
  Automatically generates an `index.html` dashboard using HTML/CSS to visualize student records and performance statistics.

- **Menu-Driven Interface**  
  Provides a keyboard-based console interface for easy navigation and interaction.

- **Input Validation & Security**  
  Includes admin password authentication and validation for fields such as marks and roll number.

---

## Dashboard Insights

The generated dashboard displays:

- Total number of students
- Average marks
- Class topper
- Pass / Fail statistics
- Complete student records table

---

## Tech Stack

- **Language:** C
- **File Handling:** `fread`, `fwrite`, `fseek`
- **Frontend Dashboard:** HTML, CSS
- **Compiler:** GCC / MinGW

---

## Project Structure

```bash
StudentSystem/
│
├── main.c
├── students.dat
├── index.html
├── README.md
└── LICENSE
```

---

## How to Run

### Compile

```bash
gcc main.c -o student_system
```

### Run

#### Linux / macOS
```bash
./student_system
```

#### Windows (PowerShell / CMD)
```bash
.\student_system.exe
```

---

## Sample Workflow

1. Login using admin password  
2. Add student records  
3. Search / update / delete records  
4. Generate dashboard  
5. Open `index.html` in browser to view analytics  

---

## Concepts Used

- Structures in C
- File Handling
- Binary Storage
- Dynamic Record Updates
- Data Validation
- HTML Report Generation

---

## License

This project is licensed under the MIT License.

---

## Author

**Janvi Patel**  
Electrical Engineering, IIT Ropar  

GitHub: https://github.com/janvipatel53
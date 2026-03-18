## Technical Features

This project implements a file-based Student Management System in C with the following features:

* Binary File Storage (File I/O)
  Uses `fwrite` and `fread` to store records in `students.dat` for persistent data storage.

* Random Access File Editing
  Uses `fseek` to directly update specific records without rewriting the entire file.

* Web Dashboard Generation
  Generates an `index.html` file with basic CSS to display student data.

* Keyboard-Based Control
  Menu-driven interface using keys (A, U, D, W, E).

* Input Handling
  Uses `clearBuffer()` to handle input issues.

* Basic Security and Validation
  Includes password check and validation for marks input.

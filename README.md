# 🎓 Student Management System — C++

A console-based **Student Management System** built in C++ that efficiently manages student records using **file handling** and **menu-driven operations**. All data is stored persistently in a local `.dat` file so records survive between sessions.

---

## 📋 Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Usage](#usage)
- [File Storage Format](#file-storage-format)
- [Input Validation](#input-validation)
- [Future Improvements](#future-improvements)

---

## ✨ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Add Student** | Register a new student with ID, name, age, course, and GPA |
| 2 | **Display All Students** | View all records in a formatted table |
| 3 | **Search by ID** | Instantly look up a student using their unique ID |
| 4 | **Update Record** | Edit any field of an existing student record |
| 5 | **Delete Record** | Remove a student record with confirmation prompt |
| 6 | **Rank by GPA** | View all students sorted from highest to lowest GPA |
| 7 | **Total Count** | Display the total number of registered students |
| 8 | **Persistent Storage** | All data is saved to `students.dat` using file I/O |

---

## 📁 Project Structure

```
student-management-system/
│
├── student_management.cpp   # Main source file (all logic)
├── students.dat             # Auto-generated data file (created on first run)
└── README.md                # Project documentation
```

> `students.dat` is created automatically when you add your first student. You do not need to create it manually.

---

## 📖 Usage

On launch, you will see the main menu:

```
============================================================
       STUDENT MANAGEMENT SYSTEM
============================================================
  1. Add Student
  2. Display All Students
  3. Search Student by ID
  4. Update Student Record
  5. Delete Student Record
  6. View Students Ranked by GPA
  7. Total Student Count
  0. Exit
============================================================
  Enter your choice:
```

Enter the number corresponding to the action you want to perform and follow the on-screen prompts.

---

## 💾 File Storage Format

Records are stored in `students.dat` as plain CSV (one student per line):

```
id,name,age,course,gpa
```

**Example:**
```
101,Tuntun Chauhan,20,Computer Science,3.85
102,Bindiya Soolanki,21,Electronics,3.60

```

This format is human-readable and can be backed up or transferred easily.

---

## ✅ Input Validation

The system validates all inputs before saving:

- **Student ID** — must be a positive integer and unique
- **Age** — must be between 1 and 149
- **GPA** — must be between 0.0 and 4.0
- **Update fields** — pressing Enter keeps the existing value unchanged
- **Delete confirmation** — asks `(y/n)` before permanently removing a record
- **Invalid input recovery** — bad inputs are caught and the user is re-prompted

---

## 🔮 Future Improvements

- [ ] Search students by name or course
- [ ] Export records to CSV or PDF
- [ ] Filter students by GPA range
- [ ] Add login/authentication for admin access
- [ ] Support for multiple courses per student
- [ ] GUI version using Qt or a web front-end

---

## 👨‍💻 Author

**Meenakshi T.S**
- GitHub: [@nul-lhypothesis](https://github.com/nul-lhypothesis)
- Email: mee879183@gmail.com

---



# Course Management System (C++ - OOP Console Project)

A simple **console-based Course Management System** built in C++ using Object-Oriented Programming (OOP) principles.

## Features

- User roles:
    - **Student**
    - **Instructor**
    - **Teaching Assistant (TA)**
    - **Admin**
- **Login System** for authentication (username + password)
- **Student Features:**
    - View available courses
    - Enroll in courses
    - View enrolled courses and their lessons
- **Course Structure:**
    - Each course contains multiple lessons
- **Admin Feature:**
    - Reset user passwords
- Fully applies OOP concepts:
    - Classes and Objects
    - Constructors
    - Encapsulation (`private`, `protected`)
    - Inheritance & Multiple Inheritance
    - Polymorphism (Overriding, Overloading)
    - Virtual Functions
    - Friend Functions & Friend Classes

## UML Class Diagram

```uml
+------------------+
|      User        |
+------------------+
| - username: str  |
| - password: str  |
| - name: str      |
+------------------+
| +login(u, p):bool|
| +displayProfile():void |
| +getRole():str   |
+------------------+
         ^
         |
  -----------------------
  |         |           |
+---------+ +-------------+ +------------------+
| Student | | Instructor  | |      Admin       |
+---------+ +-------------+ +------------------+
| - enrolledCourses: list|
| +enroll(course): void  |
| +viewCourses(): void   |
+------------------------+

+----------------------+
|      Course          |
+----------------------+
| - courseID: str      |
| - title: str         |
| - lessons: list      |
+----------------------+
| +addLesson(title, content): void |
| +displayCourse(): void           |
+----------------------+

+----------------------+
|      Lesson          |
+----------------------+
| - lessonTitle: str   |
| - content: str       |
+----------------------+
| +displayLesson(): void |
+----------------------+

```

## How to Run

1. Clone the repository or download the files.
2. Compile the `main.cpp` using a C++ compiler (e.g., g++, Code::Blocks, Visual Studio).
   ```bash
   g++ -o course_mgmt main.cpp
   ./course_mgmt

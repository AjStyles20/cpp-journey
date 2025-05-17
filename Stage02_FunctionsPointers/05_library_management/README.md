# 05_LibraryManagementSystem

## Project Description
This project demonstrates a complete Library Management System implemented in C++ using object-oriented principles. The system allows users to manage books, library members, and borrowing operations through a console interface.

## Learning Objectives
- Understand namespace organization in multi-file projects
- Learn proper data encapsulation techniques
- Practice exception handling and input validation
- Implement CRUD operations for library resources
- Develop skills in managing borrowing/returning workflows

## Technologies Used
- **C++17** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal
- **CMake** (optional for build automation)

## How to Run
1. Open the terminal in the project directory
2. Compile the program using:
   ```bash
   g++ -std=c++17 src/*.cpp -Iinclude -o LibrarySystem
   ```
3. Run the compiled executable:
   - Windows:
     ```bash
     .\LibrarySystem.exe
     ```
   - Unix-based systems:
     ```bash
     ./LibrarySystem
     ```

## How to Use
1. Run the program
2. Use the menu to select operations:
   - Add/View Books (Options 1-2)
   - Register/View Users (Options 3-4)
   - Borrow/Return Books (Options 5-6)
   - View Borrowed Books (Option 7)
3. Follow on-screen prompts for each operation

## Example Output
```
=== Library Management System ===
1. Add Book
2. Display All Books
3. Register User
4. Display All Users
5. Borrow Book
6. Return Book
7. Display Borrowed Books
0. Exit
Enter your choice: 1

Enter book title: Effective Modern C++
Enter author: Scott Meyers
Enter ISBN: 9781491903995
Book added successfully!
```

## Key Concepts Demonstrated
- Namespace organization (`Library` namespace)
- Data encapsulation (private vectors with accessors)
- Exception handling (custom exception classes)
- Move semantics for efficient string handling
- STL containers (vector, map)
- Const-correctness throughout

## Notes
- The system uses in-memory storage (vectors/maps)
- ISBN serves as unique identifier for books
- User ID must be unique for member registration
- Comprehensive input validation prevents common errors
- Error messages guide users through correct usage

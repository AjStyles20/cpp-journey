# 03_Person

## Project Description
This project demonstrates inheritance in C++ by creating a base `Person` class and deriving `Student` and `Teacher` classes from it. The implementation shows how derived classes can extend base class functionality while maintaining proper encapsulation through access specifiers.

## Learning Objectives
- Understand inheritance and class hierarchies in C++
- Implement base and derived class relationships
- Properly use access specifiers (public, protected, private)
- Extend functionality in derived classes
- Practice object-oriented design principles

## Technologies Used
- **C++17** (GNU g++ or compatible)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension
- **CMake** (optional for project building)

## How to Run
1. Open terminal in the project directory
2. Compile the program using:
   ```bash
   g++ main.cpp -o Person
   ```
3. Run the compiled executable:
   - Windows:
     ```bash
     .\Person.exe
     ```
   - Linux/Mac:
     ```bash
     ./Person
     ```

## How to Use
1. The program demonstrates inheritance through pre-defined examples
2. No user input is required - it automatically shows:
   - Base Person class functionality
   - Student class with added features
   - Teacher class with specialized methods
3. Examine the code to understand the inheritance structure

## Example Output
```
Person: Alice (Age: 25)
Student: Bob (Age: 20) | Grade: B
Teacher: Carol (Age: 35) | Subject: Mathematics
Bob is studying hard...
Carol is teaching Mathematics...
```

## Key Concepts Demonstrated
- Public inheritance with `class Student : public Person`
- Protected member access in derived classes
- Base class constructor initialization
- Extended functionality in derived classes
- Clean object-oriented design patterns

## Notes
- The base class uses protected members for derived class access
- All classes maintain proper encapsulation
- Demonstrates single inheritance (can be extended to multiple)
- Includes constructor initialization lists
- No dynamic memory allocation used (simple value types)

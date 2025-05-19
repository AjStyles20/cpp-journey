# 01_BookClassImplementation

## Project Description
This project demonstrates a complete Book class implementation in C++ with constructors, copy operations, and display functionality. The program showcases object-oriented programming principles through book object creation and manipulation.

## Learning Objectives
- Understand class definition and member variables
- Implement different types of constructors (default, parameterized, copy)
- Practice using the `this` pointer
- Learn proper copy assignment implementation
- Develop object display methods

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory
2. Compile the program using:
   ```bash
   g++ book_class.cpp -o BookProgram
   ```
3. Run the compiled executable:
   - Windows:
     ```bash
     .\BookProgram.exe
     ```
   - Unix-based systems:
     ```bash
     ./BookProgram
     ```

## How to Use
1. Run the program
2. The program will demonstrate:
   - Default constructor usage
   - Parameterized constructor initialization
   - Copy constructor operation
   - Assignment operator functionality
3. Each book's details will be displayed automatically

## Example Output
```
Book 1:
Title: 
Author: 
Year: 0

Book 2:
Title: C++ How to Program  An Objects
Author: Paul J. Deitel and Harvey M. Deitel
Year: 2023

Book 3 (copy of Book 2):
Title: C++ How to Program  An Objects
Author: Paul J. Deitel and Harvey M. Deitel
Year: 2023

Book 4 (assigned from Book 1):
Title: 
Author: 
Year: 0
```

## Key Concepts Demonstrated
- Class definition with private members
- Default and parameterized constructors
- Copy constructor implementation
- Assignment operator overloading
- Const-correct member functions
- Object display method

## Notes
- The implementation follows the Rule of Three (constructors + copy operations)
- Display method is marked const for safety
- Includes proper null checks in assignment operator
- Can be extended with dynamic memory management for more complex scenarios

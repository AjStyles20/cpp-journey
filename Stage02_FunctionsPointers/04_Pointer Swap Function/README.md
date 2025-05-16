# 04_PointerSwapFunction

## Project Description
This project demonstrates how to swap two integers using pointers in C++. The program takes two integer inputs from the user, displays their original values, swaps them using a pointer-based function, and then displays the swapped values.

## Learning Objectives
- Understand how to use pointers to modify variables in functions
- Learn pass-by-reference using pointers in C++
- Practice pointer dereferencing and memory address manipulation
- Develop skills in basic input/output operations in C++

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory
2. Compile the program using:
   ```bash
   g++ pointer_swap.cpp -o PointerSwap
   ```
3. Run the compiled executable:
   - Windows:
     ```bash
     .\PointerSwap.exe
     ```
   - Unix-based systems:
     ```bash
     ./PointerSwap
     ```

## How to Use
1. Run the program
2. Enter two integer values when prompted (separated by space)
3. The program will display:
   - Original values before swapping
   - Swapped values after the operation

## Example Output
```
        Enter the value for a & b: 15 30

        Before swapping the values, a = 15 and b = 30

        After swapping, a = 30 and b = 15
```

## Key Concepts Demonstrated
- Pointer declaration and dereferencing (`*` operator)
- Address-of operator (`&`) usage
- Function parameter passing by reference using pointers
- Temporary variable usage in value swapping

## Notes
- The program uses fundamental pointer operations to achieve value swapping
- The swapping function modifies the original variables rather than working on copies
- For extended functionality, consider adding input validation
- The same concept can be extended to swap other data types or complex objects

# 06_BubbleSortImplementation

## Project Description
This project demonstrates the bubble sort algorithm in C++ using dynamic memory allocation. The program takes user input for an array of numbers, displays the original array, sorts it using bubble sort, and then displays the sorted array.

## Learning Objectives
- Understand dynamic memory allocation with `new` and `delete[]`
- Implement the bubble sort algorithm
- Practice array manipulation using pointers
- Develop skills in formatted input/output operations
- Learn to pass arrays to functions in C++

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory
2. Compile the program using:
   ```bash
   g++ main.cpp -o ArrayAlgorithm
   ```
3. Run the compiled executable:
   - Windows:
     ```bash
     .\ArrayAlgorithm.exe
     ```
   - Unix-based systems:
     ```bash
     ./ArrayAlgorithm
     ```

## How to Use
1. Run the program
2. Enter the number of elements you want to sort
3. Input each number when prompted
4. The program will display:
   - Original array in `[x, y, z]` format
   - Sorted array in `[a, b, c]` format

## Example Output
```
How many numbers would you like to enter? 4
Enter number 1: 3.5
Enter number 2: 1.2
Enter number 3: 4.7
Enter number 4: 2.1
You entered: [3.5, 1.2, 4.7, 2.1]
Your sorted elements: [1.2, 2.1, 3.5, 4.7]
```

## Key Concepts Demonstrated
- Dynamic array allocation with `new[]` and `delete[]`
- Bubble sort algorithm implementation
- Array passing to functions
- Pointer-based array access
- Formatted console output

## Notes
- The program demonstrates classic bubble sort with O(n²) complexity
- Includes swap optimization for early termination
- Handles any valid double-precision numbers
- Remember to always pair `new[]` with `delete[]` to prevent memory leaks

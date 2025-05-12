# 09_PatternGen

## Project Description
This project generates a pyramid pattern of stars (`*`) based on the number of rows specified by the user. The program uses nested loops to create a visually appealing pyramid structure.

## Learning Objectives
- Understand the use of nested loops in C++.
- Learn how to manipulate spaces and characters to create patterns.
- Practice taking user input and dynamically generating output.

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory.
2. Compile the program using the following command:
   ```bash
   g++ main.cpp -o PatternGen
   ```
3. Run the compiled executable:
   - For Windows:
     ```bash
     .\PatternGen.exe
     ```
   - For Unix-based systems:
     ```bash
     ./PatternGen
     ```

## How to Use
1. Run the program.
2. Enter the number of rows for the pyramid when prompted.
3. The program will generate a pyramid pattern of stars (`*`) with the specified number of rows.

## Example Output
```
Enter number of rows: 5
    *
   ***
  *****
 *******
*********
```

## Notes
- The program uses nested `for` loops to handle spaces and stars for each row.
- The number of stars in each row follows the formula `2 * i - 1`, where `i` is the current row number.
- The program is beginner-friendly and demonstrates basic concepts of loops and formatting in C++.
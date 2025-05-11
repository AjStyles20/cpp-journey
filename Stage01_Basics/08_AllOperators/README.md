# 08_AllOperators

## Project Description
This project demonstrates the use of various operators in C++ by performing operations on two user-provided integers. The program covers arithmetic, relational, logical, and assignment operators, as well as increment and decrement operations.

## Learning Objectives
- Understand and apply different types of operators in C++.
- Learn how to take user input and display results using `cin` and `cout`.
- Practice using logical and relational operators for decision-making.
- Explore increment and decrement operations.

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory.
2. Compile the program using the following command:
   ```bash
   g++ main.cpp -o AllOperators
   ```
3. Run the compiled executable:
   - For Windows:
     ```bash
     .\AllOperators.exe
     ```
   - For Unix-based systems:
     ```bash
     ./AllOperators
     ```

## How to Use
1. Run the program.
2. Enter two integers when prompted.
3. The program will display:
   - Results of arithmetic operations (`+`, `-`, `*`, `/`, `%`).
   - Results of relational comparisons (`==`, `!=`, `>`, `<`).
   - Results of logical operations (`&&`, `||`, `!`).
   - Demonstrations of assignment and increment/decrement operations.

## Example Output
```
Enter first integers(Number): 10
Enter second integers(Number): 5
You entered: 10 and 5

Arithmetic Operators:
Input1 + Input2 = 15
Input1 - Input2 = 5
Input1 * Input2 = 50
Input1 / Input2 = 2
Input1 % Input2 = 0

Relational Operators:
Input1 == Input2: 0
Input1 != Input2: 1
Input1 > Input2: 1
Input1 < Input2: 0

Logical Operators:
Input1 > 0 && Input2 > 0: 1
Input1 < 0 || Input2 > 0: 1
!(Input1 < 0): 1

Assignment and Increment/Decrement:
Input1 += 2: 12
Input1++: 13
--Input2: 4
```

## Notes
- Ensure that the second integer is not zero to avoid division by zero errors.
- The program uses basic C++ syntax and is beginner-friendly.
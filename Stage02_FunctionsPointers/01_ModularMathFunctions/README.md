# 01_ModularMathFunctions

## Project Description
This project demonstrates three different approaches to calculate the factorial of a number in C++:
1. Using a `while` loop.
2. Using a `for` loop.
3. Using a modular function.

The code showcases how to implement factorial calculations in a modular and reusable way, as well as through basic iterative loops.

## Learning Objectives
- Understand the concept of factorials and how to compute them programmatically.
- Learn how to use `while` and `for` loops for iterative calculations.
- Explore modular programming by implementing a reusable function for factorial computation.

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory.
2. Compile the program using the following command:
   ```bash
   g++ main.cpp -o ModularMathFunctions
   ```
3. Run the compiled executable:
   - For Windows:
     ```bash
     .\ModularMathFunctions.exe
     ```
   - For Unix-based systems:
     ```bash
     ./ModularMathFunctions
     ```

## How to Use
1. Run the program.
2. Enter a positive integer when prompted.
3. The program will calculate and display the factorial of the entered number using the selected approach.

## Code Features
### 1. Factorial Using `while` Loop
- Computes the factorial by decrementing the input number in a `while` loop.
- Example:
  ```
  Enter your number: 5
  120
  ```

### 2. Factorial Using `for` Loop
- Computes the factorial by iterating from 1 to the input number in a `for` loop.
- Example:
  ```
  Enter your number: 4
  24
  ```

### 3. Factorial Using a Function
- Implements a reusable function `factorial(int x)` to compute the factorial.
- Example:
  ```
  Enter your number: 6
  720
  ```

## Example Output
```
Enter your number: 5
120
```

## Notes
- Ensure the input is a positive integer. Negative numbers or non-integer inputs are not handled in this implementation.
- The modular function approach is recommended for better code reusability and readability.
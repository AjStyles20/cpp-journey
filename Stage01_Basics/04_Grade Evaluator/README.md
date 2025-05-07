# GradeEvaluatorProject

## Project Description
A simple C++ program that calculates grades based on user input, such as scores or percentages, and evaluates the results using predefined grading criteria (e.g., A for 90-100, B for 80-89, etc.). The program then prints the corresponding grade to the terminal.

## Learning Objectives
- [x] Understand basic C++ syntax, some arithmetic operations and conditional statements.
- [x] Use `iostream`, `std::cout`, `string` and conditional statements like if, else_if and switch. 
- [x] Compile and execute from the terminal or use the "Run" button in Visual Studio Code. Ensure you have the correct compiler installed (e.g., MinGW for Windows) before setting up C++ in VS Code. See [this beginner-friendly guide](https://code.visualstudio.com/docs/cpp/config-mingw), which explains how to install a compiler, configure VS Code, and run C++ programs.

## Technologies Used
- C++ (GNU g++)  
- Visual Studio Code  
  - C/C++ extension by Microsoft  
  - Integrated terminal  

## How to Run
```bash
# Option 1: Name the executable
g++ <source_file>.cpp -o GradeEvaluator
# For Unix-based systems
./GradeEvaluator
# For Windows users
.\GradeEvaluator.exe

.\a.exe
g++ main.cpp  # This will create an executable named 'a.out' on Unix-based systems or 'a.exe' on Windows by default.
./a          # For Unix-based systems
.\a.exe      # For Windows users

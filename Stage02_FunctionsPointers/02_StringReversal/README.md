# 02_StringReversal

## Project Description
This project demonstrates how to reverse strings in C++ using the `std::reverse` function from the `<algorithm>` library. The program reverses a predefined string and then allows the user to input their own string, which is also reversed and displayed.

## Learning Objectives
- Learn how to use the `std::reverse` function to manipulate strings.
- Understand basic string handling and input/output in C++.
- Practice working with the `string` class and iterators.

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory.
2. Compile the program using the following command:
   ```bash
   g++ main.cpp -o StringReversal
   ```
3. Run the compiled executable:
   - For Windows:
     ```bash
     .\StringReversal.exe
     ```
   - For Unix-based systems:
     ```bash
     ./StringReversal
     ```

## How to Use
1. Run the program.
2. The program will display a reversed version of a predefined string.
3. Enter your own string when prompted.
4. The program will reverse and display your input string.

## Example Output
```
!!!!hah hA .ytirepsorp dna ecarg fo dnal eht ni devil ,eutriv fo nam a mA
Now, Your turn!!
Hello
olleH
```

## Notes
- The program uses `std::reverse`, which operates on iterators, to reverse the strings.
- Ensure that the input string does not contain spaces, as `cin` will only capture input up to the first space. To handle multi-word input, consider using `std::getline`.

#03_Dynamic Array

## Project Description
This project demonstrates fundamental concepts of array manipulation and user input in C++. It includes two main parts:

1.  **(Commented Out) Sum of User-Defined Array:** A basic example of getting the size of a one-dimensional array from the user, populating it with user-entered numbers, and calculating their sum.

2.  **Dynamically Allocated 2D Array:** The core of the program focuses on creating and managing a two-dimensional array (or "table") whose dimensions are determined by the user at runtime. It covers dynamic memory allocation, user input to fill the array, and manual memory deallocation.

## Learning Objectives
- Understand how to get user input to determine the size and elements of arrays.
- Learn about the differences between fixed-size arrays (including Variable Length Arrays) and dynamically allocated arrays.
- Practice dynamic memory allocation for 2D arrays using `new` and `delete`.
- Understand the importance of manual memory management in C++.
- Learn how to iterate through array elements for input and processing.

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
    - C/C++ extension by Microsoft
    - Integrated terminal

## How to Run
1. Open the terminal in the project directory.
2. Compile the program using the following command:
   ```bash
   g++ main.cpp -o ArrayInteraction
````

3.  Run the compiled executable:
      - For Windows:
        ```bash
        .\ArrayInteraction.exe
        ```
      - For Unix-based systems:
        ```bash
        ./ArrayInteraction
        ```

## How to Use

1.  Run the program.
2.  The program will first ask you to enter the number of rows and columns for a two-dimensional array.
3.  Enter the desired dimensions.
4.  You will then be prompted to enter the value for each element of the array, row by row.
5.  After you have entered all the elements, the program will ask if you want to delete the dynamically allocated memory for the array (Enter 'Y' or 'N').
6.  Based on your input, the program will either deallocate the memory and confirm the deletion or indicate that the table remains active.

## Example Output

```
Enter your number of rows: 2
Enter your number of cols: 3
Enter the elements of the 2x3 table:
Enter element at row 1, column 1: 1
Enter element at row 1, column 2: 2
Enter element at row 1, column 3: 3
Enter element at row 2, column 1: 4
Enter element at row 2, column 2: 5
Enter element at row 2, column 3: 6
Do you want to delete your table/array(Enter Y/N) ?: Y
Your table/array was successfully deleted!
```

## Notes

  - The commented-out section demonstrates a simple 1D array example using a Variable Length Array (VLA), which might not be standard C++ on all compilers.
  - The main part of the program uses dynamic memory allocation (`new`) for the 2D array. It's crucial to understand that memory allocated with `new` must be explicitly deallocated with `delete[]` to avoid memory leaks. This program demonstrates this deallocation process.
  - The program includes basic input validation for the dimensions to ensure they are not negative or zero.
  - In a real-world scenario, you might want to implement more robust error handling for user input.
  - For more convenient and safer dynamic array management in C++, consider using `std::vector` (for 1D arrays) and `std::vector<std::vector<T>>` (for 2D arrays), as they handle memory management automatically.


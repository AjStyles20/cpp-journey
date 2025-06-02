# 01_MedianCalculator

## Project Description
This program calculates the median of a set of integers entered by the user. It demonstrates input handling, sorting algorithms, and statistical calculations in C++ with robust error handling.

## Learning Objectives
- Handle user input with validation
- Implement sorting algorithms
- Calculate statistical medians
- Practice exception handling
- Work with STL vectors and algorithms

## Technologies Used
- **C++11** (or later)
- **STL algorithms** for sorting
- **Exception handling** for error cases
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o MedianCalculator
   ```
2. Run the executable:
   ```bash
   ./MedianCalculator    # Linux/Mac
   .\MedianCalculator.exe # Windows
   ```

## Usage Instructions
1. The program will prompt you to enter integers
2. Enter numbers one at a time
3. Press Enter after each number
4. To finish input, enter any non-number character
5. The program will display:
   - Sorted list of numbers
   - Calculated median value

## Example Usage
```
Enter integers (enter any non-number to finish):
5
2
8
3
x

Sorted numbers: 2 3 5 8 
Median: 4
```

## Key Features
- Robust input handling
- Automatic sorting of values
- Correct median calculation for both:
  - Odd number of elements (middle value)
  - Even number of elements (average of two middle values)
- Clean console output
- Comprehensive error handling

## Error Handling
The program detects and handles:
- Empty input sets
- Non-numeric input (to terminate entry)
- Potential calculation errors

## Mathematical Background
For a sorted set of numbers:
- Odd count median: `middle element`
- Even count median: `(element[n/2 - 1] + element[n/2]) / 2`

## Notes
- Requires C++11 or later
- Input terminates on any non-integer entry
- Maintains original precision in calculations

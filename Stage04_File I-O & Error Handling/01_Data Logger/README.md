# 01_DataLogger

## Project Description
This program reads numbers from an input file, calculates basic statistics (sum and average), and writes the results to an output file. It demonstrates robust file handling and error checking in C++.

## Learning Objectives
- Implement file input/output operations
- Handle file errors and edge cases
- Process numerical data from files
- Use standard algorithms for calculations
- Work with the filesystem library

## Technologies Used
- **C++17** (required for `std::filesystem` operations)
- **<fstream>** for file operations
- **<numeric>** for accumulation
- **<filesystem>** for path checking
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Create an `input.txt` file with numbers (one per line)
2. Compile the program (ensure `g++` is installed and available in your PATH):
   ```bash
   g++ main.cpp -o DataLogger
   ```
3. Run the executable:
   ```bash
   ./DataLogger      # Linux/Mac (uses forward slash `/`)
   .\DataLogger.exe  # Windows (uses backslash `\`)
   ```
4. Results will be saved to `output.txt`

## File Requirements
- `input.txt` must:
  - Exist in the same directory
  - Contain at least one valid number (either an integer or a floating-point number)
  - Have one number per line
- `output.txt` will be created automatically

## Example Usage
1. `input.txt` contents:
   ```
   10.5
   20.3
   15.2
   ```
2. Program output:
   ```
   Successfully processed 3 numbers. Results written to output.txt
   ```
3. `output.txt` contents:
   ```
   Statistics Report
   ================
   Numbers processed: 3
   Sum: 46
   Average: 15.3333

   Note: The formatting (e.g., decimal places) is customizable in the code. See the `formatOutput` function in `main.cpp`.
   ```

## Key Features
- Comprehensive error checking:
  - Input file existence
  - File open success
  - Valid number content
  - Output file creation
- Efficient number processing
- Clean output formatting

## Error Handling
The program checks for and reports:
- Missing input file
- Unreadable input file
- Empty/non-numeric input
- Output file creation failures
- Ensure C++17 or later is installed. Check your version with `g++ --version` and update if necessary.
## Notes
- Requires C++17 or later for filesystem features
- Handles both integers and floating-point numbers


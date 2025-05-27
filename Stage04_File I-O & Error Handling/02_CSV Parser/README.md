# 02_CSV Parser

## Project Description
This program reads and parses a CSV file containing student records (Student ID, Last Name, First Name, Age, Phone Number, GPA) into structured data. It demonstrates file handling, string parsing, and structured data processing in C++.

## Learning Objectives
- Read and process CSV files in C++
- Implement custom data structures for records
- Parse strings with string streams
- Handle file I/O operations
- Manage errors and exceptions

## Technologies Used
- **C++11** (or later)
- **<fstream>** for file operations
- **<sstream>** for string parsing
- **<vector>** for dynamic data storage
- **Visual Studio Code**
  - C/C++ extension by Microsoft

## How to Run
1. Create a `Student_Record.csv` file with this format:
   ```
   StudentID,LastName,FirstName,Age,PhoneNumber,GPA
   0001,Noah,Mark,20,003246892,3.5
   ```
2. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o CSV_Parser
   ```
3. Run the executable:
   ```bash
   ./CSV_Parser    # Linux/Mac
   .\CSV_Parser.exe # Windows
   ```

## File Requirements
- `Student_Record.csv` must:
  - Be in the same directory as the executable
  - Have a header row (StudentID,LastName,FirstName,Age,PhoneNumber,GPA)
  - Contain exactly 6 comma-separated fields per line
  - Have age as a valid integer and GPA as a valid number

## Example Usage
1. `Student_Record.csv` contents:
   ```
   StudentID,LastName,FirstName,Age,PhoneNumber,GPA
    0001,Noah,Mark,20,003246892,3.5
   ```
2. Program output:
   ```
     Student ID: 0001
  First Name: Mark
   Last Name: Noah
Phone Number: 003246892
         Age: 20
         GPA: 3

   ```

## Key Features
- CSV parsing with string streams
- Structured data representation for student records
- Automatic header skipping
- Comprehensive error handling

## Error Handling
The program handles:
- Missing or unreadable files
- Malformed CSV records
- Invalid age or GPA values
- Missing fields

## Structure Diagram
```text
StudentRecord Structure
├── Id (string)
├── FirstName (string)
├── LastName (string)
├── PhoneNumber (string)
├── Age (int)
├── Gpa (double)
└── display() (prints formatted info)
```

## Notes
- The first line is always treated as a header and skipped.
- Fields must be comma-separated.
- Can be extended with:
  - Writing modified data back to CSV
  - Additional data validation
  - Command-line filename specification
  - Support for quoted fields

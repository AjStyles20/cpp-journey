# 03_AdvancedCSVProcessor

## Project Description
This program provides robust CSV file processing with comprehensive error handling, reading person records (name, age, occupation), displaying them, and generating statistical reports. It demonstrates professional-grade file operations and data validation in C++.

## Learning Objectives
- Implement advanced CSV parsing with validation
- Handle multiple exception types
- Create statistical reports from structured data
- Develop interactive file processing
- Practice defensive programming techniques

## Technologies Used
- **C++11** (or later)
- **<fstream>** for file operations
- **<sstream>** for string parsing
- **<stdexcept>** for exception handling
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o CSVProcessor
   ```
2. Run the executable:
   ```bash
   ./CSVProcessor    # Linux/Mac
   .\CSVProcessor.exe # Windows
   ```
3. When prompted:
   - Enter input CSV filename (e.g., `people.csv`)
   - Enter output filename for statistics (e.g., `stats.txt`)

## File Format Requirements
Input CSV must:
- Have header row (Name,Age,Occupation)
- Contain exactly 3 comma-separated fields per line
- Have valid ages (positive integers)
- Not contain empty lines between records

Example `people.csv`:
```
Name,Age,Occupation
Alice,28,Doctor
Bob,35,Architect
```

## Example Usage
```
Enter input CSV filename: people.csv
Enter output filename: stats.txt

Successfully processed 2 records:
Name: Alice, Age: 28, Occupation: Doctor
Name: Bob, Age: 35, Occupation: Architect
Statistics written to stats.txt
```

Generated `stats.txt`:
```
Statistics Report
Total records: 2
Average age: 31.5
```

## Key Features
- Comprehensive field validation:
  - Name presence check
  - Age validity (positive integers)
  - Occupation presence check
- Detailed error reporting:
  - File access errors
  - Parsing errors with line numbers
  - Data validation errors
- Statistical calculations:
  - Record count
  - Average age calculation
- Interactive filename input

## Error Handling
The program detects and reports:
- Missing or unreadable files
- Invalid CSV formatting
- Negative or non-numeric ages
- Missing fields
- Empty input files
- Output file creation failures

## Data Flow
```text
CSV File → readCSVFile() → [Person objects] → 
1. Display records
2. writeStatistics() → Report File
```

## Notes
- Requires C++11 or later
- Maintains line numbers for error reporting
- Preserves original data precision

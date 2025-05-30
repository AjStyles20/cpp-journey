# 05_ErrorLoggingDataProcessor

## Project Description
This program demonstrates a robust file processing system with comprehensive error logging. It reads numbers from files, validates them, calculates averages, and maintains detailed error logs with timestamps. The implementation showcases professional error handling patterns in C++.

## Learning Objectives
- Implement a logging system with timestamping
- Practice defensive file processing
- Create reusable error handling components
- Develop validation for numeric data
- Build interactive console applications

## Technologies Used
- **C++11** (or later)
- **<ctime>** for timestamp generation
- **<iomanip>** for time formatting
- **Error logging** with file and console output
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o DataProcessor
   ```
2. Run the executable:
   ```bash
   ./DataProcessor    # Linux/Mac
   .\DataProcessor.exe # Windows
   ```
3. Interactive commands:
   - Enter filename to process
   - Type 'quit' to exit

## File Requirements
Input files should:
- Contain one number per line
- Have positive integers only
- Can be any text filename

Example valid `numbers.txt`:
```
42
15
37
```

## Example Usage
```
File Processing System (enter filenames, 'quit' to exit)
Enter filename: numbers.txt
Successfully processed 3 numbers from numbers.txt
Average: 31.3333
Enter filename: invalid.txt
[2023-11-15 14:30:45] ERROR: Invalid number format at line 3: abc
Enter filename: quit
```

## Key Components
### ErrorLogger Class
- Timestamps all entries
- Logs to both file and console
- Handles critical vs regular errors
- Automatic file management

### DataProcessor Class
- Validates input numbers
- Handles file operations
- Reports detailed line errors
- Returns processed data

## Error Handling
The system detects and logs:
- Missing/unreadable files
- Invalid number formats
- Negative numbers
- Empty lines
- Number range issues
- Critical system errors

## Log File Format
`error_log.txt` contains:
```
[YYYY-MM-DD HH:MM:SS] TYPE: message
```
Where TYPE is either ERROR or CRITICAL

## Notes
- Requires C++11 or later
- Creates/updates `error_log.txt` automatically
- Can be extended with:
  - Custom log levels (WARNING, INFO)
  - Log rotation
  - Email/SMS alerts for critical errors
  - Support for floating-point numbers
  - Multi-threaded processing

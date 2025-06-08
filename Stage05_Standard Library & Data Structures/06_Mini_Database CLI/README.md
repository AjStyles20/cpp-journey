# 06_GradeManagementSystem

## Project Description
A C++ program that manages student grades using STL map for efficient data storage and retrieval. The system allows adding, removing, and viewing student records with automatic grade-to-remark conversion.

## Learning Objectives
- Implement CRUD operations with map
- Handle structured student data
- Format console output professionally
- Manage user input with validation
- Automate remark generation

## Technologies Used
- **C++11** (or later)
- **STL map** for student database
- **<iomanip>** for formatted output
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o GradeManager
   ```
2. Run the executable:
   ```bash
   ./GradeManager    # Linux/Mac
   .\GradeManager.exe # Windows
   ```

## Features
- **Add Students**: Store ID, name, grade (auto-generates remarks)
- **Remove Students**: Delete by ID
- **Lookup Students**: View individual records
- **Display All**: Show all records in formatted table
- **Automatic Remarks**: 
  - 90+: Excellent
  - 80-89: Good
  - 70-79: Average
  - Below 70: Needs Improvement

## Usage Instructions
1. Run the program
2. Use menu to select operations:
   ```
   1. Add Student
   2. Remove Student
   3. Lookup Student
   4. Display All
   5. Exit
   ```
3. Follow prompts for each operation

## Example Session
```
Enter student ID: 101
Enter student name: Alice Johnson
Enter student grade (0-100): 92
Added student: ID 101 - Alice Johnson

Student Record:
ID: 101
Name: Alice Johnson
Grade: 92.00
Remarks: Excellent
```

## Data Structure
```cpp
map<int, StudentRecord> database
├── Key: Student ID (int)
└── Value: StudentRecord struct containing:
   ├── name (string)
   ├── grade (double)  
   └── remarks (string)
```

## Key Concepts
- **Map Operations**: insert, erase, find, iteration
- **Structured Data**: Using structs with maps
- **Input Validation**: Clearing buffer, numeric checks
- **Output Formatting**: Fixed precision, column alignment

## Notes
- Requires C++11 or later
- ID-based operations (case-sensitive)
- Maintains sorted order by student ID

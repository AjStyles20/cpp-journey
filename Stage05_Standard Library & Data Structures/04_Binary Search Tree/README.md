# 04_PhonebookApplication

## Project Description
This C++ program implements a phonebook manager using STL map to store and manage contacts. It provides basic CRUD (Create, Read, Update, Delete) operations for contact management with a console-based interface.

## Learning Objectives
- Implement CRUD operations with map data structure
- Handle user input with validation
- Manage ordered data storage
- Format console output professionally
- Develop menu-driven applications

## Technologies Used
- **C++11** (or later)
- **STL map** for contact storage
- **<iomanip>** for formatted output
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o Phonebook
   ```
2. Run the executable:
   ```bash
   ./Phonebook    # Linux/Mac
   .\Phonebook.exe # Windows
   ```

## Features
- **Add Contact**: Store name and phone number
- **Find Contact**: Search by name
- **Delete Contact**: Remove by name
- **List Contacts**: View all entries in formatted table
- **Update Existing**: Automatically updates if name exists

## Usage Instructions
1. Run the program
2. Use the menu to select operations:
   ```
   1. Add Contact
   2. Find Contact
   3. Delete Contact
   4. List All Contacts
   5. Exit
   ```
3. Follow prompts for each operation

## Example Session
```
Phonebook Menu:
1. Add Contact
2. Find Contact
3. Delete Contact
4. List All Contacts
5. Exit
Enter your choice: 1
Enter name: John Doe
Enter phone number: 555-1234
Contact saved: John Doe - 555-1234

Phonebook Contacts:
NAME                PHONE NUMBER
----------------------------------------
John Doe            555-1234
```

## Key Concepts
- **Map Operations**: insert, find, erase, iteration
- **Input Handling**: getline with cin.ignore
- **Output Formatting**: setw, left alignment
- **Error Handling**: Contact existence checks

## Data Structure
```text
std::map<string, string> contacts
├── Key: Contact name (string)
└── Value: Phone number (string)
```

## Notes
- Requires C++11 or later
- Names are case-sensitive
- Maintains alphabetical ordering

# 03_StackQueueSimulator

## Project Description
This program demonstrates fundamental data structures through two interactive simulations:
1. **Text Editor** with undo  functionality (Stack implementation)
2. **Printer Queue** management system (Queue implementation)

## Learning Objectives
- Understand stack LIFO (Last-In-First-Out) behavior
- Understand queue FIFO (First-In-First-Out) behavior
- Implement stack-based undo functionality
- Manage job queues in order processing
- Develop interactive console applications

## Technologies Used
- **C++11** (or later)
- **STL stack** for editor undo history
- **STL queue** for print job management
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o DataStructures
   ```
2. Run the executable:
   ```bash
   ./DataStructures    # Linux/Mac
   .\DataStructures.exe # Windows
   ```

## Simulation 1: Text Editor (Stack)
### Commands:
- `[text]` : Type normally
- `undo` : Undo last change
- `exit` : Return to main menu

### Features:
- Maintains document state history
- Unlimited undo levels (until initial state)
- Real-time document display

### Example Session:
```
Typed: "Hello"
Current document: "Hello"
Typed: " World"
Current document: "Hello World"
undo performed. Current content:
Current document: "Hello"
```

## Simulation 2: Printer Queue (Queue)
### Commands:
- `add [document]` : Add print job
- `print` : Process next job
- `queue` : Show current queue
- `exit` : Return to main menu

### Features:
- First-come-first-served processing
- Queue status display
- Job count tracking

### Example Session:
```
Added to queue: "Resume.pdf"
Added to queue: "Report.doc"
Current printer queue (2 jobs):
1. Resume.pdf
2. Report.doc
Printing: "Resume.pdf"
```

## Key Concepts Demonstrated
| Concept          | Text Editor | Printer Queue |
|------------------|-------------|---------------|
| Data Structure   | Stack       | Queue         |
| Insert Operation | push()      | push()        |
| Remove Operation | pop()       | pop()         |
| Access Operation | top()       | front()       |
| Principle        | LIFO        | FIFO          |

## Implementation Notes
- Built with C++11 standard
- Console-based user interface
- Error handling for invalid inputs
- Memory-efficient data structure usage
- Cross-platform compatibility
- Modular code structure with separate simulation handlers

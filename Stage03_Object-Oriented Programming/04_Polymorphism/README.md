# 04_Polymorphism

## Project Description
This project demonstrates inheritance and runtime polymorphism in C++ through a `Person` base class with `Student` and `Teacher` derived classes. The implementation showcases virtual functions, method overriding, and polymorphic behavior using base class pointers.

## Learning Objectives
- Understand inheritance hierarchies and protected members
- Implement virtual functions for polymorphic behavior
- Practice method overriding with the `override` keyword
- Use base class pointers to derived objects
- Learn proper memory management with dynamic allocation

## Technologies Used
- **C++11** (or later) for override keyword
- **Virtual functions** for runtime polymorphism
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o Polymorphism
   ```
2. Run the executable:
   ```bash
   ./Polymorphism    # Linux/Mac
   .\Polymorphism.exe # Windows
   ```

## How to Use
1. The program automatically demonstrates:
   - Base `Person` class functionality
   - `Student` class with grade information
   - `Teacher` class with subject specialization
   - Polymorphic behavior through virtual functions
2. No user input required - all examples are pre-configured

## Example Output
```
Person: Alice (Age: 25)
Student: Bob (Age: 20, Grade: A)
Teacher: Carol (Age: 35, Subject: Math)
```

## Key Concepts Demonstrated
- Public inheritance (`class Student : public Person`)
- Virtual function declaration and overriding
- Runtime polymorphism through base class pointers
- Protected member access in derived classes
- Proper cleanup with `delete` for dynamic objects



## Notes
- `describe()` is declared `virtual` for polymorphic behavior
- Derived classes use `override` for explicit method overriding
- Demonstrates proper use of `new`/`delete` for dynamic objects
- Uncomment the pure virtual function to make `Person` abstract
- Can be extended with:
  - Multiple inheritance
  - Smart pointers for automatic memory management
  - Additional derived classes

# 05_Vector2DClass

## Project Description
This project demonstrates operator overloading in C++ through a `Vector2D` class that represents 2D vectors. The implementation showcases vector addition and stream output through overloaded operators while maintaining proper encapsulation.

## Learning Objectives
- Implement operator overloading (`+` and `<<`)
- Understand friend functions for stream operations
- Practice class encapsulation with private members
- Create constructor with default parameters
- Work with const-correct member functions

## Technologies Used
- **C++11** (or later)
- **Operator overloading** for natural vector operations
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ main.cpp -o VectorClass
   ```
2. Run the executable:
   ```bash
   ./VectorClass    # Linux/Mac
   .\VectorClass.exe # Windows
   ```

## How to Use
1. The program demonstrates:
   - Vector creation with x,y coordinates
   - Vector addition using `+` operator
   - Vector output using `<<` operator
2. No user input required - example vectors are pre-configured

## Example Output
```
v1: (1, 2)
v2: (3, 4)
v1 + v2: (4, 6)
```

## Key Concepts Demonstrated
- Operator overloading (`operator+` and `operator<<`)
- Friend function for stream insertion
- Constructor with default parameters
- Const-correct member functions
- Proper encapsulation with private members

## Class Interface

class Vector2D {
private:
    double x, y;
public:
    Vector2D(double x = 0, double y = 0);  // Constructor
    Vector2D operator+(const Vector2D&) const;  // Addition
    friend std::ostream& operator<<(std::ostream&, const Vector2D&);  // Output
};
```

## Notes
- The `operator+` is implemented as a member function
- The `operator<<` is implemented as a friend function
- Default constructor parameters allow `Vector2D()` and `Vector2D(x,y)`
- Can be extended with:
  - Additional operators (`-`, `*`, `+=`, etc.)
  - Vector magnitude/normalization methods
  - Dot/cross product calculations
  - Comparison operators


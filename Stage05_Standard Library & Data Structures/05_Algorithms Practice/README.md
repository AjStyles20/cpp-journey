# 05_STLAlgorithmDemo

## Project Description
This program demonstrates various C++ STL algorithms through string manipulation operations on a collection of words. It showcases function objects, function pointers, and lambda expressions with different STL algorithm use cases.

## Learning Objectives
- Understand STL algorithm applications
- Implement function objects (functors)
- Use function pointers with algorithms
- Write lambda expressions for custom operations
- Practice common algorithm patterns (transform, find, count)

## Technologies Used
- **C++11** (or later)
- **STL algorithms**: transform, find_if, count_if, for_each
- **Function objects and lambdas**
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Code Runner extension

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o AlgorithmDemo
   ```
2. Run the executable:
   ```bash
   ./AlgorithmDemo    # Linux/Mac
   .\AlgorithmDemo.exe # Windows
   ```

## Demonstration Features
1. **Uppercase Conversion**  
   Uses a function object (`Capitalize` struct) with `transform`

2. **Lowercase Conversion**  
   Uses a function pointer (`toLower`) with `transform`

3. **Finding Elements**  
   Uses lambda with `find_if` to locate first 5-letter word

4. **Counting Elements**  
   Uses lambda with `count_if` to count words starting with 'a/A'

5. **Element Processing**  
   Uses lambda with `for_each` to print formatted output

## Example Output
```
All uppercase:
APPLE BANANA CHERRY DATE EGGPLANT 

All lowercase:
apple banana cherry date eggplant 

First word with length 5: apple

1 words start with 'a' or 'A'

Modified words:
• apple
• banana
• cherry
• date
• eggplant
```

## Key Concepts Demonstrated
| Algorithm | Technique Used | Purpose |
|-----------|----------------|---------|
| `transform` | Function object | Case conversion |
| `transform` | Function pointer | Case conversion |
| `find_if` | Lambda expression | Finding elements |
| `count_if` | Lambda expression | Counting elements |
| `for_each` | Lambda expression | Element processing |

## Code Structure
```text
1. Capitalize functor (struct)
2. toLower function
3. Main program with:
   - Initial word list
   - 5 algorithm demonstrations
   - Various callable techniques
```

## Notes
- Requires C++11 or later
- Demonstrates multiple ways to use algorithms
- Clear separation of concerns

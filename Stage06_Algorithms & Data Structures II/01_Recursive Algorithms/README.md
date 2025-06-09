# 01_Recursive Algorithms

## Project Description
This project demonstrates classic recursive algorithms and dynamic programming (memoization) in C++. It includes:
1. Fibonacci sequence calculation (naive and memoized)
2. Directory tree size computation (recursive traversal)
3. Factorial calculation (with memoization)

## Learning Objectives
- Understand the difference between naive recursion and memoization
- Implement memoization using STL containers
- Analyze time complexity improvements
- Apply recursion to tree-like data structures
- Measure execution time with `<chrono>`

## Technologies Used
- **C++11** (or later)
- **STL Containers**: `unordered_map`, `vector`
- **<chrono>** for timing
- **Visual Studio Code** (with C/C++ extension)

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o RecursionExamples
   ```
2. Run the executable:
   ```bash
   ./RecursionExamples    # Linux/Mac
   .\RecursionExamples.exe # Windows
   ```

## Features

### 1. Fibonacci Sequence
- **Naive Recursive**: Exponential time (O(2^n))
- **Memoized Version**: Linear time (O(n)) using `unordered_map`
- **Performance Comparison**: Timed execution for various n

### 2. Directory Size Calculation
- **Recursive Tree Traversal**: Computes total size of a directory and all subdirectories
- **Example Structure**:
  ```
  Root (1000 KB)
  ├── Documents (500 KB)
  │   ├── Work (300 KB)
  │   └── Personal (200 KB)
  └── Pictures (1500 KB)
      ├── Vacation (800 KB)
      └── Family (700 KB)
  ```

### 3. Factorial Calculation
- **Memoized Implementation**: Caches results to avoid redundant calculations
- **Demonstration**: Computes factorials up to 20!

## Example Output
```
Fibonacci Sequence:
fib(5) = 5 (computed in 12 μs)
fib(10) = 55 (computed in 3 μs)
fib(20) = 6765 (computed in 5 μs)
fib(30) = 832040 (computed in 8 μs)
fib(40) = 102334155 (computed in 10 μs)

Directory Tree Size: 4000 KB

Factorial with Memoization:
5! = 120
10! = 3628800
15! = 1307674368000
20! = 2432902008176640000
```

## Data Structures
```cpp
// Fibonacci/Factorial memoization
unordered_map<int, long long> cache;

// Directory structure
struct DirEntry {
    string name;
    int file_size;
    vector<DirEntry> children;
};
```

## Key Concepts
- **Memoization**: Store computed results to avoid redundant work
- **Time Complexity**: Exponential → Linear improvements
- **Tree Recursion**: Directory size calculation via depth-first traversal
- **Timing**: Use `<chrono>` for microsecond-level measurements


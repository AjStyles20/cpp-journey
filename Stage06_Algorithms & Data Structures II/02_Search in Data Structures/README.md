# 02_Search in Data Structures

## Project Description
This project demonstrates and benchmarks three approaches to searching for an integer in a large sorted vector using C++:
1. **Iterative Binary Search**
2. **Recursive Binary Search**
3. **STL Binary Search** (using `std::lower_bound`)

It compares their correctness and performance on a dataset of 1,000,000 sorted even numbers.

## Learning Objectives
- Understand and implement iterative and recursive binary search algorithms
- Use STL algorithms for efficient searching
- Benchmark and compare algorithm performance using `<chrono>`
- Handle both successful and unsuccessful search cases

## Technologies Used
- **C++11** (or later)
- **STL Containers**: `vector`
- **STL Algorithms**: `lower_bound`
- **<chrono>** for timing
- **Visual Studio Code** (with C/C++ extension)

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o SearchDemo
   ```
2. Run the executable:
   ```bash
   ./SearchDemo    # Linux/Mac
   .\SearchDemo.exe # Windows
   ```

## How It Works

- The program creates a sorted vector of 1,000,000 even numbers: `0, 2, 4, ..., 1999998`.
- It searches for several targets (some present, some absent) using all three methods.
- For each search, it prints whether the target was found, its index (if found), and the time taken in nanoseconds.

## Example Output
```
Searching for 0:
Iterative: Found at index 0 (took 120 ns)
Recursive: Found at index 0 (took 110 ns)
STL: Found at index 0 (took 90 ns)

Searching for 123456:
Iterative: Found at index 61728 (took 130 ns)
Recursive: Found at index 61728 (took 120 ns)
STL: Found at index 61728 (took 100 ns)

Searching for 999999:
Iterative: Not found (took 130 ns)
Recursive: Not found (took 120 ns)
STL: Not found (took 100 ns)
...
```

## Key Functions

- `int binarySearchIterative(const vector<int>& arr, int target)`
- `int binarySearchRecursive(const vector<int>& arr, int target, int left, int right)`
- `int stlBinarySearch(const vector<int>& arr, int target)`
- `void testSearch(const string& name, int (*searchFunc)(const vector<int>&, int), const vector<int>& arr, int target)`

## Key Concepts
- **Binary Search**: Efficient O(log n) search in sorted arrays
- **Iterative vs Recursive**: Two approaches to binary search logic
- **STL Algorithms**: Using `std::lower_bound` for searching
- **Benchmarking**: Measuring execution time with `<chrono>`

## Notes
- The program tests both present and absent values to demonstrate search outcomes.
- You can modify the `targets` vector to test other values.
- The STL search returns the index using `lower_bound`, not just a boolean.

---

This project is a practical introduction to searching algorithms and performance measurement in C++.
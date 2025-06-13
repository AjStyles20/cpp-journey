# 05_Algorithm Comparison

## Project Description
This project benchmarks and compares the performance of three sorting algorithms in C++:
- **Bubble Sort** (simple, slow for large data)
- **QuickSort** (efficient, divide-and-conquer)
- **STL sort** (`std::sort`, highly optimized)

It measures and displays the time taken by each algorithm to sort random integer arrays of various sizes.

## Learning Objectives
- Understand the differences in time complexity and performance between sorting algorithms
- Implement and benchmark classic sorting algorithms
- Use C++ STL for efficient sorting and timing
- Analyze the scalability of algorithms with increasing data size

## Technologies Used
- **C++11** (or later)
- **STL Containers**: `vector`
- **STL Algorithms**: `sort`
- **<chrono>** for timing
- **Visual Studio Code** (with C/C++ extension)

## How to Run
1. Compile the program:
   ```bash
   g++ -std=c++11 main.cpp -o AlgorithmComparison
   ```
2. Run the executable:
   ```bash
   ./AlgorithmComparison    # Linux/Mac
   .\AlgorithmComparison.exe # Windows
   ```

## How It Works

- The program generates random integer arrays of sizes: 100, 1000, 5000, 10000, and 20000.
- For each size, it sorts the data using:
  - **Bubble Sort** (skipped for sizes > 10,000 due to slowness)
  - **QuickSort** (custom implementation)
  - **STL sort** (`std::sort`)
- It prints the time taken (in microseconds) for each algorithm.

## Example Output
```
Sorting Algorithm Performance Comparison
--------------------------------------

Data size: 100 elements
-----------------------
 Bubble Sort:      120 μs
   QuickSort:       30 μs
    STL sort:       10 μs

Data size: 10000 elements
-----------------------
 Bubble Sort:   950000 μs
   QuickSort:    12000 μs
    STL sort:     8000 μs

Data size: 20000 elements
-----------------------
 Bubble Sort:   (skipped - too slow)
   QuickSort:    25000 μs
    STL sort:    17000 μs
```

## Key Functions

- `bubbleSort(vector<int>& arr)` — Classic bubble sort
- `quickSort(vector<int>& arr, int low, int high)` — Recursive QuickSort
- `testSort(const string& name, void (*sortFunc)(vector<int>&), vector<int> data)` — Benchmarks a sorting function

## Key Concepts
- **Time Complexity**: Bubble Sort (O(n²)), QuickSort (O(n log n)), STL sort (O(n log n))
- **Benchmarking**: Using `<chrono>` for microsecond timing
- **Algorithm Scalability**: Performance impact as data size increases

## Notes
- Bubble Sort is only run for arrays up to 10,000 elements due to its inefficiency.
- STL sort is used as a reference for optimal performance.
- You can modify the `sizes` vector to test other data sizes.

---

This
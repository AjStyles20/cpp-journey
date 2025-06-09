#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. Fibonacci Sequence
// Naive recursive implementation (exponential time)
int fib_naive(int n) {
    if (n <= 1) return n;
    return fib_naive(n-1) + fib_naive(n-2);
}

// Memoized version (O(n) time)
unordered_map<int, long long> fib_cache;
long long fib_memo(int n) {
    if (n <= 1) return n;
    if (fib_cache.find(n) != fib_cache.end()) {
        return fib_cache[n];
    }
    fib_cache[n] = fib_memo(n-1) + fib_memo(n-2);
    return fib_cache[n];
}

// 2. Directory Size Calculation (simulated)
struct DirEntry {
    string name;
    int file_size;
    vector<DirEntry> children;
};

// Recursive directory size calculation
int calculateDirSize(const DirEntry& dir) {
    int total = dir.file_size; // Count the directory itself
    for (const auto& child : dir.children) {
        total += calculateDirSize(child);
    }
    return total;
}

// 3. Factorial with memoization
unordered_map<int, long long> fact_cache;
long long factorial(int n) {
    if (n <= 1) return 1;
    if (fact_cache.find(n) != fact_cache.end()) {
        return fact_cache[n];
    }
    fact_cache[n] = n * factorial(n-1);
    return fact_cache[n];
}

int main() {
    // Fibonacci comparison
    cout << "Fibonacci Sequence:\n";
    for (int n : {5, 10, 20, 30, 40}) {
        auto start = high_resolution_clock::now();
        long long result = fib_memo(n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "fib(" << n << ") = " << result 
             << " (computed in " << duration.count() << " μs)\n";
    }

    // Simulated directory structure
    DirEntry root {
        "Root",
        1000,
        {
            {"Documents", 500, {
                {"Work", 300, {}},
                {"Personal", 200, {}}
            }},
            {"Pictures", 1500, {
                {"Vacation", 800, {}},
                {"Family", 700, {}}
            }}
        }
    };

    cout << "\nDirectory Tree Size: " << calculateDirSize(root) << " KB\n";

    // Factorial demonstration
    cout << "\nFactorial with Memoization:\n";
    for (int n : {5, 10, 15, 20}) {
        cout << n << "! = " << factorial(n) << "\n";
    }

    return 0;
}
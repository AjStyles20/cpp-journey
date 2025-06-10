#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. Iterative binary search
int binarySearchIterative(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Not found
}

// 2. Recursive binary search
int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
    if (left > right) return -1;

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

// 3. STL binary_search wrapper to get index
int stlBinarySearch(const vector<int>& arr, int target) {
    auto it = lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end() && *it == target) {
        return distance(arr.begin(), it);
    }
    return -1;
}

template<typename F>
void testSearch(const string& name, F searchFunc, 
                const vector<int>& arr, int target) {
    auto start = high_resolution_clock::now();
    int result = searchFunc(arr, target);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << name << ": ";
    if (result != -1) {
        cout << "Found at index " << result;
    } else {
        cout << "Not found";
    }
    cout << " (took " << duration.count() << " ns)\n";
}

int main() {
    // Create a large sorted vector
    vector<int> numbers;
    for (int i = 0; i < 1000000; ++i) {
        numbers.push_back(i * 2); // Even numbers 0 to 1,999,998
    }

    // Test targets (existing and non-existing)
    vector<int> targets = {0, 123456, 999999, 1000000, 1999998, 1999999};

    for (int target : targets) {
        cout << "\nSearching for " << target << ":\n";
        testSearch("Iterative", binarySearchIterative, numbers, target);
        testSearch("Recursive", [&](const vector<int>& arr, int t) { 
            return binarySearchRecursive(arr, t, 0, arr.size()-1); 
        }, numbers, target);
        testSearch("STL", stlBinarySearch, numbers, target);
    }

    return 0;
}
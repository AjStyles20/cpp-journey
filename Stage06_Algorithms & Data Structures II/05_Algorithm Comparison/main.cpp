#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Bubble Sort implementation
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// QuickSort implementation
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// Generate random vector
vector<int> generateRandomData(int size) {
    vector<int> data(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);
    
    for (int& num : data) {
        num = dist(gen);
    }
    return data;
}

// Test sorting algorithm
void testSort(const string& name, void (*sortFunc)(vector<int>&), vector<int> data) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << setw(12) << name << ": " << setw(8) << duration.count() << " μs\n";
}

int main() {
    // Test with different input sizes
    vector<int> sizes = {100, 1000, 5000, 10000, 20000};
    
    cout << "Sorting Algorithm Performance Comparison\n";
    cout << "--------------------------------------\n";
    
    for (int size : sizes) {
        vector<int> data = generateRandomData(size);
        vector<int> copy1 = data; // Copy for Bubble Sort
        vector<int> copy2 = data; // Copy for QuickSort
        vector<int> copy3 = data; // Copy for STL sort
        
        cout << "\nData size: " << size << " elements\n";
        cout << "-----------------------\n";
        
        // Test Bubble Sort (only for smaller sizes)
        if (size <= 10000) {
            testSort("Bubble Sort", bubbleSort, copy1);
        } else {
            cout << "Bubble Sort:   (skipped - too slow)\n";
        }
        
        // Test QuickSort
        testSort("QuickSort", [](vector<int>& arr) {
            quickSort(arr, 0, arr.size()-1);
        }, copy2);
        
        // Test STL sort (reference)
        testSort("STL sort", [](vector<int>& arr) {
            sort(arr.begin(), arr.end());
        }, copy3);
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

using namespace std;

// Function to read integers from user input
vector<int> readIntegers() {
    vector<int> numbers;
    int num;
    
    cout << "Enter integers (enter any non-number to finish):\n";
    
    while (cin >> num) {
        numbers.push_back(num);
    }
    
    // Clear error state if non-number was entered
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return numbers;
}

// Function to calculate median of a sorted vector
double calculateMedian(vector<int>& nums) {
    if (nums.empty()) {
        throw invalid_argument("Cannot calculate median of empty vector");
    }
    
    size_t size = nums.size();
    if (size % 2 == 0) {
        // Even number of elements - average middle two
        return (nums[size/2 - 1] + nums[size/2]) / 2.0;
    } else {
        // Odd number of elements - return middle element
        return nums[size/2];
    }
}

int main() {
    try {
        // Read numbers from user
        vector<int> numbers = readIntegers();
        
        if (numbers.empty()) {
            cout << "No numbers entered.\n";
            return 0;
        }
        
        // Sort the vector
        sort(numbers.begin(), numbers.end());
        
        // Display sorted numbers
        cout << "\nSorted numbers: ";
        for (int num : numbers) {
            cout << num << " ";
        }
        cout << "\n";
        
        // Calculate and display median
        double median = calculateMedian(numbers);
        cout << "Median: " << median << "\n";
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
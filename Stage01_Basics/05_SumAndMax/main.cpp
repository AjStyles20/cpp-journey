#include <iostream>
#include <vector>
#include <limits> // Required for numeric_limits
#include <numeric> // For std::accumulate

using namespace std;

int main() {
    vector<double> input;
    double num;
    cout << "Enter 'q' to quit" << endl;
    cout << "Enter your numbers :";

    while (cin >> num) {
        input.push_back(num);
        cout << "Enter another number or 'q' to quit: ";
    }

    // Clear the error flags and ignore any remaining input in the buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nYou entered the following numbers:" << endl;
    for (double val : input) {
        cout << val << " ";
    }
    cout << endl;

    if (!input.empty()) {
        double sum = 0;
        double max_num = input[0]; // Initialize max with the first element

        // Loop to calculate the sum and find the maximum
        for (double val : input) {
            sum += val;
            if (val > max_num) {
                max_num = val;
            }
        }

        cout << "Sum of the numbers: " << sum << endl;
        cout << "Maximum number: " << max_num << endl;
    } else {
        cout << "No numbers were entered." << endl;
    }

    return 0;
}
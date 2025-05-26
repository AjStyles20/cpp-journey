#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <filesystem> // For checking file existence

int main() {
    const std::string inputFilename = "input.txt";
    const std::string outputFilename = "output.txt";

    // Check if input file exists first
    if (!std::filesystem::exists(inputFilename)) {
        std::cerr << "Error: File '" << inputFilename << "' not found in:\n"
                  << std::filesystem::current_path() << "\n";
        return 1;
    }

    // Open input file
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Error: Could not open '" << inputFilename << "' for reading\n";
        return 1;
    }

    // Read numbers
    std::vector<double> numbers;
    double num;
    while (inputFile >> num) {
        numbers.push_back(num);
    }

    // Check if we actually read anything
    if (inputFile.eof() && numbers.empty()) {
        std::cerr << "Error: '" << inputFilename << "' exists but contains no valid numbers\n";
        inputFile.close();
        return 1;
    }
    inputFile.close();

    // Calculate statistics
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    double average = sum / numbers.size();

    // Write output
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error: Could not open '" << outputFilename << "' for writing\n";
        return 1;
    }

    outputFile << "Statistics Report\n"
               << "================\n"
               << "Numbers processed: " << numbers.size() << "\n"
               << "Sum: " << sum << "\n"
               << "Average: " << average << "\n";

    outputFile.close();
    std::cout << "Successfully processed " << numbers.size() 
              << " numbers. Results written to " << outputFilename << "\n";

    return 0;
}
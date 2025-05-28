#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept> // For standard exceptions

using namespace std;

struct Person {
    string name;
    int age;
    string occupation;
    
    void display() const {
        cout << "Name: " << name 
             << ", Age: " << age 
             << ", Occupation: " << occupation << endl;
    }
};

Person parseCSVLine(const string& line) {
    Person person;
    stringstream ss(line);
    string token;
    
    try {
        // Name parsing
        if (!getline(ss, token, ',')) {
            throw runtime_error("Missing name field");
        }
        person.name = token;
        
        // Age parsing with validation
        if (!getline(ss, token, ',')) {
            throw runtime_error("Missing age field");
        }
        try {
            person.age = stoi(token);
            if (person.age < 0) throw out_of_range("Age cannot be negative");
        } catch (const invalid_argument&) {
            throw invalid_argument("Invalid age format: " + token);
        } catch (const out_of_range&) {
            throw out_of_range("Age out of reasonable range: " + token);
        }
        
        // Occupation parsing
        if (!getline(ss, token)) {
            throw runtime_error("Missing occupation field");
        }
        person.occupation = token;
        
    } catch (const exception& e) {
        throw runtime_error("Error parsing line: " + line + "\nReason: " + e.what());
    }
    
    return person;
}

vector<Person> readCSVFile(const string& filename) {
    ifstream file;
    vector<Person> people;
    
    try {
        // File opening with validation
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file: " + filename);
        }
        
        string line;
        // Skip header with validation
        if (!getline(file, line)) {
            throw runtime_error("Empty file or missing header");
        }
        
        // Line reading with counter
        int line_num = 1;
        while (getline(file, line)) {
            line_num++;
            try {
                if (!line.empty()) {
                    people.push_back(parseCSVLine(line));
                }
            } catch (const exception& e) {
                cerr << "Error on line " << line_num << ": " << e.what() << endl;
            }
        }
        
        if (people.empty()) {
            throw runtime_error("No valid records found in file");
        }
        
    } catch (const exception& e) {
        file.close();
        throw; // Re-throw to main
    }
    
    file.close();
    return people;
}

void writeStatistics(const vector<Person>& people, const string& outputFilename) {
    try {
        if (people.empty()) {
            throw runtime_error("No data to process");
        }
        
        ofstream outFile(outputFilename);
        if (!outFile) {
            throw runtime_error("Could not create output file");
        }
        
        // Calculate average age
        int totalAge = 0;
        for (const auto& person : people) {
            totalAge += person.age;
        }
        double avgAge = static_cast<double>(totalAge) / people.size();
        
        outFile << "Statistics Report\n"
                << "Total records: " << people.size() << "\n"
                << "Average age: " << avgAge << "\n";
        
        outFile.close();
        cout << "Statistics written to " << outputFilename << endl;
        
    } catch (const exception& e) {
        cerr << "Error generating statistics: " << e.what() << endl;
        throw;
    }
}

int main() {
    try {
        string inputFile, outputFile;
        
        cout << "Enter input CSV filename: ";
        getline(cin, inputFile);
        cout << "Enter output filename: ";
        getline(cin, outputFile);
        
        vector<Person> people = readCSVFile(inputFile);
        
        cout << "\nSuccessfully processed " << people.size() << " records:\n";
        for (const auto& person : people) {
            person.display();
        }
        
        writeStatistics(people, outputFile);
        
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
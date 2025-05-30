#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip> // for put_time

using namespace std;

// Error logger class
class ErrorLogger {
private:
    ofstream logFile;
    
public:
    ErrorLogger(const string& filename = "error_log.txt") {
        logFile.open(filename, ios::app);
        if (!logFile) {
            cerr << "Warning: Could not open error log file. Logging to console only.\n";
        }
    }
    
    ~ErrorLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    void log(const string& message, bool isCritical = false) {
        // Get current time
        time_t now = time(nullptr);
        tm tm = *localtime(&now);
        
        // Format timestamp
        string timestamp;
        timestamp.resize(20);
        strftime(&timestamp[0], 20, "%Y-%m-%d %H:%M:%S", &tm);
        
        // Format full message
        string fullMessage = "[" + timestamp + "] " + 
                           (isCritical ? "CRITICAL: " : "ERROR: ") + 
                           message + "\n";
        
        // Output to console
        cerr << fullMessage;
        
        // Output to file if available
        if (logFile.is_open()) {
            logFile << fullMessage;
            logFile.flush();
        }
        
        if (isCritical) {
            throw runtime_error(fullMessage);
        }
    }
};

// Data processor with error handling
class DataProcessor {
private:
    ErrorLogger& logger;
    
public:
    DataProcessor(ErrorLogger& logger) : logger(logger) {}
    
    vector<int> processFile(const string& filename) {
        vector<int> numbers;
        ifstream file(filename);
        
        // Check if file exists and can be opened
        if (!file) {
            logger.log("Could not open file: " + filename);
            return numbers;
        }
        
        string line;
        int lineNum = 0;
        
        while (getline(file, line)) {
            lineNum++;
            
            try {
                if (line.empty()) {
                    logger.log("Empty line at " + to_string(lineNum) + " in " + filename);
                    continue;
                }
                
                int num = stoi(line);
                if (num < 0) {
                    logger.log("Negative number at line " + to_string(lineNum) + ": " + line);
                    continue;
                }
                
                numbers.push_back(num);
                
            } catch (const invalid_argument&) {
                logger.log("Invalid number format at line " + to_string(lineNum) + ": " + line);
            } catch (const out_of_range&) {
                logger.log("Number too large at line " + to_string(lineNum) + ": " + line);
            }
        }
        
        if (numbers.empty()) {
            logger.log("No valid numbers found in file: " + filename);
        }
        
        return numbers;
    }
};

int main() {
    ErrorLogger logger;
    DataProcessor processor(logger);
    
    try {
        cout << "File Processing System (enter filenames, 'quit' to exit)\n";
        
        while (true) {
            cout << "Enter filename: ";
            string filename;
            getline(cin, filename);
            
            if (filename == "quit") break;
            
            vector<int> numbers = processor.processFile(filename);
            
            if (!numbers.empty()) {
                cout << "Successfully processed " << numbers.size() 
                     << " numbers from " << filename << endl;
                
                // Calculate and display average
                double sum = 0;
                for (int num : numbers) {
                    sum += num;
                }
                cout << "Average: " << (sum / numbers.size()) << endl;
            }
        }
        
    } catch (const exception& e) {
        logger.log("Fatal error: " + string(e.what()), true);
        return 1;
    }
    
    return 0;
}
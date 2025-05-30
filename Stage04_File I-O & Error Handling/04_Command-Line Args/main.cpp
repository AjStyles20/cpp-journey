#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::find

using namespace std;

// Display help information
void showHelp() {
    cout << "Command-Line Argument Processor\n"
         << "Usage:\n"
         << "  ./program [options] [arguments]\n\n"
         << "Options:\n"
         << "  -h, --help       Show this help message\n"
         << "  -f <file>        Process specified file\n"
         << "  -n <number>      Process a number\n"
         << "  -v, --verbose    Enable verbose output\n\n"
         << "Examples:\n"
         << "  ./program -f data.txt -n 42\n"
         << "  ./program --verbose -n 100\n";
}

// Process a file
void processFile(const string& filename, bool verbose) {
    if (verbose) {
        cout << "Processing file: " << filename << endl;
    }
    // Add your file processing logic here
    cout << "File '" << filename << "' would be processed here.\n";
}

// Process a number
void processNumber(int num, bool verbose) {
    if (verbose) {  
        cout << "Processing number: " << num << endl;
    }
    // Add your number processing logic here
    cout << "Number " << num << " would be processed here.\n";
}

int main(int argc, char* argv[]) {
    vector<string> args(argv + 1, argv + argc); // Convert argv to vector
    bool verbose = false;
    string filename;
    int number = 0;
    bool hasNumber = false;

    // Check for help request
    if (argc == 1 || find(args.begin(), args.end(), "-h") != args.end() || 
        find(args.begin(), args.end(), "--help") != args.end()) {
        showHelp();
        return 0;
    }

    // Process arguments
    for (size_t i = 0; i < args.size(); ++i) {
        string arg = args[i];
        
        if (arg == "-v" || arg == "--verbose") {
            verbose = true;
            cout << "Verbose mode enabled.\n";
        }
        else if (arg == "-f") {
            if (i + 1 < args.size()) {
                filename = args[++i];
                processFile(filename, verbose);
            } else {
                cerr << "Error: Missing filename after -f option.\n";
                return 1;
            }
        }
        else if (arg == "-n") {
            if (i + 1 < args.size()) {
                try {
                    number = stoi(args[++i]);
                    hasNumber = true;
                    processNumber(number, verbose);
                } catch (const invalid_argument&) {
                    cerr << "Error: Invalid number format.\n";
                    return 1;
                } catch (const out_of_range&) {
                    cerr << "Error: Number out of range.\n";
                    return 1;
                }
            } else {
                cerr << "Error: Missing number after -n option.\n";
                return 1;
            }
        }
        else {
            cerr << "Error: Unknown argument '" << arg << "'\n";
            showHelp();
            return 1;
        }
    }

    // Check if required arguments were provided
    if (filename.empty() && !hasNumber) {
        cerr << "Error: No file or number specified for processing.\n";
        showHelp();
        return 1;
    }

    return 0;
}
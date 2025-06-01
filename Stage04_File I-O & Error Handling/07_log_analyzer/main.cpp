#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == string::npos || last == string::npos) return "";
    return str.substr(first, (last - first + 1));
}

// Extract log level from line: assumes format "[timestamp] LEVEL: message"
string extractLevel(const string& line) {
    size_t closeBracket = line.find(']');
    if (closeBracket == string::npos) return "";

    size_t levelStart = closeBracket + 2;
    size_t colon = line.find(':', levelStart);
    if (colon == string::npos) return "";

    return line.substr(levelStart, colon - levelStart);
}

// Extract timestamp from line: assumes format "[timestamp] LEVEL: message"
string extractTimestamp(const string& line) {
    size_t openBracket = line.find('[');
    size_t closeBracket = line.find(']');
    if (openBracket == string::npos || closeBracket == string::npos) return "";

    return line.substr(openBracket + 1, closeBracket - openBracket - 1);
}

// Compare timestamps as strings (ISO-like format allows lexicographical comparison)
bool inTimeRange(const string& timestamp, const string& start, const string& end) {
    return (start.empty() || timestamp >= start) && (end.empty() || timestamp <= end);
}

// Write results to a file
void exportToFile(const vector<string>& lines, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not write to " << filename << endl;
        return;
    }
    for (const auto& line : lines) {
        outFile << line << endl;
    }
    cout << "Results written to: " << filename << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <log_file> [--level LEVEL] [--start YYYY-MM-DD_HH:MM:SS] [--end ...] [--out output.txt]\n";
        return 1;
    }

    string logFile = argv[1];
    string filterLevel = "";
    string startTime = "";
    string endTime = "";
    string outFile = "";

    // Parse optional arguments
    for (int i = 2; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--level" && i + 1 < argc) {
            filterLevel = argv[++i];
            transform(filterLevel.begin(), filterLevel.end(), filterLevel.begin(), ::toupper);
        } else if (arg == "--start" && i + 1 < argc) {
            startTime = argv[++i];
        } else if (arg == "--end" && i + 1 < argc) {
            endTime = argv[++i];
        } else if (arg == "--out" && i + 1 < argc) {
            outFile = argv[++i];
        }
    }

    ifstream file(logFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open log file.\n";
        return 1;
    }

    string line;
    int totalLines = 0;
    vector<string> matchingLines;
    map<string, int> levelCounts;

    while (getline(file, line)) {
        totalLines++;

        string trimmed = trim(line);
        string level = extractLevel(trimmed);
        string timestamp = extractTimestamp(trimmed);

        // Update count for this level
        if (!level.empty())
            levelCounts[level]++;

        // Filter by level and timestamp range
        bool matchesLevel = filterLevel.empty() || level == filterLevel;
        bool matchesTime = inTimeRange(timestamp, startTime, endTime);

        if (matchesLevel && matchesTime) {
            matchingLines.push_back(trimmed);
        }
    }

    file.close();

    // Display summary
    cout << "Analyzed " << totalLines << " lines.\n";
    cout << "Log Level Counts:\n";
    for (const auto& [lvl, count] : levelCounts) {
        cout << "  " << lvl << ": " << count << endl;
    }

    // Show filtered results
    cout << "\nMatching Entries (" << matchingLines.size() << "):\n";
    for (const string& line : matchingLines) {
        cout << line << endl;
    }

    // Export to file if requested
    if (!outFile.empty()) {
        exportToFile(matchingLines, outFile);
    }

    return 0;
}

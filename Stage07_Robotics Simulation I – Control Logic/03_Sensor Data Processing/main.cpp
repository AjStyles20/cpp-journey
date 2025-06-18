#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct SensorReading {
    string timestamp;
    double value;
};

vector<SensorReading> readSensorData(const string& filename) {
    vector<SensorReading> readings;
    ifstream file(filename);
    
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open file " + filename);
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line);
        string timestamp;
        double value;

        if (iss >> timestamp >> value) {
            readings.push_back({timestamp, value});
        } else {
            cerr << "Warning: Invalid line format - " << line << endl;
        }
    }

    if (readings.empty()) {
        throw runtime_error("Error: No valid data found in file");
    }

    return readings;
}

void computeStatistics(const vector<SensorReading>& readings) {
    if (readings.empty()) return;

    double minVal = numeric_limits<double>::max();
    double maxVal = numeric_limits<double>::lowest();
    double sum = 0.0;

    for (const auto& reading : readings) {
        minVal = min(minVal, reading.value);
        maxVal = max(maxVal, reading.value);
        sum += reading.value;
    }

    double average = sum / readings.size();

    cout << fixed << setprecision(3);
    cout << "\nSensor Data Statistics:\n";
    cout << "-----------------------\n";
    cout << "Total readings: " << readings.size() << "\n";
    cout << "Minimum value:  " << minVal << "\n";
    cout << "Maximum value:  " << maxVal << "\n";
    cout << "Average value:  " << average << "\n";

    // Additional statistics could be added here:
    // - Standard deviation
    // - Median
    // - Time range
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <sensor_data_file>\n";
        return 1;
    }

    try {
        string filename = argv[1];
        cout << "Processing sensor data from: " << filename << "\n";

        vector<SensorReading> readings = readSensorData(filename);
        computeStatistics(readings);

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
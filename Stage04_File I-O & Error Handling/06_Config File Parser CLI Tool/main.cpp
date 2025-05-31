#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

// Trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// Convert string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c){ return tolower(c); });
    return lowerStr;
}

// Configuration parser class
class ConfigParser {
private:
    map<string, string> config;
    string filename;

    void parseLine(const string& line) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos == string::npos) return;

        string key = trim(line.substr(0, delimiterPos));
        string value = trim(line.substr(delimiterPos + 1));

        if (!key.empty()) {
            config[toLower(key)] = value;
        }
    }

public:
    ConfigParser(const string& file) : filename(file) {
        ifstream fileStream(filename);
        if (!fileStream.is_open()) {
            throw runtime_error("Could not open config file: " + filename);
        }

        string line;
        while (getline(fileStream, line)) {
            // Skip comments and empty lines
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;
            
            parseLine(line);
        }
        fileStream.close();
    }

    bool hasKey(const string& key) const {
        return config.find(toLower(key)) != config.end();
    }

    string getValue(const string& key) const {
        auto it = config.find(toLower(key));
        if (it == config.end()) {
            throw out_of_range("Key not found: " + key);
        }
        return it->second;
    }

    void setValue(const string& key, const string& value) {
        config[toLower(key)] = value;
    }

    void saveToFile() {
        ofstream fileStream(filename);
        if (!fileStream.is_open()) {
            throw runtime_error("Could not write to config file: " + filename);
        }

        for (const auto& pair : config) {
            fileStream << pair.first << " = " << pair.second << "\n";
        }
        fileStream.close();
    }

    void printAll() const {
        cout << "Current configuration:\n";
        for (const auto& pair : config) {
            cout << "  " << pair.first << " = " << pair.second << "\n";
        }
    }
};

void showHelp() {
    cout << "Config Parser CLI Tool\n"
         << "Usage:\n"
         << "  config_tool <config_file> [options]\n\n"
         << "Options:\n"
         << "  get <key>        Get value for a key\n"
         << "  set <key> <value> Set value for a key\n"
         << "  list             Show all key-value pairs\n"
         << "  help             Show this help message\n\n"
         << "Example:\n"
         << "  config_tool settings.cfg get timeout\n"
         << "  config_tool app.conf set port 8080\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showHelp();
        return 1;
    }

    try {
        string configFile = argv[1];
        ConfigParser parser(configFile);

        if (argc == 2) {
            parser.printAll();
            return 0;
        }

        string command = argv[2];
        
        if (command == "get" && argc == 4) {
            cout << parser.getValue(argv[3]) << endl;
        }
        else if (command == "set" && argc == 5) {
            parser.setValue(argv[3], argv[4]);
            parser.saveToFile();
            cout << "Updated " << argv[3] << " = " << argv[4] << endl;
        }
        else if (command == "list") {
            parser.printAll();
        }
        else if (command == "help") {
            showHelp();
        }
        else {
            cerr << "Invalid command or arguments\n";
            showHelp();
            return 1;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
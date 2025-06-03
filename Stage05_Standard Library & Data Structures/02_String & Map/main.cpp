#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cctype> // for tolower()
#include <sstream>
#include <algorithm>

using namespace std;

// Function to clean and normalize a word
string normalizeWord(const string& word) {
    string normalized;
    for (char c : word) {
        if (isalpha(c)) {
            normalized += tolower(c);
        }
    }
    return normalized;
}

// Function to count word frequencies
map<string, int> countWordFrequencies(const string& paragraph) {
    map<string, int> wordCounts;
    istringstream iss(paragraph);
    string word;

    while (iss >> word) {
        string cleanWord = normalizeWord(word);
        if (!cleanWord.empty()) {
            wordCounts[cleanWord]++;
        }
    }

    return wordCounts;
}

// Function to display results sorted by frequency
void displayByFrequency(const map<string, int>& wordCounts) {
    // Copy to vector for sorting
    vector<pair<string, int>> counts(wordCounts.begin(), wordCounts.end());

    // Sort by frequency (descending)
    sort(counts.begin(), counts.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

    // Display results
    cout << "\nWord Frequencies (sorted by count):\n";
    cout << "--------------------------------\n";
    for (const auto& entry : counts) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

int main() {
    string paragraph;
    
    cout << "Enter a paragraph of text (press Enter twice to finish):\n";
    
    // Read multiple lines until empty line
    string line;
    while (getline(cin, line) && !line.empty()) {
        paragraph += line + " ";
    }

    if (paragraph.empty()) {
        cout << "No text entered.\n";
        return 0;
    }

    // Count word frequencies
    map<string, int> wordCounts = countWordFrequencies(paragraph);

    // Display results
    displayByFrequency(wordCounts);

    return 0;
}
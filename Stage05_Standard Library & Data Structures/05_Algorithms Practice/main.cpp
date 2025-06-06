#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype> // for toupper(), tolower()
#include <string>

using namespace std;

// Function object for capitalization
struct Capitalize {
    char operator()(char c) const {
        return toupper(c);
    }
};

// Function to lowercase a character
char toLower(char c) {
    return tolower(c);
}

int main() {
    vector<string> words = {"apple", "Banana", "Cherry", "date", "EGGPLANT"};

    // 1. Transform all strings to uppercase using function object
    cout << "All uppercase:\n";
    for (string& word : words) {
        transform(word.begin(), word.end(), word.begin(), Capitalize());
        cout << word << " ";
    }
    cout << "\n\n";

    // 2. Transform to lowercase using function pointer
    cout << "All lowercase:\n";
    for (string& word : words) {
        transform(word.begin(), word.end(), word.begin(), toLower);
        cout << word << " ";
    }
    cout << "\n\n";

    // 3. Find first word with length 5 using lambda
    auto it = find_if(words.begin(), words.end(), 
        [](const string& s) { return s.length() == 5; });
    
    if (it != words.end()) {
        cout << "First word with length 5: " << *it << "\n\n";
    }

    // 4. Count words starting with 'a' or 'A'
    int count = count_if(words.begin(), words.end(),
        [](const string& s) { return !s.empty() && (s[0] == 'a' || s[0] == 'A'); });
    cout << count << " words start with 'a' or 'A'\n\n";

    // 5. Print modified words using for_each
    cout << "Modified words:\n";
    for_each(words.begin(), words.end(),
        [](const string& s) { cout << "• " << s << "\n"; });

    return 0;
}
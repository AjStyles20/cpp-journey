#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

// Text Editor with Undo (Stack) Simulation
class TextEditor {
private:
    stack<string> documentStates;
    string currentDoc;

public:
    void type(const string& text) {
        // Save current state before modification
        documentStates.push(currentDoc);
        currentDoc += text;
        cout << "Typed: \"" << text << "\"\n";
    }

    void undo() {
        if (!documentStates.empty()) {
            currentDoc = documentStates.top();
            documentStates.pop();
            cout << "Undo performed. Current content:\n";
        } else {
            cout << "Nothing to undo!\n";
        }
        display();
    }

    void display() const {
        cout << "Current document: \"" << currentDoc << "\"\n";
    }
};

// Printer Queue (Queue) Simulation
class PrinterQueue {
private:
    queue<string> printJobs;

public:
    void addJob(const string& document) {
        printJobs.push(document);
        cout << "Added to queue: \"" << document << "\"\n";
    }

    void printNext() {
        if (!printJobs.empty()) {
            cout << "Printing: \"" << printJobs.front() << "\"\n";
            printJobs.pop();
        } else {
            cout << "No jobs in queue!\n";
        }
    }

    void displayQueue() const {
        if (printJobs.empty()) {
            cout << "Printer queue is empty\n";
            return;
        }

        cout << "Current printer queue (" << printJobs.size() << " jobs):\n";
        queue<string> temp = printJobs;
        int position = 1;
        while (!temp.empty()) {
            cout << position++ << ". " << temp.front() << "\n";
            temp.pop();
        }
    }
};

void showMenu() {
    cout << "\nChoose simulation:\n"
         << "1. Text Editor (Stack)\n"
         << "2. Printer Queue (Queue)\n"
         << "3. Exit\n"
         << "Enter choice: ";
}

void runEditorSimulation() {
    TextEditor editor;
    string input;
    
    cout << "\n=== Text Editor Simulation (type 'undo' to undo, 'exit' to quit) ===\n";
    while (true) {
        cout << "Enter text: ";
        getline(cin, input);
        
        if (input == "undo") {
            editor.undo();
        } else if (input == "exit") {
            break;
        } else {
            editor.type(input);
        }
    }
}

void runPrinterSimulation() {
    PrinterQueue printer;
    string input;
    
    cout << "\n=== Printer Queue Simulation ===\n"
         << "Commands:\n"
         << "  'add <text>' - Add document\n"
         << "  'print'      - Print next job\n"
         << "  'exit'       - Quit\n";
    
    while (true) {
        cout << "\nEnter command: ";
        getline(cin, input);
        
        if (input.substr(0, 4) == "add ") {
            printer.addJob(input.substr(4));
        } else if (input == "print") {
            printer.printNext();
        } else if (input == "queue") {
            printer.displayQueue();
        } else if (input == "exit") {
            break;
        } else {
            cout << "Invalid command!\n";
        }
    }
}

int main() {
    while (true) {
        showMenu();
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            runEditorSimulation();
        } else if (choice == "2") {
            runPrinterSimulation();
        } else if (choice == "3") {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}
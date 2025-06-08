#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct StudentRecord {
    string name;
    double grade;
    string remarks;
};

class GradeManager {
private:
    map<int, StudentRecord> database; // student ID -> record

public:
    void addStudent(int id, const string& name, double grade) {
        string remarks = (grade >= 90) ? "Excellent" :
                        (grade >= 80) ? "Good" :
                        (grade >= 70) ? "Average" : "Needs Improvement";
        
        database[id] = {name, grade, remarks};
        cout << "Added student: ID " << id << " - " << name << "\n";
    }

    void removeStudent(int id) {
        if (database.erase(id)) {
            cout << "Removed student ID " << id << "\n";
        } else {
            cout << "Student ID " << id << " not found!\n";
        }
    }

    void displayStudent(int id) const {
        auto it = database.find(id);
        if (it != database.end()) {
            cout << "\nStudent Record:\n"
                 << "ID: " << id << "\n"
                 << "Name: " << it->second.name << "\n"
                 << "Grade: " << fixed << setprecision(2) << it->second.grade << "\n"
                 << "Remarks: " << it->second.remarks << "\n";
        } else {
            cout << "Student ID " << id << " not found!\n";
        }
    }

    void displayAll() const {
        if (database.empty()) {
            cout << "No student records available.\n";
            return;
        }

        cout << "\nAll Student Records:\n";
        cout << setw(10) << "ID" << setw(20) << "Name" 
             << setw(10) << "Grade" << setw(20) << "Remarks\n";
        cout << string(60, '-') << "\n";

        for (const auto& entry : database) {
            cout << setw(10) << entry.first 
                 << setw(20) << entry.second.name
                 << setw(10) << fixed << setprecision(2) << entry.second.grade
                 << setw(20) << entry.second.remarks << "\n";
        }
    }
};

void displayMenu() {
    cout << "\nGrade Management System\n"
         << "1. Add Student\n"
         << "2. Remove Student\n"
         << "3. Lookup Student\n"
         << "4. Display All\n"
         << "5. Exit\n"
         << "Enter choice: ";
}

int main() {
    GradeManager manager;
    int choice, id;
    string name;
    double grade;

    while (true) {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter student ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, name);
                cout << "Enter student grade (0-100): ";
                cin >> grade;
                manager.addStudent(id, name, grade);
                break;
            case 2:
                cout << "Enter student ID to remove: ";
                cin >> id;
                manager.removeStudent(id);
                break;
            case 3:
                cout << "Enter student ID to lookup: ";
                cin >> id;
                manager.displayStudent(id);
                break;
            case 4:
                manager.displayAll();
                break;
            case 5:
                cout << "Exiting system.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
#include <iostream>
#include <map>
#include <string>
#include <iomanip> // for setw
#include <limits>  // for cin.ignore

using namespace std;

class Phonebook {
private:
    map<string, string> contacts; // name -> phone number

public:
    void addContact(const string& name, const string& number) {
        auto result = contacts.insert({name, number});
        if (!result.second) {
            cout << "Contact already exists. Updating number.\n";
            contacts[name] = number;
        }
        cout << "Contact saved: " << name << " - " << number << "\n";
    }

    void findContact(const string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            cout << "Contact found: " << it->first << " - " << it->second << "\n";
        } else {
            cout << "Contact not found.\n";
        }
    }

    void deleteContact(const string& name) {
        if (contacts.erase(name)) {
            cout << "Contact deleted.\n";
        } else {
            cout << "Contact not found.\n";
        }
    }

    void listAllContacts() const {
        if (contacts.empty()) {
            cout << "Phonebook is empty.\n";
            return;
        }

        cout << "\nPhonebook Contacts:\n";
        cout << setw(20) << left << "NAME" << "PHONE NUMBER\n";
        cout << string(40, '-') << "\n";
        
        for (const auto& contact : contacts) {
            cout << setw(20) << left << contact.first << contact.second << "\n";
        }
    }
};

void displayMenu() {
    cout << "\nPhonebook Menu:\n"
         << "1. Add Contact\n"
         << "2. Find Contact\n"
         << "3. Delete Contact\n"
         << "4. List All Contacts\n"
         << "5. Exit\n"
         << "Enter your choice: ";
}

int main() {
    Phonebook phonebook;
    string name, number;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, number);
                phonebook.addContact(name, number);
                break;
            case 2:
                cout << "Enter name to find: ";
                getline(cin, name);
                phonebook.findContact(name);
                break;
            case 3:
                cout << "Enter name to delete: ";
                getline(cin, name);
                phonebook.deleteContact(name);
                break;
            case 4:
                phonebook.listAllContacts();
                break;
            case 5:
                cout << "Exiting phonebook.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
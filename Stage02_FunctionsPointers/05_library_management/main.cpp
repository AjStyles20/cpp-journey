#include <iostream>
#include <string>
#include "library.h"

using namespace std;
using namespace Library;

int main() {
    int choice;

    do {
        cout << "\n--- Library Management System ---" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Register User" << endl;
        cout << "4. Display Users" << endl;
        cout << "5. Borrow Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Display Borrowed Books" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Consume the newline character

        switch (choice) {
            case 1: {
                string title, author, isbn;
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                Book newBook(title, author, isbn);
                addBook(newBook);
                break;
            }
            case 2:
                displayBooks();
                break;
            case 3: {
                int userId;
                string name;
                cout << "Enter user ID: ";
                cin >> userId;
                cin.ignore(); // Consume the newline character
                cout << "Enter user name: ";
                getline(cin, name);
                User newUser(userId, name);
                registerUser(newUser);
                break;
            }
            case 4:
                displayUsers();
                break;
            case 5: {
                int userId;
                string isbn;
                cout << "Enter user ID borrowing the book: ";
                cin >> userId;
                cin.ignore();
                cout << "Enter ISBN of the book to borrow: ";
                getline(cin, isbn);
                borrowBook(userId, isbn);
                break;
            }
            case 6: {
                string isbn;
                cout << "Enter ISBN of the book to return: ";
                getline(cin, isbn);
                returnBook(isbn);
                break;
            }
            case 7:
                displayBorrowedBooks();
                break;
            case 0:
                cout << "Exiting the Library Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
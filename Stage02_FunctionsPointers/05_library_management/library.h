#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector> 

namespace Library {

// Structure to represent a Book
struct Book {
    std::string title;
    std::string author;
    std::string isbn;
    bool isBorrowed; // To track if the book is borrowed

    // Constructor for convenience
    Book(const std::string& title = "", const std::string& author = "", const std::string& isbn = "")
        : title(title), author(author), isbn(isbn), isBorrowed(false) {}
};

// Structure to represent a User
struct User {
    int userId;
    std::string name;

    // Constructor for convenience
    User(int id = 0, const std::string& name = "") : userId(id), name(name) {}
};

// Global variable to track the total number of books
extern int totalBooks;

// Function prototypes for Book Management (defined in book_management.cpp)
void addBook(const Book& book);
void displayBooks();

// Function prototypes for User Management (defined in user_management.cpp)
void registerUser(const User& user);
void displayUsers();

// Function prototypes for Borrowing/Returning (defined in borrowing.cpp)
void borrowBook(int userId, const std::string& isbn);
void returnBook(const std::string& isbn);
void displayBorrowedBooks(); // Optional: To see which books are borrowed

} // namespace Library

#endif // LIBRARY_H
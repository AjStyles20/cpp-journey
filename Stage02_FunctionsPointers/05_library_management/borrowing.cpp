#include "library.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Library {

static std::map<std::string, int> borrowedBooks;

// Helper function to find a book by ISBN
static Book* findBookByISBN(const std::string& isbn) {
    extern std::vector<Book> books;

    for (auto& book : books) {
        if (book.isbn == isbn) {
            return &book;
        }
    }
    return nullptr;
}

// Helper function to find a user by ID
static User* findUserByID(int userId) {
    extern std::vector<User> users;
    for (auto& user : users) {
        if (user.userId == userId) {
            return &user;
        }
    }
    return nullptr;
}

void borrowBook(int userId, const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    User* user = findUserByID(userId);

    if (!user) {
        std::cout << "User with ID " << userId << " not found." << std::endl;
        return;
    }

    if (!book) {
        std::cout << "Book with ISBN " << isbn << " not found." << std::endl;
        return;
    }

    if (book->isBorrowed) {
        std::cout << "Book '" << book->title << "' is already borrowed." << std::endl;
        return;
    }

    borrowedBooks[isbn] = userId;
    book->isBorrowed = true;
    std::cout << "User '" << user->name << "' (ID " << userId << ") has borrowed book '" << book->title << "'." << std::endl;
}

void returnBook(const std::string& isbn) {
    Book* book = findBookByISBN(isbn);

    if (!book) {
        std::cout << "Book with ISBN " << isbn << " not found." << std::endl;
        return;
    }

    if (!book->isBorrowed) {
        std::cout << "Book '" << book->title << "' is not currently borrowed." << std::endl;
        return;
    }

    int borrowerId = borrowedBooks[isbn];
    User* user = findUserByID(borrowerId);

    borrowedBooks.erase(isbn);
    book->isBorrowed = false;
    std::cout << "Book '" << book->title << "' has been returned by user '" << user->name << "' (ID " << borrowerId << ")." << std::endl;
}

void displayBorrowedBooks() {
    if (borrowedBooks.empty()) {
        std::cout << "No books are currently borrowed." << std::endl;
        return;
    }
    std::cout << "\n--- Currently Borrowed Books ---" << std::endl;
    for (const auto& pair : borrowedBooks) {
        std::string isbn = pair.first;
        int userId = pair.second;
        Book* book = findBookByISBN(isbn);
        User* user = findUserByID(userId);
        if (book && user) {
            std::cout << "Book: '" << book->title << "' (ISBN: " << isbn << ") - Borrowed by: '" << user->name << "' (ID: " << userId << ")" << std::endl;
        }
    }
}


std::vector<Book> books;
std::vector<User> users;

} // namespace Library
#include "library.h"
#include <iostream>
#include <vector>

namespace Library {

// Definition of the global variable totalBooks
int totalBooks = 0;

// Static vector to store the books in the library (local to this file)
static std::vector<Book> books;

void addBook(const Book& book) {
    books.push_back(book);
    totalBooks++;
    std::cout << "Book '" << book.title << "' added to the library." << std::endl;
}

void displayBooks() {
    if (books.empty()) {
        std::cout << "The library has no books." << std::endl;
        return;
    }
    std::cout << "\n--- Library Books ---" << std::endl;
    for (const auto& book : books) {
        std::cout << "Title: " << book.title << std::endl;
        std::cout << "Author: " << book.author << std::endl;
        std::cout << "ISBN: " << book.isbn << std::endl;
        std::cout << "Borrowed: " << (book.isBorrowed ? "Yes" : "No") << std::endl;
        std::cout << "---------------------" << std::endl;
    }
    std::cout << "Total books: " << totalBooks << std::endl;
}

} // namespace Library
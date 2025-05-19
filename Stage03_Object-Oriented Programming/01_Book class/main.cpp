#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    // Default constructor
    Book() : title(""), author(""), year(0) {}
    

    // Parameterized constructor
    Book(string title, string author, int year) : title(title), author(author), year(year) {}

    // Copy constructor (optional, but good practice for classes managing resources)
    Book(const Book& other) : title(other.title), author(other.author), year(other.year) {}

    // Assignment operator (optional, but good practice for classes managing resources)
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            year = other.year;
        }
        return *this;
    }

    // Display method
    void display() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
    }

private:
    string title;
    string author;
    int year;
};

int main() {
    // Using the default constructor
    Book book1;
    cout << "Book 1:" << endl;
    book1.display();
    std::cout << endl;

    // Using the parameterized constructor
    Book book2("C++ How to Program  An Objects", "Paul J. Deitel and Harvey M. Deitel", 2023);
    cout << "Book 2:" << endl;
    book2.display();
    cout << endl;

    // Using the copy constructor
    Book book3 = book2;
    cout << "Book 3 (copy of Book 2):" << endl;
    book3.display();
    cout << endl;

    // Using the assignment operator
    Book book4;
    book4 = book1;
    cout << "Book 4 (assigned from Book 1):" << endl;
    book4.display();
    cout << endl;

    return 0;
}
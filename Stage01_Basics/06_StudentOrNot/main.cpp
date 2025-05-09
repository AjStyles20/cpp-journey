#include <iostream>
#include <string>


using namespace std;

int main() {
    string name;
    int age = 0;    
    double gpa = 0.0; 

    cout << "Enter your name: ";
    cin >> name; 

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your GPA: ";
    cin >> gpa;
    if (!name.empty()) {
        cout << "Hello " << name << endl;
    } else {
        
        cout << "Hello World (name was not provided)" << endl;
    }

    if (age > 0) {
        cout << "You are " << age << " years old." << endl;
    } else {
     
        cout << "Invalid or empty age entered (age is not positive)." << endl;
    }

    if (gpa > 0) {
        
        cout << "Your GPA is " << gpa << endl;
    } else {
        
        cout << "Invalid or empty GPA entered (GPA is not positive)." << endl;
    }

    if (age > 0 && gpa > 0) {
        cout << "You are a student." << endl;
    } else {
        
        cout << "You are not a student (due to age or GPA not being positive, possibly from empty/invalid input)." << endl;
    }

    return 0;
}
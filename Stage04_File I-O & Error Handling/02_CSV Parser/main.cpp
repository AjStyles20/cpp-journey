#include <iostream>    // For console input/output
#include <fstream>     // For file operations
#include <sstream>     // For string stream processing
#include <vector>      // For dynamic arrays
#include <string>      // For string operations

using namespace std;

// Structure to hold student record data
struct StudentRecord{
public:
    // Constructor to initialize all fields
    StudentRecord(
        string id,
        string firstName,
        string lastName,
        int age,
        string phoneNumber,
        double gpa
    ){
        Id = id;
        FirstName = firstName;
        LastName = lastName;
        PhoneNumber = phoneNumber;
        Age = age;
        Gpa = gpa;
    }

    // Display the student record to the console
    void display(){
        cout <<"  Student ID: " << Id << endl;
        cout <<"  First Name: " << FirstName << endl;
        cout <<"   Last Name: " << LastName << endl;
        cout <<"Phone Number: " << PhoneNumber << endl;
        cout <<"         Age: " << Age << endl;
        cout <<"         GPA: " << Gpa << endl;
        cout << endl;
    }

    // Member variables
    string Id;
    string FirstName;
    string LastName;
    string PhoneNumber;
    int Age;
    double Gpa;

};


int main(int argc, char** argv){

    ifstream inputFile;
    inputFile.open("Student_Record.csv"); // Open the CSV file for reading
    vector<StudentRecord> students;       // Vector to store all student records
    string line = " ";
    getline(inputFile, line);             // Skip the header line
    line = " ";
    // Read each line from the CSV file
    while (getline(inputFile, line)){
        
        string studentId;
        string lastName;
        string firstName;
        int age;
        string phone;
        double gpa;
        string tempString;

        stringstream inputString(line);   // Create a stringstream from the line

        // Parse each field separated by commas
        getline(inputString, studentId, ',');
        getline(inputString, lastName, ',');
        getline(inputString, firstName, ',');

        // Get the age as a string, then convert to int
        getline(inputString, tempString, ',');
        age = atoi(tempString.c_str());

        getline(inputString, phone, ',');

        // Get the GPA as a string, then convert to double
        tempString = " ";
        getline(inputString, tempString);
        gpa = atoi(tempString.c_str());

        // Create a StudentRecord object and add to the vector
        StudentRecord student(studentId, lastName,
             firstName, age, phone, gpa);

        students.push_back(student);

        line = " ";
    }

    // Display all student records
    for (auto student : students){
        student.display();
    }

    return 0;
}
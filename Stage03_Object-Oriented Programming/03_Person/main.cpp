#include <iostream>
#include <string>

using namespace std;

//Base Class (Person)
class Person {
protected:  // Accessible in derived classes
    string name;
    int age;
public:
    Person(const string &name, int age) : name(name), age(age) {}
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

 //Derived Class (Student)
class Student : public Person {  // Public inheritance
    char grade;
public:
    Student(const string &name, int age, char grade) 
        : Person(name, age), grade(grade) {}
    
    void study() const {
        cout << name << " is studying..." << endl;
    }
    
    char getGrade() const { 
        return grade; 
    }
};

 //Derived Class (Teacher)
class Teacher : public Person {
    string subject;
public:
    Teacher(const string &name, int age, const string &subject)
        : Person(name, age), subject(subject) {}
    
    void teach() const {
        cout << name << " is teaching " << subject << endl;
    }
    
    string getSubject() const { return subject; }
};

//Main Function (Usage Example)
int main() {
    Person person("Alice", 25);
    Student student("Bob", 20, 'B');
    Teacher teacher("Carol", 35, "Math");

    person.display();
    student.display();
    student.study();
    teacher.display();
    teacher.teach();

    return 0;
}
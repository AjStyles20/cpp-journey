#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(const string &name, int age) : name(name), age(age) {}
    
    // Virtual function (can be overridden)
    virtual void describe() const {
        cout << "Person: " << name << " (Age: " << age << ")" << endl;
    }

    // Pure virtual function (makes Person abstract)
    // virtual void role() const = 0;
};

class Student : public Person {
    char grade;
public:
    Student(const string &name, int age, char grade) 
        : Person(name, age), grade(grade) {}
    
    // Override describe() for Student
    void describe() const override {
        cout << "Student: " << name << " (Age: " << age << ", Grade: " << grade << ")" << endl;
    }
    
    void study() const {
        cout << name << " is studying..." << endl;
    }
};

class Teacher : public Person {
    string subject;
public:
    Teacher(const string &name, int age, const string &subject)
        : Person(name, age), subject(subject) {}
    
    // Override describe() for Teacher
    void describe() const override {
        cout << "Teacher: " << name << " (Age: " << age << ", Subject: " << subject << ")" << endl;
    }
    
    void teach() const {
        cout << name << " is teaching " << subject << endl;
    }
};

int main() {
    // Using base class pointers for polymorphic behavior
    Person* person1 = new Person("Alice", 25);
    Person* student1 = new Student("Bob", 20, 'A');
    Person* teacher1 = new Teacher("Carol", 35, "Math");

    // Calls the correct overridden describe() at runtime
    person1->describe();   
    student1->describe();  
    teacher1->describe();  

    // Cleanup
    delete person1;
    delete student1;
    delete teacher1;

    return 0;
}
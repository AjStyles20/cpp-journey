#include <iostream>
using namespace std;

int main() {
    int Input1, Input2;
    bool result;
    cout << "Enter first integers(Number): ";
    cin >> Input1; 
    cout << "Enter second integers(Number): ";
    cin >> Input2;
    
    cout << "You entered: " << Input1 << " and " << Input2 << endl;


    cout << "Arithmetic Operators:" << endl;
    cout << "Input1 + Input2 = " << Input1 + Input2 << endl;
    cout << "Input1 - Input2 = " << Input1 - Input2 << endl;
    cout << "Input1 * Input2 = " << Input1 * Input2 << endl;
    cout << "Input1 / Input2 = " << Input1 / Input2 << endl;
    cout << "Input1 % Input2 = " << Input1 % Input2 << endl;

    cout << "\nRelational Operators:" << endl;
    cout << "Input1 == Input2: " << (Input1 == Input2) << endl;
    cout << "Input1 != Input2: " << (Input1 != Input2) << endl;
    cout << "Input1 > Input2: " << (Input1 > Input2) << endl;
    cout << "Input1 < Input2: " << (Input1 < Input2) << endl;

    cout << "\nLogical Operators:" << endl;
    result = (Input1 > 0 && Input2 > 0);
    cout << "Input1 > 0 && Input2 > 0: " << result << endl;
    result = (Input1 < 0 || Input2 > 0);
    cout << "Input1 < 0 || Input2 > 0: " << result << endl;
    result = !(Input1 < 0);
    cout << "!(Input1 < 0): " << result << endl;

    cout << "\nAssignment and Increment/Decrement:" << endl;
    Input1 += 2;
    cout << "Input1 += 2: " << Input1 << endl;
    Input1++;
    cout << "Input1++: " << Input1 << endl;
    --Input2;
    cout << "--Input2: " << Input2 << endl;

    return 0;
}

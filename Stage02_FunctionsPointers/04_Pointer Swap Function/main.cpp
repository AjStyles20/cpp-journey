//C++ program to illustrate pointers and functions
#include <iostream>
using namespace std;

// The function doesn't need to return anything, so it should be void
void swapping(int *x, int *y) {  // Changed return type from int to void
    int temp;
    
    temp = *x;
    *x = *y;
    *y = temp;  
    // No return statement needed since it's void
}

int main() {
    int a = 0, b = 0;
    
    cout << "\tEnter the value for a & b: ";
    cin >> a >> b;
    
    cout << "\n\n\tBefore swapping the values, a = " << a << " and b = " << b << "\n";
    swapping(&a, &b);

    cout << "\n\tAfter swapping, a = " << a << " and b = " << b << "\n";  // Added space after "a = " for better formatting
    return 0;
}
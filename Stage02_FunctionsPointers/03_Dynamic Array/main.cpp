/*
#include <iostream>

using namespace std;

int main(){

    int size;
    int sum;
    cout<<"Enter the size of your array: ";
    cin>> size;

    int myArray[size]; 
    // The size of the array must be known at compile time.
    for(int i = 0; i < size; i++){
        cout<<"Array["<< i << "]";
        cin>> myArray[i];

    }
    for(int i = 0; i < size; i++){
        cout<<myArray[i]<< " ";
         sum += myArray[i];
    }


    cout<<endl<<"The sum of the numbers you entered is: "<< sum;
    return 0;
}

*/



#include <iostream>
#include <string>

using namespace std;

int main() {
    int rows;
    int cols;
    int **Table = nullptr; // Initialize Table to nullptr
    string choose;

    cout << "Enter your number of rows: ";
    cin >> rows;

    cout << "Enter your number of cols: ";
    cin >> cols;

    if (rows <= 0 || cols <= 0) {
        cout << "Invalid dimensions." << endl;
        return 1;
    }

    // Dynamically allocate the 2D array
    Table = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        Table[i] = new int[cols];
    }

    cout << "Enter the elements of the " << rows << "x" << cols << " table:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Enter element at row " << i + 1 << ", column " << j + 1 << ": ";
            cin >> Table[i][j]; // Read into the dynamically allocated Table
        }
    }

    if (rows > 1 && cols > 2) {
        Table[1][2] = 88;
    }

    cout << "Do you want to delete your table/array (Enter Y/N)?: ";
    cin >> choose;

    if (choose == "Y" || choose == "y") {
        for (int i = 0; i < rows; ++i) {
            delete[] Table[i];
        }
        delete[] Table;
        Table = nullptr;
        cout << "Your table/array was successfully deleted!" << endl;
    } else if (choose == "N" || choose == "n") {
        cout << "Your table is still active." << endl;
    } else {
        cout << "OK." << endl;
    }

    return 0;
}
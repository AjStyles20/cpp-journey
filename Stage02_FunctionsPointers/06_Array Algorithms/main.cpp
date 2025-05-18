#include <iostream>
using namespace std;

void bubble_sort(double UserInputs[], int Numbers);

int main() {
    int Numbers;
    cout << "How many numbers would you like to enter? ";
    cin >> Numbers;

    double *UserInputs = new double[Numbers];  // Allocation
    
    // Input
    for(int i = 0; i < Numbers; i++) {
        cout << "Enter number " << i + 1 << ": ";
        cin >> UserInputs[i];
    }

    // Output
    cout << "You entered: [";
    for(int i = 0; i < Numbers; i++) {
        cout << UserInputs[i];
        if(i != Numbers - 1) cout << ", ";
    }
    cout << "]" << endl;

    
    // Show sorted array
    bubble_sort(UserInputs, Numbers);
    cout << "Your sorted elements: [";
    for(int i = 0; i < Numbers; i++){
        cout<< UserInputs[i];
        if(i != Numbers - 1) cout << ", ";
    }
     cout << "]" << endl;

    delete[] UserInputs;  // Cleanup
    return 0;
}

void bubble_sort(double UserInputs[], int Numbers){
    bool swapped;
    int i = 0;
    do{
        swapped = false;
        for(int j = 0; j < Numbers - 1 - i; j++){
            if(UserInputs[j] > UserInputs[j +1]){
                int swap = UserInputs[j];
                UserInputs[j] = UserInputs[j + 1];
                UserInputs[j + 1] = swap;
                swapped = true;
            }
        }
        i++;
    }while (swapped);
    
}
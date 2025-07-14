
#include <iostream>

using namespace std;

int main(){

    double input;
    cout<<"The grade ranges from 0 to 100"<< endl;

    cout<<"Enter your the grade: ";
    cin>> input;

    if(input >= 90 && input <= 100){
        cout<<"Your grade is: "<<"A+";
    }
    else if(input >= 80 && input <= 89){
        cout<<"Your grade is: "<<"A";
    }
    else if(input >= 70 && input <= 79){
        cout<<"Your grade is: "<<"B+";
    }
    else if(input >= 60 && input <= 69){
        cout<<"Your grade is: "<<"B";
    }
    else if(input >= 50 && input <= 59){
        cout<<"Your grade is: "<<"C";
    }
    else if(input >= 40 && input <= 49){
        cout<<"Your grade is: "<<"D";
    }
    else if(input >= 30 && input <= 39){
        cout<<"Your grade is: "<<"E";
    }
    else if(input >= 0 && input <= 29){
        cout<<"Your grade is: "<<"F";
    }
    else{
        cout<<"Enter a valide digit for grading.";
    }

    return 0;
}




/*
#include <iostream>
#include <string>

using namespace std;

int main() {
    double input;
    cout << "The grade ranges from 0 to 100" << endl;
    cout << "Enter your the grade: ";
    cin >> input;

    if (input >= 0 && input <= 100) {
        int gradeCategory = static_cast<int>(input / 10);

        switch (gradeCategory) {
            case 10: // 100
            case 9:  // 90-99
                cout << "Your grade is: A+" << endl;
                break;
            case 8:  // 80-89
                cout << "Your grade is: A" << endl;
                break;
            case 7:  // 70-79
                cout << "Your grade is: B+" << endl;
                break;
            case 6:  // 60-69
                cout << "Your grade is: B" << endl;
                break;
            case 5:  // 50-59
                cout << "Your grade is: C" << endl;
                break;
            case 4:  // 40-49
                cout << "Your grade is: D" << endl;
                break;
            case 3:  // 30-39
                cout << "Your grade is: E" << endl;
                break;
            case 2:  // 20-29
            case 1:  // 10-19
            case 0:  // 0-9
                cout << "Your grade is: F" << endl;
                break;
            default:
                cout << "Error in grade calculation (should not happen for valid input)" << endl;
                break;
        }
    } else {
        cout << "Enter a valid digit for grading." << endl;
    }

    return 0;
}
*/
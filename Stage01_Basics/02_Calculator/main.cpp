#include <iostream>
#include <cmath>

using namespace std;

int main(){
    string Operation;
    double number1, number2;

    //Handles user inputs
    cout <<"Enter your first number: ";
    cin >>number1;

    cout <<"Choose an operator(+, -, *, /, ^, %): ";
    cin >>Operation;

    cout <<"Enter your second number: ";
    cin >>number2;

    //Handles conditions or user choices
    if(Operation == "+"){
        cout <<"Your answer is: "<<number1 + number2;
    }
    else if (Operation == "-"){
        cout <<"Your answer is: "<<number1 - number2;
    }
    else if (Operation == "*"){
        cout <<"Your answer is: "<<number1 * number2;
    }
    else if (Operation == "/"){
        cout <<"Your answer is: "<<number1 / number2;
    }
    else if (Operation == "^"){
        cout <<"Your answer is: "<<pow(number1, number2);
    }
    else if (Operation == "%"){
        cout <<"Your answer is: "<<fmod(number1, number2);
    }
    else{
        cout <<"Invalid operator!";
    }
    
    return 0;
}
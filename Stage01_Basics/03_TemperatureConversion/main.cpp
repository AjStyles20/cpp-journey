#include <iostream>
#include <string>

using namespace std;

int main(){
    double Fahrenheit;
    double Celsius;
    string UserInput;


    cout<<"What do you want to convert(Enter F/f for Fahrenheit to Celsius, Or enter C/c for Celsius to Fahrenheit) ?";
    cin>> UserInput;

   if(UserInput == "F" || UserInput == "f"){
    cout<<"Enter your digit (Fahrenheit)";
    cin>> Fahrenheit;
    cout<< "C =" <<(Fahrenheit - 32.0)*5.0/9.0 << endl;

   }
   else if(UserInput == "C" || UserInput == "c"){
    cout<<"Enter your digit (Celsius)";
    cin>> Celsius;
    cout<< "F ="<< (Celsius * 9.0/5.0) + 32.0 << endl;
   }else{
    cout<< "Follow the instruction";
   }
    return 0;
}
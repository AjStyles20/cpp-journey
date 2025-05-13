            /*           Factorial Of A Number Using While Loop       */

/*
#include <iostream>

using namespace std;

int main(){
    int input;
    int Fact;

    cout<<"Enter your number: ";
    cin>>input;

    Fact = input;

    while(input > 1){
        input--;
        Fact = Fact * input;
    }
    cout<<Fact;

    return 0;
}

*/


            /*           Factorial Of A Number Using For Loop       */

/*
#include <iostream>

using namespace std;

int main(){
    int n;
    int fact =1;

    cout<< "Enter your number: ";
    cin>>n;

    for(int i = 1; i <= n; i++){
        fact = fact * i;
    }
    cout<< fact;
}
*/



        /*           Factorial Of A Number Using Function        */

#include <iostream>

using namespace std;

int factorial(int x){
    int fact = 1;

    for(int i = 1; i <= x; i++) {
        fact = fact * i;
    }
    return fact;
}

int main(){
    int n;

    cout<<"Enter your number: ";
    cin>> n;

    cout << factorial(n);

    return 0;
}
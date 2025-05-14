#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string MyInput = "Am a man of virtue, lived in the land of grace and prosperity. Ah ah ahh!!!!\n";
    string UserInput;
    reverse(MyInput.begin(), MyInput.end());
    cout<<MyInput<<endl;

    cout<<"Now, Your turn!!\n";
    cin>>UserInput;

    reverse(UserInput.begin(), UserInput.end());
    cout<< UserInput;
    return 0;
}
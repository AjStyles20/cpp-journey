#include <iostream>
#include <iomanip>

using namespace std;

// BankAccount class encapsulates all banking operations and data
class BankAccount {
private:
    double balance;  // Private member variable to store the balance

public:
    // Constructor with default initial balance of 0
    BankAccount(double initialBalance = 0) : balance(initialBalance) {}

    // Displays the current balance (const because it doesn't modify the object)
    void showBalance() const {
        cout << "Your balance is: $" << setprecision(2) << fixed << balance << "\n";
    }

    // Handles deposit operation
    void deposit() {
        double amount = 0;
        cout << "Enter amount to be deposited: ";
        cin >> amount;

        if (amount > 0) {
            balance += amount;  // Add amount to balance if valid
            cout << "Deposit successful.\n";
        } else {
            cout << "That's not a valid amount.\n";
        }
    }

    // Handles withdrawal operation
    void withdraw() {
        double amount = 0;
        cout << "Enter amount to be withdrawn: ";
        cin >> amount;

        if (amount > balance) {
            cout << "Insufficient funds.\n";  // Can't withdraw more than balance
        } else if (amount < 0) {
            cout << "That's not a valid amount.\n";  // Negative amounts not allowed
        } else {
            balance -= amount;  // Subtract amount from balance if valid
            cout << "Withdrawal successful.\n";
        }
    }
};

int main() {
    BankAccount account;  // Create a BankAccount object with default 0 balance
    int choice = 0;       // Variable to store user's menu choice

    do {
        // Display menu options
        cout << "******************************\n";
        cout << "Enter your choice:\n";
        cout << "******************************\n";
        cout << "1. Show Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Exit\n";
        cin >> choice;

        // Clear any error flags and flush the input buffer
        cin.clear();
        fflush(stdin);
        
        // Process user's choice
        switch (choice) {
            case 1:
                account.showBalance();
                break;
            case 2:
                account.deposit();
                account.showBalance();
                break;
            case 3:
                account.withdraw();
                account.showBalance(); 
                break;
            case 4:
                cout << "Thanks for visiting!\n";
                break;
            default: 
                cout << "Invalid choice\n";
        } 
    } while (choice != 4);  // Continue until user chooses to exit
    
    return 0;
}
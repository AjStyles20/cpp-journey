# 02_BankAccountClass

## Project Description
This project demonstrates object-oriented programming principles in C++ by implementing a simple bank account system. The program features a `BankAccount` class with encapsulated data and methods for deposits, withdrawals, and balance checking.

## Learning Objectives
- Implement encapsulation using private and public access modifiers
- Create and use class member functions
- Understand constructor implementation
- Practice object-oriented programming fundamentals
- Develop interactive console applications
- Handle user input validation

## Technologies Used
- **C++** (GNU g++)
- **Visual Studio Code**
  - C/C++ extension by Microsoft
  - Integrated terminal

## How to Run
1. Open the terminal in the project directory
2. Compile the program using:
   ```bash
   g++ main.cpp -o BankAccountClass
   ```
3. Run the compiled executable:
   - Windows:
     ```bash
     .\BankAccountClass.exe
     ```
   - Unix-based systems:
     ```bash
     ./BankAccountClass
     ```

## How to Use
1. Run the program
2. Select an option from the menu:
   - `1` to check your balance
   - `2` to deposit money
   - `3` to withdraw money
   - `4` to exit
3. Follow the on-screen prompts for deposits/withdrawals
4. View your updated balance after each transaction

## Example Output
```
******************************
Enter your choice:
******************************
1. Show Balance
2. Deposit Money
3. Withdraw Money
4. Exit
2
Enter amount to be deposited: 500
Deposit successful.
Your balance is: $500.00
******************************
Enter your choice:
******************************
1. Show Balance
2. Deposit Money
3. Withdraw Money
4. Exit
3
Enter amount to be withdrawn: 200
Withdrawal successful.
Your balance is: $300.00
******************************
Enter your choice:
******************************
1. Show Balance
2. Deposit Money
3. Withdraw Money
4. Exit
4
Thanks for visiting!
```

## Key Concepts Demonstrated
- Encapsulation through private member variables
- Public member functions as class interface
- Constructor with default parameter
- Input validation for financial transactions
- Menu-driven console application
- Formatted currency output

## Notes
- The account starts with a zero balance by default
- Negative amounts are automatically rejected
- Withdrawals exceeding balance are prevented
- Balance is displayed with 2 decimal places
- Includes input buffer clearing for robust operation

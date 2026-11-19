#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

const int userCount = 3;

// The arrays at the same index belong to the same user.
string names[3] = {"Thando Mkhize", "Thato Motaung", "Keletso Mofokeng"};
int accountNumbers[3] = {2001, 2002, 2003};
int pins[3] = {1234, 9876, 3456};
double balances[3] = {6500.00, 2250.00, 3800.00};

void displayMenu();
int findAccount(int accountNumber);
int getValidAmountChoice();
void deposit(int userIndex);
void withdraw(int userIndex);
void sendCash(int userIndex);
void checkBalance(int userIndex);
void showUsers();
void clearBadInput();

int main()
{
    int accountNumber;
    int pin;
    int userIndex = -1;

    cout << "===== GCC BANK =====" << endl;
    cout << "Users and account numbers : " << endl;
    showUsers();

    cout << "\nLog in with your account number: " << endl;
    while (!(cin >> accountNumber))
        {
          clearBadInput();
          cout << "Please enter a number for the account number: " << endl;
        }

    userIndex = findAccount(accountNumber);
    if (userIndex == -1)
        {
          cout << "Account not found. Goodbye." << endl;
          return 0;
        }

    cout << "Enter your 4-digit PIN: " << endl;
    while (!(cin >> pin))
        {
          clearBadInput();
          cout << "Please enter numbers for your PIN: " << endl;
        }

    if (pin != pins[userIndex])
        {
          cout << "Incorrect PIN. Goodbye." << endl;
          return 0;
        }

    cout << "Welcome, " << names[userIndex] << endl;

    int choice;
    do {
        displayMenu();
        cout << "Enter choice: " << endl;
        while (!(cin >> choice))
            {
              clearBadInput();
              cout << "Invalid input. Enter a menu number from 1 to 5: " << endl;
            }

        switch (choice)
        {
            case 1:
                deposit(userIndex);
                break;
            case 2:
                withdraw(userIndex);
                break;
            case 3:
                sendCash(userIndex);
                break;
            case 4:
                checkBalance(userIndex);
                break;
            case 5:
                cout << "Thank you for using GCC Bank. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please choose a number from 1 to 5." << endl;
        }
    } while (choice != 5);

    return 0;
}

void displayMenu()
{
    cout << "===== GCC BANK MENU =====" << endl;
    cout << "Enter 1 to Deposit" << endl;
    cout << "Enter 2 to Withdraw" << endl;
    cout << "Enter 3 to Send Cash" << endl;
    cout << "Enter 4 to Check Balance" << endl;
    cout << "Enter 5 to Exit" << endl;
}

int findAccount(int accountNumber)
{
    for (int i = 0; i < userCount; i++)
        {
         if (accountNumbers[i] == accountNumber)
          {
              return i;
          }
        }
    return -1;
}

void deposit(int userIndex)
{
    double amount;
    cout << "Enter amount to deposit: R" << endl;
    while (!(cin >> amount))
        {
          clearBadInput();
          cout << "Invalid amount. Enter a number greater than 0: R" << endl;
        }

    if (amount <= 0)
        {
          cout << "Deposit must be more than R0.00" << endl;
        }
    else
        {
          balances[userIndex] += amount;
          cout << fixed << setprecision(2) << "Deposit successful. New balance: R" << balances[userIndex] << endl;
        }
}

void withdraw(int userIndex)
{
    double amount;
    cout << "Enter amount to withdraw: R" << endl;
    while (!(cin >> amount))
        {
          clearBadInput();
          cout << "Invalid amount. Enter a number greater than 0: R" << endl;
        }

    if (amount <= 0)
        {
          cout << "Withdrawal must be more than R0.00" << endl;
        }
    else if (amount > balances[userIndex])
        {
          cout << "Insufficient funds. Your balance is R" << fixed << setprecision(2) << balances[userIndex] << endl;
        }
    else
        {
          balances[userIndex] -= amount;
          cout << fixed << setprecision(2) << "Withdrawal successful. New balance: R" << balances[userIndex] << endl;
        }
}

void sendCash(int userIndex)
{
    int recipientAccount;
    cout << "Enter recipient account number: " << endl;
    while (!(cin >> recipientAccount))
        {
          clearBadInput();
          cout << "Invalid account number. Enter a number: " << endl;
        }

    int recipientIndex = findAccount(recipientAccount);
    if (recipientIndex == -1)
        {
          cout << "Recipient account does not exist" << endl;
          return;
        }
    if (recipientIndex == userIndex)
        {
          cout << "You cannot send cash to your own account" << endl;
          return;
        }

    double amount;
    cout << "Enter amount to send: R" << endl;
    while (!(cin >> amount))
        {
          clearBadInput();
          cout << "Invalid amount. Enter a number greater than 0: R" << endl;
        }

    if (amount <= 0)
        {
          cout << "Send amount must be more than R0.00" << endl;
        }
    else if (amount > balances[userIndex])
        {
          cout << "Insufficient funds. Your balance is R" << fixed << setprecision(2) << balances[userIndex] << endl;
        } else
          {
             balances[userIndex] -= amount;
             balances[recipientIndex] += amount;
             cout << fixed << setprecision(2) << "R" << amount << " sent successfully to " << names[recipientIndex] << endl;
             cout << "Your new balance is R" << balances[userIndex] << endl;
          }
}

void checkBalance(int userIndex)
{
    cout << fixed << setprecision(2) << "Account holder: " << names[userIndex] << "\nAccount number: " << accountNumbers[userIndex]
         << "\nCurrent balance: R" << balances[userIndex] << endl;
}

void showUsers()
{
    for (int i = 0; i < userCount; i++)
        {
          cout << names[i] << " - Account " << accountNumbers[i] << endl;
        }
}

void clearBadInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max());
}



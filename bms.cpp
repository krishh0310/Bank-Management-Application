#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    // Create Account
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        cout << "\nAccount Created Successfully!\n";
    }

    // Display Account Details
    void displayAccount() const {
        cout << "\n===== Account Details =====\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << name << endl;
        cout << "Balance        : ₹" << balance << endl;
    }

    // Deposit Money
    void deposit(float amount) {
        balance += amount;
        cout << "₹" << amount << " Deposited Successfully!\n";
    }

    // Withdraw Money
    void withdraw(float amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
        } else {
            balance -= amount;
            cout << "₹" << amount << " Withdrawn Successfully!\n";
        }
    }

    // Get Account Number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Get Balance
    float getBalance() const {
        return balance;
    }
};

// 🔹 Create New Account
void createNewAccount() {
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    file.write((char*)&acc, sizeof(acc));

    file.close();

    cout << "Account Saved Successfully!\n";
}

// 🔹 Display All Accounts
void displayAllAccounts() {
    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    if (!file) {
        cout << "No Records Found!\n";
        return;
    }

    while (file.read((char*)&acc, sizeof(acc))) {
        acc.displayAccount();
    }

    file.close();
}

// 🔹 Search Account
void searchAccount() {
    int accNo;
    bool found = false;

    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    cout << "Enter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccountNumber() == accNo) {
            acc.displayAccount();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!\n";
    }

    file.close();
}

// 🔹 Deposit Money
void depositMoney() {
    int accNo;
    float amount;
    bool found = false;

    BankAccount acc;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc))) {

        if (acc.getAccountNumber() == accNo) {

            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            acc.deposit(amount);

            int pos = -1 * sizeof(acc);

            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!\n";
    }

    file.close();
}

// 🔹 Withdraw Money
void withdrawMoney() {
    int accNo;
    float amount;
    bool found = false;

    BankAccount acc;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc))) {

        if (acc.getAccountNumber() == accNo) {

            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            acc.withdraw(amount);

            int pos = -1 * sizeof(acc);

            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!\n";
    }

    file.close();
}

// 🔹 Check Balance
void checkBalance() {
    int accNo;
    bool found = false;

    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    cout << "Enter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc))) {

        if (acc.getAccountNumber() == accNo) {

            cout << "\nCurrent Balance: ₹" << acc.getBalance() << endl;

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "Account Not Found!\n";
    }

    file.close();
}

// 🔹 Main Function
int main() {

    int choice;

    do {

        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";

        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Check Balance\n";
        cout << "7. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                createNewAccount();
                break;

            case 2:
                displayAllAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                depositMoney();
                break;

            case 5:
                withdrawMoney();
                break;

            case 6:
                checkBalance();
                break;

            case 7:
                cout << "Thank You for Using Bank Management System!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}

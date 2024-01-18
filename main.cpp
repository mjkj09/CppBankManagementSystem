#include <iostream>
#include "bank.h"

using namespace std;

int main() {
    while (true) {
        Bank MunikBank;


        cout << "Welcome to C++ Bank Management System!" << endl;
        cout << "Choose one of the following options:" << endl << endl;

        cout << "1. I already have an account" << endl;
        cout << "2. I don't have an account yet" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cout << "Enter your choice:";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                cout << "Enter your account number: ";
                int accountNumber;
                cin >> accountNumber;
                cout << endl;
                Account init(accountNumber, 500000);

                MunikBank.addAccount(init);

                try {
                    Account account = MunikBank.findAccount(accountNumber);
                    cout << "Account found: " << account << endl;
                } catch (const AccountNotFoundException &e) {
                    cout << "Account not found." << endl;
                }

                break;
            }
            case 2:
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

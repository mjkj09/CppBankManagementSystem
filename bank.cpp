//
// Created by Mikołaj on 17.01.2024.
//

#include "bank.h"

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        throw invalid_argument("Invalid amount");
    }
}

void Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    } else {
        throw invalid_argument("Invalid amount");
    }
}

double Account::getBalance() const {
    return balance;
}

ostream &operator<<(ostream &os, const Account &account) {
    os << "Account ID: " << account.id << setprecision(2) << ", Balance: " << account.balance;
    return os;
}

int Account::getId() const {
    return id;
}


void SavingsAccount::deposit(double amount) {
    Account::deposit(amount);
    balance += (balance * rateOfInterest * years) * (1 - taxRate);
}

double SavingsAccount::getRateOfInterest() const {
    return rateOfInterest;
}

ostream &operator<<(ostream &os, const SavingsAccount &account) {
    os << static_cast<const Account &>(account) << ", Rate of interest: " << account.getRateOfInterest() << ", Years: "
       << account.years;
    return os;
}

//TODO: check Bank methods + documentation

void Bank::add_account(Account &account) {
    accounts.push_back(&account);
}

void Bank::remove_account(int id) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if ((*it)->getId() == id) {
            accounts.erase(it);
            break;
        }
    }
    throw runtime_error("Account not found");
}

void Bank::display_all_accounts() const {
    for (const auto &account: accounts) {
        cout << account << endl;
    }
}

Account &Bank::find_account(int id) const {
    for (const auto &account: accounts) {
        if ((*account).getId() == id) {
            return *account;
        }
    }
    throw runtime_error("Account not found");
}
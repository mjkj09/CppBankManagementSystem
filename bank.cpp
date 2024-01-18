//
// Created by Mikołaj on 17.01.2024.
//

#include "bank.h"


void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        throw InvalidAmountException();
    }
}

void Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
    } else {
        throw InvalidAmountException();
    }
}

double Account::getBalance() const {
    return balance;
}

ostream &operator<<(ostream &os, const Account &account) {
    os << "Account ID: " << account.id << setprecision(2) << fixed << ", Balance: " << account.balance;
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

//TODO: idk if emplace_back works

void Bank::addAccount(Account &account) {
    accounts.emplace_back(&account);
}

void Bank::removeAccount(int id) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if ((*it)->getId() == id) {
            accounts.erase(it);
            return;
        }
    }
    throw AccountNotFoundException();
}

void Bank::displayAllAccounts() const {
    for (const auto &account: accounts) {
        cout << *account << endl;
    }
}

Account &Bank::findAccount(int id) const {
    for (const auto &account: accounts) {
        if (account->getId() == id) {
            return *account;
        }
    }
    throw AccountNotFoundException();
}

Bank::~Bank() {
    for (const auto &account: accounts) {
        delete account;
    }
    accounts.clear();
}

Bank::Bank(const Bank &other) {
    for (const auto &account: other.accounts) {
        accounts.emplace_back(account);
    }
}

Bank &Bank::operator=(const Bank &other) {
    if (this != &other) {
        for (const auto &account: accounts) {
            delete account;
        }
        accounts.clear();
        for (const auto &account: other.accounts) {
            accounts.emplace_back(account);
        }
    }
    return *this;
}

void TransactionRecorder::recordTransaction(double amount, const string &transactionType) const {
    string filename = to_string(accountId) + ".csv";
    ofstream file(filename, ios::out | ios::app);

    if (!file.is_open()) {
        throw FileFailedException();
    }

    file << amount << ";" << transactionType << endl;
    file.close();
}

void TransactionRecorder::record_deposit(double amount) {
    recordTransaction(amount, "Deposit");
}

void TransactionRecorder::record_withdrawal(double amount) {
    recordTransaction(-amount, "Withdrawal");
}


//
// Created by Mikołaj on 17.01.2024.
//

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

#ifndef CPPBANKMANAGEMENTSYSTEM_BANK_H
#define CPPBANKMANAGEMENTSYSTEM_BANK_H

class Account {
public:
    Account() = default;

    Account(int id, double balance) : id(id), balance(balance) {}

    virtual ~Account() = default; //zeby destruktor dzialal w odpowiedniej kolejnosci

    virtual void deposit(double amount);

    virtual void withdraw(double amount);

    [[nodiscard]] double getBalance() const;

    friend ostream &operator<<(ostream &os, const Account &account);

    [[nodiscard]] virtual int getId() const;

protected:
    int id{};
    double balance{};
};

class SavingsAccount : public Account {
public:
    SavingsAccount() = default;

    SavingsAccount(int id, double balance, double rateOfInterest, int years)
            : Account(id, balance), rateOfInterest(rateOfInterest), years(years) {};

    ~SavingsAccount() override = default;

    void deposit(double amount) override;

    [[nodiscard]] double getRateOfInterest() const;

    friend ostream &operator<<(ostream &os, const SavingsAccount &account);

    double taxRate = 0.19;

private:
    double rateOfInterest{};
    int years{};
};

class Bank {
public:
    Bank() = default;

    void add_account(Account &account);

    void remove_account(int id);

    void display_all_accounts() const;

    [[nodiscard]] Account &find_account(int id) const;

private:
    vector<Account *> accounts;
};

#endif //CPPBANKMANAGEMENTSYSTEM_BANK_H

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

/**
 * This class represents a bank account.
 * It provides methods to deposit and withdraw money,
 * as well as retrieve the account balance. It also allows retrieving the account ID.
 */
class Account {
public:
    /**
     * Default constructor.
     */
    Account() = default;

    /**
     * Constructor that initializes the account with the given ID and balance.
     *
     * @param id The ID of the account.
     * @param balance The initial balance of the account.
     */
    Account(int id, double balance) : id(id), balance(balance) {};

    /**
     * Virtual destructor.
     */
    virtual ~Account() = default;

    /**
     * Deposits the specified amount into the account.
     *
     * @param amount The amount to deposit.
     */
    virtual void deposit(double amount);

    /**
     * Withdraws the specified amount from the account.
     *
     * @param amount The amount to withdraw.
     */
    void withdraw(double amount);

    /**
     * Returns the current balance of the account.
     *
     * @return The balance of the account.
     */
    [[nodiscard]] double getBalance() const;

    /**
     * Returns the ID of the account.
     *
     * @return The ID of the account.
     */
    [[nodiscard]] int getId() const;

    /**
     * Overloads the \<\< operator for outputting the account information.
     * @param os The output stream
     * @param account The account to output
     * @return The output stream
     */
    friend ostream &operator<<(ostream &os, const Account &account);

protected:
    /**
     *  An integer representing the account ID.
     */
    int id{};

    /**
     * A double representing the account balance.
     */
    double balance{};
};

/**
 * This class inherits from the Account class
 * and represents a savings account. It adds additional
 * fields and methods specific to savings accounts.
 */
class SavingsAccount : public Account {
public:
    /**
     * Default constructor.
     */
    SavingsAccount() = default;

    /**
   * Constructor that initializes the savings account with the given parameters.
   *
   * @param id The ID of the account.
   * @param balance The initial balance of the account.
   * @param rateOfInterest The rate of interest for the savings account.
   * @param years The number of years the account would be active.
   */
    SavingsAccount(int id, double balance, double rateOfInterest, int years)
            : Account(id, balance), rateOfInterest(rateOfInterest), years(years) {};

    /**
     * Default destructor.
     */
    ~SavingsAccount() override = default;

    /**
     * Overrides the deposit method from the base class, adds profit from savings.
     *
     * @param amount The amount to deposit.
     */
    void deposit(double amount) override;

    /**
     * Returns the rate of interest for the savings account.
     *
     * @return The rate of interest.
     */
    [[nodiscard]] double getRateOfInterest() const;

    /**
     * Overloads the \<\< operator for outputting the savings account information.
     *
     * @param os The output stream.
     * @param account The savings account to output.
     * @return The output stream.
     */
    friend ostream &operator<<(ostream &os, const SavingsAccount &account);

    /**
     * The tax rate for savings accounts.
     */
    double taxRate = 0.19;

private:
    /**
     * The rate of interest for the savings account.
     */
    double rateOfInterest{};

    /**
     * The number of years the account would be active.
     */
    int years{};
};

/**
 * This class represents a bank and manages a collection of accounts.
 * It provides methods to add and remove accounts, as well as display all accounts.
 * It also allows finding an account based on its ID.
 */
class Bank {
public:
    /**
     * Default constructor.
     */
    Bank() = default;

    /**
     * Destructor.
     */
    ~Bank();

    /**
     * Copy constructor.
     */
    Bank(const Bank &);

    /**
     * Assignment operator.
     */
    Bank &operator=(const Bank &);

    /**
     * Adds an account to the bank.
     *
     * @param account The account to add.
     */
    void addAccount(Account &account);

    /**
    * Removes an account from the bank based on its ID.
    *
    * @param id The ID of the account to remove.
    */
    void removeAccount(int id);

    /**
     * Displays information about all accounts in the bank.
     */
    void displayAllAccounts() const;

    /**
     * Finds and returns an account based on its ID.
     *
     * @param id The ID of the account to find.
     * @return The found account.
     */
    [[nodiscard]] Account &findAccount(int id) const;

private:
    /**
     * The collection of accounts in the bank.
     */
    vector<Account *> accounts;
};


class TransactionRecorder {
public:
    TransactionRecorder() = default;

    explicit TransactionRecorder(int accountId) : accountId(accountId) {}

    void record_deposit(double amount);
    void record_withdrawal(double amount);


private:
    int accountId;
    void recordTransaction(double amount, const string &transactionType) const;
};



/**
 * This exception is thrown when an invalid amount is provided.
 */
class InvalidAmountException : public invalid_argument {
public:
    explicit InvalidAmountException() : invalid_argument("Invalid amount.") {}
};

/**
 * This exception is thrown when an account is not found.
 */
class AccountNotFoundException : public runtime_error {
public:
    explicit AccountNotFoundException() : runtime_error("Account not found.") {}
};

/**
 * This exception is thrown when a file cannot be opened.
 */
class FileFailedException : public runtime_error {
public:
    explicit FileFailedException() : runtime_error("Failed to open the file.") {}
};


#endif //CPPBANKMANAGEMENTSYSTEM_BANK_H

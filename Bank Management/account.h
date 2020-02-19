
#include <iostream>
#include <string>
#include <vector>
#include "Funds.h"

using namespace std;

#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

class Account {
    friend ostream &operator<<(ostream &Out, const Account &Account);
public:
//default
Account();
Account(const int &ID, const string &FName, const string &LName);
//destructor
~Account();
//overloading operators
bool operator>(const Account &Acct)const;
bool operator<(const Account &Acct)const;

//returns true if can transfer to other account
bool transferAssets(const int &FundType, const int &FundType1, const int &Money, Account *&acc, Account *&acc1);

//returns true if it remove funds, returns false if not enough funds to remove
bool withdrawAssets(const int &FundType, const int &Money);

//function to add money to the right fund type
bool depositAssets(const int &FundType, const int &Money);

//getters
//get first name
string getFName()const;

//get last name
string getLName()const;

//get id
int getID()const;

//display all transactions in each fund type
void displayTransactions() const;

//displays fund history for fund type given
void displayFundHistory(const int &FundType);

private:
    //transfers between money market and bonds
bool transferBetweenFunds(const int &FundType, const int &Money);
//add fund types into vector
vector<Fund> Funds;
//sets fund types into vector
void setFunds();
//variables
int ID;
string FName, LName;
};
#endif
// ASS5_ACCOUNT_H

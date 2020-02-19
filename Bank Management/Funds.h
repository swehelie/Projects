#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef ASS5_FUNDS_H
#define ASS5_FUNDS_H

class Fund{
public:
    //default constructor
Fund();
    //constructor
Fund(const string &FundName, const int &Balance);
//destructor
~Fund();

//if money deposited is more than or equal to zero, then true
//false otherwise
bool Deposit(const int &Money);

//if money withdrawn is more than equal to zero,
//remove from balance and return true, false if negative
bool Withdraw(const int &Money);
//returns balance
int getBalance() const;
//returns fund name
string getFundName() const;

//sets fund name and connects to variable
bool setFundName(const string &Fund);

//pushes message into string vector
void pushString(const string &history);

//prints the message from string vector fundV
void printHistory() const;
//int vectorSize();

private:
string FundName;
int Balance;
//string vector
vector<string> FundV;
};

#endif
// ASS5_FUNDS_H
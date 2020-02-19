#include <iostream>
#include "Funds.h"

//default constructor
Fund::Fund(){
  Balance = 0;
  FundName = "";
}

//constructor
Fund::Fund(const string &FundName, const int &Balance){
  this->FundName = FundName;
  this->Balance = Deposit(Balance);
}
//destructor
Fund::~Fund()= default;;

//returns fund name
string Fund::getFundName()const{
  return FundName;
}

//setter for fund name
bool Fund::setFundName(const string & Fund){
  this->FundName = Fund;
  return true;
}

//returns balances
int Fund::getBalance() const{
  return Balance;
}

//if money deposited is more than or equal to zero, then true
//false otherwise
bool Fund::Deposit(const int &Money){
  if(Money >= 0){
    Balance += Money;
    return true;
  }
  else{
    cout << "[ERROR] Negative amounts cannot be deposited." << endl;
      return false;
  }
}

//if money withdrawn is more than equal to zero,
//remove from balance and return true, false if negative
bool Fund::Withdraw(const int &Money){
  if(Money >= 0){
    if(Balance - Money >= 0){
      Balance -= Money;
      return true;
    }
    else{
      return false;
    }
  }
  else{
    cout << "[ERROR] Negative amounts cannot be withdrawn." << endl;
      return false;
  }
}

//pushes message into string vector
void Fund::pushString(const string &history){
  FundV.push_back(history);
}

//prints the message from string vector fundV
void Fund::printHistory()const{
  for(const auto & i : FundV){
    cout << i << endl;
  }
}


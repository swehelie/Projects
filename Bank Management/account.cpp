#include "account.h"
#include <iostream>
#include <string>
#include "Funds.h"
using namespace std;
using index_t = std::vector<int>::size_type;

//friend function
ostream &operator<<(ostream &Out, const Account &Account) {
    int size = Account.Funds.size();
    Out << "Name: " << Account.FName << " " << Account.LName << " ID: "
    << Account.getID() << endl;
    for(int i = 0; i < size; i++){
      Out << " " << Account.Funds[i].getFundName() << " : $" <<
      Account.Funds[i].getBalance() << endl;
    }
  return Out;
}

//initialize everything to an empty account
Account::Account() {
FName = ""; 
LName = ""; 
ID = 0000;
Funds.resize(10);
setFunds();
}

//opens a new account from queue
Account::Account(const int &ID, const string &FName, const string &LName) {
this->FName = FName;
this->LName = LName; 
this->ID = ID;
Funds.resize(10);
setFunds();
}

//sets each fundtype name in vector
void Account::setFunds(){
  Funds[0].setFundName("Money Market");
  Funds[1].setFundName("Prime Money Market");
  Funds[2].setFundName("Long Term Bond");
  Funds[3].setFundName("Short Term Bond");
  Funds[4].setFundName("500 Index Fund");
  Funds[5].setFundName("Capital Value Fund");
  Funds[6].setFundName("Growth Equality Fund");
  Funds[7].setFundName("Growth Index Fund");
  Funds[8].setFundName("Value Fund");
  Funds[9].setFundName("Value Stock Index");
}
//destructor
Account::~Account() = default;

//get first name
string Account::getFName()const{
  return FName;
}

//get last name
string Account::getLName()const{
  return LName;
}

//get account id
int Account::getID()const{
  return ID;
}

//function to add money to the right fund type
bool Account::depositAssets(const int &FundType, const int  &Money) {
    Funds[FundType].Deposit(Money);
    Funds[FundType].pushString("  Deposit: " + to_string(ID) +
    to_string(FundType) + " $" + to_string(Money));
  return true;
}

//transfer between money market accounts or bond accounts
bool Account::transferBetweenFunds(const int &FundType, const int &Money) {
  if(FundType == 0 || FundType == 2){
    int Amount = Funds[FundType].getBalance();
    if(Funds[FundType + 1].Withdraw(Money - Amount)){
      Funds[FundType + 1].pushString("  Withdrew: $" +
      to_string(Money - Amount) + " for " + Funds[FundType].getFundName());
      Funds[FundType].Withdraw(Amount);
      Funds[FundType].pushString("  Withdrew: $" + to_string(Amount)
      + " and borrowed $" + to_string(Money - Amount) + " from " +
      Funds[FundType+1].getFundName());
      return true;
    }
    else{
      //error: not enough funds & push error to record
        Funds[FundType].pushString("  Withdrawal of $" + to_string(Money)
        + " from " + Funds[FundType].getFundName() +
        " [FAILED] (Insufficient Funds).");
      return false;
    }
  }
  else if(FundType == 1 || FundType == 3){
    int Amount = Funds[FundType].getBalance();
    if(Funds[FundType - 1].Withdraw(Money - Amount)){
      Funds[FundType - 1].pushString("  Withdrew: $" +
      to_string(Money - Amount) + " for " + Funds[FundType].getFundName());
      Funds[FundType].Withdraw(Amount);
      Funds[FundType].pushString("  Withdrew: $" + to_string(Amount)
      + " and borrowed $" +to_string(Money - Amount) + " from " +
      Funds[FundType-1].getFundName());
      return true;
    }
    else{
      //error
        Funds[FundType].pushString("  Withdrawal of $" + to_string(Money)
        + " from " + Funds[FundType].getFundName() +
        " [FAILED] (Insufficient Funds).");
      return false;
    }
  }
  else{
      Funds[FundType].pushString("  Withdrawal of $" + to_string(Money)
                                 + " from " + Funds[FundType].getFundName() +
                                 " [FAILED] (Insufficient Funds).");
      return false;
  }
}

//returns true if it remove funds, returns false if not enough funds to remove
bool Account::withdrawAssets(const int &FundType, const int &Money) { 
  bool Test = Funds[FundType].Withdraw(Money);
  //if can be withdrawn, push history into vector
  if(Test){
      Funds[FundType].pushString("  Withdrew: "  + to_string(ID) +
      to_string(FundType) + " $" +
      to_string(Money));
      return true;
  }
  //if cannot, check for Money Markets and Bonds
  else{
    transferBetweenFunds(FundType, Money);
  }
  return true;
}

//returns true if can transfer to other account
bool Account::transferAssets(const int &FundType, const int &FundType1,
        const int &Money, Account *&acc, Account *&acc1){
//if transferring to different account
    if(acc->getID() != acc1->getID()){
        //if can be withdrawn, push history into vector
        if(acc->Funds[FundType].Withdraw(Money)){
            acc1->Funds[FundType1].Deposit(Money);
            acc->Funds[FundType].pushString("  Transfer: " +
            to_string(ID) + to_string(FundType) + " $" +
            to_string(Money) + " " + to_string(acc1->getID()) +
            to_string(FundType1) + "[Successful]");
            acc1->Funds[FundType1].pushString("  Deposit: $" +
            to_string(Money) + " from " + to_string(acc->getID()));
            return true;
        }
            //if cannot, error message
        else {
            acc->Funds[FundType1].pushString
            ("  Deposit: " + to_string(acc->getID()) +
            to_string(FundType1) + " " + to_string(Money)
            +" [FAILED] due to insufficient funds.");
            return false;
        }
    }
        //not transferring to different account
    else {
        //if can be withdrawn, push history into vector
        if(Funds[FundType].Withdraw(Money)){
            Funds[FundType1].Deposit(Money);
            Funds[FundType].pushString("  Transfer: " +
            to_string(ID) +
            to_string(FundType) + " $" + to_string(Money) + " " +
            to_string(ID) + to_string(FundType1) + " [Successful]");
            Funds[FundType1].pushString("  Deposit: " +
            to_string(ID) +
            to_string(FundType1) + " $" + to_string(Money) + " from " +
            to_string(ID) + to_string(FundType));
            return true;
        }
            //if cannot, error message
        else {
            Funds[FundType].pushString("  Transfer: " +
            to_string(ID) +
            to_string(FundType) + " $" + to_string(Money) + " " +
            to_string(ID) + to_string(FundType1) +
            " [FAILED] due to insufficient funds.");
            return false;
        }
    }
}

//display all transactions
void Account::displayTransactions() const {
  cout << "Transaction History For: " << getFName() << " " << getLName()
  << " -- " << getID() << endl;
    for (index_t I = 0; I < Funds.size(); I++) {
      if(!Funds.empty()) {
        cout << "Fund" << "{" << I << "} " << Funds[I].getFundName()
        << ": $" << Funds[I].getBalance() << endl;
        Funds.at(I).printHistory();
      }
    }
}

//returns true if current account number is greater than the other account number
bool Account::operator>(const Account &Acct) const {
	return ID > Acct.getID();
}

//returns true if current account number is less than the other account number
bool Account::operator<(const Account &Acct) const {
	return ID < Acct.getID();
}

//displays transaction history for fund type
void Account::displayFundHistory(const int &FundType){
  cout << " **Fund History For** \n" << getFName() << " " << getLName()
  << " -- " << getID() << endl;

  cout << "  Fund: " << Funds[FundType].getFundName() << endl;
  cout << "  Balance: $"
  << Funds[FundType].getBalance() << endl;

  Funds[FundType].printHistory();
}







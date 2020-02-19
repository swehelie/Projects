
#include "bank.h"
#include <iostream>
#include <sstream>
using namespace std;

// empty


Bank::Bank() = default;

Bank::~Bank() = default;

//reads the file and distinguishes the items in the string
//pushed into queue
void Bank::processTransactions(const string &FileName) {
  ifstream file;
  file.open(FileName);
  string line;
  while(!file.eof()){
    getline(file, line);
    istringstream sar(line);
    while(!sar.eof()){
      string Type;
      getline(sar, Type, ' ');
      if(Type == "O"){
        Info Open;
        Open.Key = Type;
        string FirstName;
        getline(sar, FirstName, ' ');
        string LastName;
        getline(sar, LastName, ' ');
        string AccNum;
        getline(sar, AccNum, ' ');
        if(AccNum.size() != 4 || (atoi(AccNum.c_str()) < 1000) ||
        (atoi(AccNum.c_str()) > 9999)){
            cout << "[ERROR] Invalid ID Number:" << AccNum << endl;
        }
        else{
          Open.FirstN = FirstName;
          Open.LastN = LastName;
          Open.ID = atoi(AccNum.c_str());
          BankQ.push(Open);
        }
      }//End OF Open
      else if(Type == "D"){
        Info Deposit;
        Deposit.Key = Type;
        string FundId;
        getline(sar, FundId, ' ');
        if(FundId.size() != 5){
          cout << "[ERROR] Invalid ID & Fund Number:" << FundId << endl;
        }
        else{
          //separating ID and fund type
          string SID = FundId.substr(0, 4);
          string FKey = FundId.substr(4, 1);
          string Balance;
          getline(sar, Balance, ' ');
          if(atoi(Balance.c_str()) < 0){
            cout << "[ERROR] Cannot Deposit a Negative Balance" << endl;
          }
          else{
            //string to int
           Deposit.ID = atoi(SID.c_str());
           Deposit.FundType1 = atoi(FKey.c_str());
           Deposit.Amount = atoi(Balance.c_str());
           BankQ.push(Deposit);
          }
        }
      }//End OF D
      else if(Type == "W"){
        Info Withdraw;
        Withdraw.Key = Type;
        string FundId;
        getline(sar, FundId, ' ');
        if(FundId.size() != 5){
          cout << "[ERROR] Invalid ID & Fund Number:" << FundId << endl;
        }
        else{
          //separating ID and fund type
          string SID = FundId.substr(0, 4);
          string FKey = FundId.substr(4, 1);
          string Balance;
          getline(sar, Balance, ' ');
          if(atoi(Balance.c_str()) < 0){
            cout << "[ERROR] Cannot Deposit a Negative Balance" << endl;
          }
          else{
            //string to int
           Withdraw.ID = atoi(SID.c_str());
           Withdraw.FundType1 = atoi(FKey.c_str());
           Withdraw.Amount = atoi(Balance.c_str());
           BankQ.push(Withdraw);
          }
        }
      }//End of W
      else if(Type == "T"){
        Info Transfer;
        Transfer.Key = Type;
        string FundId;
        getline(sar, FundId, ' ');
        if(FundId.size() != 5){
          cout << "[ERROR] Invalid ID & Fund Number:" << FundId << endl;
        }
        else{
          //separating ID and fund type
          string SID = FundId.substr(0, 4);
          string FKey = FundId.substr(4, 1);
          string Balance;
          getline(sar, Balance, ' ');
          if(atoi(Balance.c_str()) < 0){
            cout << "[ERROR] Cannot Deposit a Negative Balance" << endl;
          }
          else{
            string transfer;
            getline(sar, transfer, ' ');
            if(transfer.size() != 5){
              cout << "[ERROR] Invalid ID & Fund Number:" << FundId << endl;
            }
            else{
              string SIDTrans = transfer.substr(0, 4);
              string FKeyTrans = transfer.substr(4, 1);
              Transfer.ID = atoi(SID.c_str());
              Transfer.ID2 = atoi(SIDTrans.c_str());
              Transfer.FundType1 = atoi(FKey.c_str());
              Transfer.FundType2 = atoi(FKeyTrans.c_str());
              Transfer.Amount = atoi(Balance.c_str());
              BankQ.push(Transfer);
            }
          }
        }
      }//End of T
      else if(Type == "H"){
        Info History;
        History.Key = Type;
        string FundId;
        getline(sar, FundId, ' ');
        if(FundId.size() < 4 || FundId.size() > 5){
          cout << "[ERROR] Invalid ID & Fund Number:" << FundId << endl;
        }
        else{
          string SID = FundId.substr(0, 4);
          string FKey = "-1";
          if(FundId.size() == 5){
            FKey = FundId.substr(4, 1);
          }
          History.ID = atoi(SID.c_str());
          int Num = atoi(FKey.c_str());
          History.FundType1 = Num;
          BankQ.push(History);
        }
      }//End of H
    }
  }
  file.close();
}

//handles all the transactions with dequeue
void Bank::handleQueue(){
  while(!BankQ.empty()){
    Info items = BankQ.front();
    if(items.Key == "O") {
        string FName = items.FirstN;
        string LName = items.LastN;
        int ID = items.ID;
        Account *Acc;
        Acc = new Account(ID, FName, LName);
        // deletes Account to avoid memory leak
            if (!Accounts.insert(Acc)) {
                cout << "[ERROR] Account " + to_string(ID) +
                " is already open." << endl;
                delete Acc;
            }
    }//End of O
    else if(items.Key == "D"){
      int Fund = items.FundType1;
      int Balance = items.Amount;
      int ID = items.ID;
      Account *Acc;
      bool result = Accounts.retrieve(ID, Acc);
      if(result){
        Acc->depositAssets(Fund, Balance);
      }
      else{
        cout << "[ERROR] Account " << ID << " Does Not Exist." << endl;
      }
    }//End of D
    else if(items.Key == "W"){
      int Fund = items.FundType1;
      int Balance = items.Amount;
      int ID = items.ID;
      Account *Acc;
      if(Accounts.retrieve(ID, Acc)){
        Acc->withdrawAssets(Fund, Balance);
      }
      else{
        cout << "[ERROR] Account " << ID << " Does Not Exist." << endl;
      }
    }//End of W
    else if(items.Key == "T"){
      int Fund = items.FundType1;
      int Balance = items.Amount;
      int ID = items.ID;
      int transFund = items.FundType2;
      int transID = items.ID2;
        Account *Acc;
        Account *Acct;
        if(!Accounts.retrieve(ID, Acc) ||
        !Accounts.retrieve(transID, Acct)){
            cout << "[ERROR] Account " << transID << " Does Not Exist." << endl;
        }
        else{
            Acc->transferAssets(Fund, transFund, Balance, Acc, Acct);
        }
    }//End of T
    else if(items.Key == "H") {
      int Fund = items.FundType1;
      int ID = items.ID;
      Account *Acc;
      if (Accounts.retrieve(ID, Acc)) {
        if(Fund == -1){
          Acc->displayTransactions();
        }
        else{
          Acc->displayFundHistory(Fund);
        }
      }
      else{
        cout << "[ERROR] Account " << ID << " Does Not Exist." << endl;
      }
    }//End of H
    BankQ.pop();
  }
}


//display all accounts at the end
void Bank::displayAllBankBalances() const {
  Accounts.display();
}



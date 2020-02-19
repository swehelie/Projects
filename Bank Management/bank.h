
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include "account.h"
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class Bank {
public:
  Bank();
  ~Bank();
  void processTransactions(const string &FileName);
  void displayAllBankBalances() const;
  void handleQueue();

private:
  struct Info{
      string FirstN, LastN, Key;
    int FundType1, FundType2;
    int Amount, ID, ID2;
  };
  AccountTree Accounts;
  queue<Info> BankQ;
};
#endif
// ASS5_BANK_H

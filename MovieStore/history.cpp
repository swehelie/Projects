//
// Created by Sarah Wehelie on 3/11/20.
// History Class. Inherits functions from Transaction.
// Child class of Transaction. Prints customer history

#include "history.h"

// Constructor - initalizes customer pointer
History::History(Customer *Cust) {
  this->Cust = Cust;
}

// used to print History
void History::output() {
  cout << "History: " << Cust->getName();
}

// implements the function to print
// Customer History
void History::transact() {
  cout << endl;
  cout << "History: " << Cust->getName() << endl;
  Cust->printTransactions();
}
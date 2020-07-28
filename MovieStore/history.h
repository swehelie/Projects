//
// Created by Sarah Wehelie on 3/11/20.
// History Class. Inherits functions from Transaction.
// Child class of Transaction. Prints customer history

#ifndef MOVIESTORE_HISTORY_H
#define MOVIESTORE_HISTORY_H
#include "transaction.h"
#include <string>
using namespace std;

class History : public Transaction {
public:
    // Constructor - initalizes customer pointer
    explicit History(Customer* Cust);
    ~History() override = default;
    // used to print History
    void output() override;
    // implements the function to print
    // Customer History
    void transact() override;

private:
    Customer* Cust{};
};
#endif //MOVIESTORE_HISTORY_H

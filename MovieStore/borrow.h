//
// Created by Sarah Wehelie on 3/4/20.
// Contains Borrow Class.
// Inherits functions output() and transact() from Transaction class
// Executes Borrow command by updating Stock and using Customer pointer
// to record the command. Assumes that Stock > 0.

#ifndef MOVIESTORE_BORROW_H
#define MOVIESTORE_BORROW_H
#include "transaction.h"


class Borrow : public Transaction{
public:
    // ==== Constructor ====
    Borrow(Customer* Cust, Movie* Mv);
    // ==== Destructor ====
    ~Borrow() override = default;
    // Prints the record of Borrowed Movies
    void output() override;
    // implements Borrow command
    void transact() override;

private:
    // local variables
    Movie* MPtr;
    int Stock;
    Customer* CPtr;
};
#endif //MOVIESTORE_BORROW_H

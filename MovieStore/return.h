//
// Created by Sarah Wehelie on 3/8/20.
// Return Class. Child Class of Transaction.
// Implements output() to print out record of returned movie
// Implements transact() to return movie, update customer, and stock records.

#ifndef MOVIESTORE_RETURN_H
#define MOVIESTORE_RETURN_H
#include "transaction.h"
#include <string>

class Return : public Transaction{
public:
    // Constructor - initializes customer and movie
    Return(Customer* Cust, Movie* Mv);
    ~Return() override = default;
    // prints record of returned movie
    void output() override;
    // implements return function
    void transact() override;

private:
     Movie* MPtr;
     int Stock;
     Customer* CPtr;
};
#endif //MOVIESTORE_RETURN_H

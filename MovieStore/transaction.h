//
// Created by Sarah Wehelie on 3/8/20.
// Transaction Abstract Class. Child classes are Borrow, Return,
// Inventory, and History. Carries out actual transactions and creates
// the child classes objects.

#ifndef MOVIESTORE_TRANSACTION_H
#define MOVIESTORE_TRANSACTION_H
#include <string>
#include "store.h"
#include "movie.h"
#include "moviefactory.h"
#include "transactionfactory.h"
#include "movie.h"
#include "drama.h"
#include "comedy.h"
#include "classics.h"
#include <set>

class Customer;
class Transaction{
public:
    friend class Store;
    Transaction() = default;
    virtual ~Transaction() = default;
    // VIRTUAL Child classes will implement
    virtual void output() = 0;
    virtual void transact() = 0;
    // creates transactions
    static Transaction* create(string& Line);

private:
    // makes the transactions
    static Transaction* make(char CommandType, Customer* Cust, Movie* Mv);

};
#endif //MOVIESTORE_TRANSACTION_H

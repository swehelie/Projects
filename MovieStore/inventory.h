//
// Created by Sarah Wehelie on 3/11/20.
// Inventory Class. Child class of Transaction.
// Responsible for implementing function to print
// inventory of movies.

#ifndef MOVIESTORE_INVENTORY_H
#define MOVIESTORE_INVENTORY_H
#include "transaction.h"
#include <iostream>

class Inventory : public Transaction {
public:
    Inventory()= default;
    ~Inventory() override = default;
    void output() override;
    // implements function to print inventory of movies
    void transact() override;

};
#endif //MOVIESTORE_INVENTORY_H

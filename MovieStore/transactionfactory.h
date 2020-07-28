//
// Created by Sarah Wehelie on 3/11/20.
//

#ifndef MOVIESTORE_TRANSACTIONFACTORY_H
#define MOVIESTORE_TRANSACTIONFACTORY_H
#include "transaction.h"
#include <string>
using namespace std;

class Transaction;
class TransactionFactory{
public:
    virtual Transaction* create(string& Line) = 0;
};
#endif //MOVIESTORE_TRANSACTIONFACTORY_H

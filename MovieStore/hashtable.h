//
// Created by Sarah Wehelie on 3/8/20.
// HashTable class. Uses HashList to define Customer and Key.
// HashTable is used to find and gather the Customer's information.

#ifndef MOVIESTORE_HASHTABLE_H
#define MOVIESTORE_HASHTABLE_H
#include "customer.h"
const int TABLE_SIZE = 300;
using namespace std;

class Customer;
class HashList{
public:
    // to store into hash table
    int Key;
    // Customer pointer
    Customer* Cust;
    // Constructor - initialize key and customer
    HashList(int K, Customer* C){
      Key = K;
      Cust = C;
    }
};

class HashTable{
public:
    // ==== Constructor ====
    HashTable();
    // ==== Destructor ====
    ~HashTable();
    int hashFunction(int Key);
    // search for customer at a key,
    // returns customer pointer
    Customer *search(int Key);
    // Adds customer at a key in hashtable
    void add(int Key, Customer* Cust);
    // removes customer from key
    void remove(int Key);
    void print();
    // destroy the objects created by the constructor
    void clear();

private:
    HashList **Table;
};
#endif //MOVIESTORE_HASHTABLE_H

//
// Created by Sarah Wehelie on 3/5/20.
// Store database that reads all text files and
// stores them in their proper containers, which will be accessed
// in other functions.

#ifndef MOVIESTORE_STORE_H
#define MOVIESTORE_STORE_H

#include <string>
#include <iostream>
#include "movie.h"
#include "moviefactory.h"
#include "customer.h"
#include "hashtable.h"
#include "bst.h"
#include "classics.h"
#include "drama.h"
#include "comedy.h"
#include <map>
#include <set>
#include <queue>
#include <vector>

using namespace std;
class HashTable;
class Transaction;
class Store{
public:
    friend class Transaction;
    // constructor
  Store(){}
  // reads movie text files, creates objects, and stores in bst
  void readMovies(const string& FileName);
  // reads commands text files and stores in queue
  void readCommands(const string& FileName);
  // reads customers and stores in hashtable
  void readCustomers(const string& FileName);
  // prints all movies in the bst
  static void printMovies();
  // retrieves movie pointer from bst
  Movie* retrieve(Movie *Mv, const string &Action);
  // destructor
  ~Store();

private:
    // variables
    static BinarySearch Classics;
    static BinarySearch Drama;
    static BinarySearch Comedy;
    static HashTable Customers;
    static set<string> MediaType;
    queue<Transaction*> TPtr;
};
#endif //MOVIESTORE_STORE_H

//
// Created by Sarah Wehelie on 3/8/20.
// Customer Class. Contains the information of individual
// customers who conduct transactions.


#ifndef MOVIESTORE_CUSTOMER_H
#define MOVIESTORE_CUSTOMER_H
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include "movie.h"
#include "transaction.h"
using namespace std;

class Transaction;

class Customer{
public:
    // Constructor
   Customer();
    // Constructor
   Customer(int ID, string Name);

   // ==== GETTERS ====
   string getName() const;
   int getID() const;

   // Deletes items in queue and vector
   void clearCommands();
   void clearMovieList();

   // Prints Customer history
   void printTransactions();
   // Removes movie from customer history after returned
   void removeMovie(Movie *MvPtr);
   // Checks if movie has already been rented
   bool isRented(Movie *MvPtr);
   // Adds movie into MovieList vector
   void addMovie(Movie *MvPtr);
   // Adds transaction into Commands queue
   void addTransaction(Transaction *Trans);
   // friend function
   friend ostream& operator<<(ostream& Os, const Customer& Cust);

private:
    // local variables
    string CName;
    int ID;
    // Holds transactions made my customers
    queue<Transaction*> Commands;
    // Adds movie information
    vector<Movie*> MovieList;

};
#endif //MOVIESTORE_CUSTOMER_H

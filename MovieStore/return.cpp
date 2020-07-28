//
// Created by Sarah Wehelie on 3/8/20.
// Return Class. Child Class of Transaction.
// Implements output() to print out record of returned movie
// Implements transact() to return movie, update customer, and stock records.
#include "return.h"
#include <iostream>
using namespace std;

// Constructor - initializes customer and movie
Return::Return(Customer *Cust, Movie *Mv) {
  MPtr = Mv;
  CPtr = Cust;
  Stock = 0;
}

// prints record of returned movie
void Return::output() {
  cout << "-RETURNED: " << MPtr->getGenre() << ", " <<  MPtr->getTitle()
  << ", " << MPtr->getDirector() << " " << MPtr->getYear() << endl;
}

// implements return function
void Return::transact() {
  Stock = 0;
  if(CPtr->isRented(MPtr)){
    // records in customer
    CPtr->removeMovie(MPtr);
    CPtr->addTransaction(this);
    MPtr->returnMovie();
    Stock = MPtr->getStock();
  }
}
//
// Created by Sarah Wehelie on 3/8/20.
// Contains Borrow Class.
// Inherits functions output() and transact() from Transaction class
// Executes Borrow command by updating Stock and using Customer pointer
// to record the command. Assumes that Stock > 0.
#include "borrow.h"
#include <iostream>
using namespace std;

// ==== Constructor ====
Borrow::Borrow(Customer *Cust, Movie *Mv) {
  MPtr = Mv;
  CPtr = Cust;
  Stock = 0;
}

// Prints the record of Borrowed Movies
void Borrow::output() {
  cout << "-BORROWED: " << MPtr->getGenre() << ", " <<
  MPtr->getTitle() << ", " << MPtr->getDirector() << " " <<
  MPtr->getYear() << endl;
}

// implements Borrow command
void Borrow::transact() {
  Stock = 0;
  if(MPtr->getStock() > 0){
    // adds Movie record to Customer pointer
    CPtr->addMovie(MPtr);
    // adds evidence of transaction to Customer pointer
    CPtr->addTransaction(this);
    // Decreases Stock
    MPtr->borrowMovie();
    // Updates Stock
    Stock = MPtr->getStock();
  }
  // If Movie out of stock
  else{
    cout << "ERR:: MOVIE OUT OF STOCK -- " << MPtr->getGenre() << ", " <<
    MPtr->getTitle() << ", " << MPtr->getDirector() <<  " " <<
    MPtr->getYear() << endl;
  }
}
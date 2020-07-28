//
// Created by Sarah Wehelie on 3/8/20.
// Customer Class. Contains the information of individual
// customers who conduct transactions.
#include "customer.h"
#include <iostream>
#include <algorithm>

// Constructor
Customer::Customer() {
  ID = 0;
  CName = "";
}

// Constructor
Customer::Customer(int ID, string Name) {
  this->ID = ID;
  CName = Name;
}

// ==== GETTERS ====
string Customer::getName() const {
  return CName;
}

int Customer::getID() const {
  return ID;
}

// Deletes items in queue and vector

void Customer::clearCommands() {
  while(!Commands.empty()){
    Commands.pop();
  }
}

void Customer::clearMovieList() {
  MovieList.clear();
}

// Prints Customer history
void Customer::printTransactions() {
  cout << *this << endl;
  queue<Transaction*> Temp;
  while(!Commands.empty()) {
    Commands.front()->output();
    Temp.push(Commands.front());
    Commands.pop();
  }
  cout << endl;
  Commands = Temp;
}

// Removes movie from customer history after returned
void Customer::removeMovie(Movie *MvPtr) {
  auto It = find(MovieList.begin(), MovieList.end(), MvPtr);
  if(It != MovieList.end()){
    MovieList.erase(It);
  }
}

// Checks if movie has already been rented
bool Customer::isRented(Movie *MvPtr) {
  auto It = find(MovieList.begin(), MovieList.end(), MvPtr);
  if(It != MovieList.end()){
    return true;
  }
  return false;
}

// Adds movie into MovieList vector
void Customer::addMovie(Movie *MvPtr) {
  MovieList.push_back(MvPtr);
}

// Adds transaction into Commands queue
void Customer::addTransaction(Transaction *Trans) {
  Commands.push(Trans);
}

// friend function
ostream& operator<<(ostream &Os, const Customer &Cust) {
  Os << Cust.ID << " " << Cust.CName;
  return Os;
}
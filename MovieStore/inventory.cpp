//
// Created by Sarah Wehelie on 3/11/20.
// Inventory Class. Child class of Transaction.
// Responsible for implementing function to print
// inventory of movies.
#include "inventory.h"

// prints inventory
void Inventory::output() {
  cout << "Inventory: " << endl;
}

// implements function to print inventory of movies
void Inventory::transact() {
  Store::printMovies();
}
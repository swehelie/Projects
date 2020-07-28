//
// Created by Sarah Wehelie on 3/8/20.
// HashTable class. Uses HashList to define Customer and Key.
// HashTable is used to find and gather the Customer's information.

#include "hashtable.h"
#include <iostream>

// ==== Constructor ====
HashTable::HashTable() {
  Table = new HashList *[TABLE_SIZE];
  for(int I = 0; I < TABLE_SIZE; I++){
    Table[I] = nullptr;
  }
}

// ==== Destructor ====
HashTable::~HashTable() {
  clear();
}

// destroy the objects created by the constructor
void HashTable::clear() {
  for (int I = 0; I < TABLE_SIZE; I++) {
    if (Table[I] != nullptr) {
      delete Table[I]->Cust;
      delete Table[I];
    }
  }
  delete[] Table;
}

int HashTable::hashFunction(int Key) {
  return Key % TABLE_SIZE;
}

// search for customer at a key,
// returns customer pointer
Customer* HashTable::search(int Key) {
  int Hash = hashFunction(Key);
  while (Table[Hash] != nullptr && Table[Hash]->Key != Key) {
    Hash = hashFunction(Hash + 1);
  }
  if (Table[Hash] == nullptr) {
    return nullptr;
  }
  else {
    return Table[Hash]->Cust;
  }
}

// Adds customer at a key in hashtable
void HashTable::add(int Key, Customer *Cust) {
  if(Key > 9999 || Key < 0){
    return;
  }
  int Hash = hashFunction(Key);
  while (Table[Hash] != nullptr && Table[Hash]->Key != Key) {
    Hash = hashFunction(Hash + 1);
  }
  if (Table[Hash] != nullptr) {
    delete Table[Hash];
  }
  Table[Hash] = new HashList(Key, Cust);
}

// removes customer from key
void HashTable::remove(int Key) {
  int Hash = hashFunction(Key);
  while (Table[Hash] != nullptr) {
    if (Table[Hash]->Key == Key)
      break;
    Hash = hashFunction(Hash + 1);
  }
  if (Table[Hash] == nullptr) {
    cout<<"No Element found at key "<<Key<<endl;
    return;
  } else {
    delete Table[Hash];
  }
  cout<<"Element Deleted"<<endl;
}

// prints content of HashTable
void HashTable::print() {
  for (int I = 0; I < TABLE_SIZE; I++) {
    if (Table[I] != nullptr)
      std::cout << *Table[I]->Cust << std::endl;
  }
}
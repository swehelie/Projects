//
// Created by Sarah Wehelie on 3/5/20.
// Store database that reads all text files and
// stores them in their proper containers, which will be accessed
// in other functions.

#include "store.h"
#include "inventory.h"
#include "transaction.h"
#include <fstream>
#include <sstream>
#include <set>

// initializing static variables
set<string> Store::MediaType = {"D"};
BinarySearch Store::Classics;
BinarySearch Store::Drama;
BinarySearch Store::Comedy;
HashTable Store::Customers;

// destructor
Store::~Store(){
  while(!TPtr.empty()){
    delete TPtr.front();
    TPtr.pop();
  }
}

// reads movie text files, creates objects, and stores in bst
void Store::readMovies(const string &FileName) {
  ifstream myFile(FileName);
  string Read;
  if(myFile.is_open()){
    while(getline(myFile, Read)){
      Movie* Mv = Movie::create(Read);
      if(Mv != nullptr) {
        char Type = Read[0];
          if(Type =='D'){
            Drama.insert(Mv);
          }
          else if(Type == 'C') {
            Classics.insert(Mv);
          }
          else if(Type == 'F'){
            Comedy.insert(Mv);
          }
          else {
            cout << "ERR:: INVALID MOVIE TYPE" << endl;
          }
      }
      Read = "";
    }
  }
  else{
    cout << "ERR:: Could Not Open File: " << FileName;
  }
  myFile.close();
}

// reads commands text files and stores in queue
void Store::readCommands(const string &FileName) {
  ifstream myFile(FileName);
  string Read;
//  vector<string> Errors;
  if(myFile.is_open()){
    while(getline(myFile, Read)){
      Transaction* Trans = Transaction::create(Read);
      if(Trans != nullptr){
        TPtr.push(Trans);
      }
    }
    Read = "";
  }
  else{
    cout << "ERR:: Could Not Open File: " << FileName;
  }
  myFile.close();
}

// reads customers and stores in hashtable
void Store::readCustomers(const string &FileName) {
  ifstream myFile(FileName);
  string Read;
  stringstream ss;
  int ID;
  string Name;
  if(myFile.is_open()){
    while(getline(myFile, Read)){
      ss << Read;
      ss >> ID;
      ss.get();
      getline(ss, Name);
      if(Customers.search(ID) == nullptr){
        auto* Cust = new Customer(ID, Name);
        Customers.add(ID, Cust);
        ss.clear();
      }
    }
  } else {
    cout << "ERR:: Could Not Open File: " << FileName;
  }
  myFile.close();
}

// prints all movies in the bst
void Store::printMovies() {
  cout << endl;
  Inventory In;
  In.output();
  cout << "\n" << "==== Comedy ====" << endl;
  cout << "Movie Type ~ Stock ~ Director ~ Title ~ Year" << endl;
  Comedy.printOutput();
  cout << endl;
  cout << "==== Drama ====" << endl;
  cout << "Movie Type ~ Stock ~ Director ~ Title ~ Year" << endl;
  Drama.printOutput();
  cout << endl;
  cout << "==== Classics ====" << endl;
  cout << "Movie Type ~ Stock ~ Director ~ Title ~ Actor ~ Month ~ Year" << endl;
  Classics.printOutput();
  cout << endl;
}

// retrieves movie pointer from bst
Movie* Store::retrieve(Movie *Mv, const string& Action) {
    if(Action == "D") {
      return Drama.retrieve(Mv);
    }
    else if(Action == "F") {
      return Comedy.retrieve(Mv);
    }
    else if (Action == "C") {
      return Classics.retrieve(Mv);
    }
    else{
      return nullptr;
    }
}





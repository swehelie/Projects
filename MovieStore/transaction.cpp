//
// Created by Sarah Wehelie on 3/8/20.
// Transaction Abstract Class. Child classes are Borrow, Return,
// Inventory, and History. Carries out actual transactions and creates
// the child classes objects.

#include "transaction.h"
#include "borrow.h"
#include "return.h"
#include "history.h"
#include "inventory.h"
#include "classics.h"
#include <iostream>
#include "customer.h"
#include <sstream>
#include <set>

// creates transactions, returns transaction pointer
// that will then make the transaction in the make() function
Transaction* Transaction::create(string& Line) {
  int ID = 0;
  char ActionType;
  string MovieC, MediaC;
  int Month = 0;
  int Year = 0;
  Movie* Mv = nullptr;
  Movie* Curr = nullptr;
  Transaction* Trans = nullptr;
  string Title, Director, Actor, ActorF, ActorL;
  stringstream ss(Line);
  ss >> ActionType;
  if(ActionType == 'I'){
    return make(ActionType, nullptr, nullptr);
  }
  ss >> ID;
  Customer* Cust = Store::Customers.search(ID);
  if(Cust == nullptr){
    cout << "ERR:: CUSTOMER ID " << ID << " IS NOT VALID." << endl;
    return nullptr;
  }
  if(ActionType == 'H'){
    return make(ActionType, Cust, nullptr);
  }
  if(ActionType == 'B' || ActionType == 'R'){
    ss >> MediaC;
    ss.get();
    if(Store::MediaType.count(MediaC) == 1){
      ss >> MovieC;
      string Space;
      if(MovieC == "D"){
        getline(ss, Space, ' ');
        getline(ss, Director, ',');
        getline(ss, Space, ' ');
        getline(ss, Title, ',');
        Curr = new Drama(Director, Title);
        Store St;
        Mv = St.retrieve(Curr, MovieC);
        if(Mv != nullptr) {
          Trans = make(ActionType, Cust, Mv);
        }
        else{
          cout << "ERR:: THE MOVIE " << MovieC << ": " << Title << " "
          << Director << " DOES NOT EXIST. " << endl;
        }
        delete Curr;
      }
      else if(MovieC == "F"){
        getline(ss, Space, ' ');
        getline(ss, Title, ',');
        getline(ss, Space, ' ');
        getline(ss, Director);
        stringstream(Director) >> Year;
        Curr = new Comedy(Title, Year);
        Store St;
        Mv = St.retrieve(Curr, MovieC);
        if(Mv != nullptr) {
          Trans = make(ActionType, Cust, Mv);
        }
        else{
          getline(ss, Title);
          cout << "ERR:: THE MOVIE " << MovieC << ": " << Title << " "
               << Year << " DOES NOT EXIST. " << endl;
        }
        delete Curr;
      }
      else if(MovieC == "C"){
        getline(ss, Title, ' ');
        getline(ss, Title, ' ');
        stringstream(Title) >> Month;
        getline(ss, Title, ' ');
        stringstream(Title) >> Year;
        ss >> Title;
        Actor += Title;
        Actor += ' ';
        ss >> Title;
        Actor += Title;
        Curr = new Classics(Actor, Month, Year);
        Store St;
        Mv = St.retrieve(Curr, MovieC);
        if(Mv != nullptr) {
          Trans = make(ActionType, Cust, Mv);
        }
        else{
          cout << "ERR:: THE MOVIE " << MovieC << ": " << Actor << " "
               << Month << " " << Year << " DOES NOT EXIST. " << endl;
        }
        delete Curr;
      }
      else{
        cout << "ERR:: INVALID MOVIE CODE - " << MovieC << endl;
      }
    }
    else{
      cout << "ERR:: INVALID MEDIA TYPE - " << MediaC << endl;
    }
  }
  else{
    cout << "ERR:: INVALID COMMAND - " << ActionType << endl;
  }
  return Trans;
}

// makes the transaction, actually implements, and returns transaction pointer
Transaction* Transaction::make(char CommandType, Customer *Cust, Movie *Mv) {
  Transaction* Trans = nullptr;
  switch(CommandType){
    case 'B' : {
      Trans = new Borrow(Cust, Mv);
      Trans->transact();
      break;
    }
    case 'R' : {
      Trans = new Return(Cust, Mv);
      Trans->transact();
      break;
    }
    case 'I' : {
      Trans = new Inventory();
      Trans->transact();
      break;
    }
    case 'H' : {
      Trans = new History(Cust);
      Trans->transact();
      break;
    }
    default:
      cout << "ERR:: Invalid Action Type. " << endl;
  }
  return Trans;
}



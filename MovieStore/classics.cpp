//
// Created by Sarah Wehelie on 3/8/20.
// Classic movie class. Inherits from Movie Class.
// Implements unique sorting attributes.
#include "classics.h"
#include <iostream>
#include <sstream>

// Constructor. Initializes actor, month, year
Classics::Classics(const string& Actor, const int& Month, const int& Year) {
  this->Actor = Actor;
  this->Month = Month;
  this->Year = Year;
}

// Constructor. Initializes all local variables
Classics::Classics(const int& Stock, const string& Director,
                   const string& Title, const string& Actor, const int& Month,
                   const int& Year) {
  this->Stock = Stock;
  this->Director = Director;
  this->Title = Title;
  this->Actor = Actor;
  this->Month = Month;
  this->Year = Year;
  this->Genre = "Classic";
}

// prints in its own format ex: C, 10, Hal Ashby, Harold and Maude,
// Ruth Gordon 3 1971
string Classics::getFormat() const {
  ostringstream Os;
  Os << "C, " << this->Stock << ", " << this->Director << ", "
  << this->Title << ", " << this->Actor << ", " << this->Month << " " <<
  this->Year << endl;
  return Os.str();
}

// ======= GETTERS =======
int Classics::getStock() const {
  return Stock;
}

string Classics::getDirector() const {
  return Director;
}

string Classics::getGenre() const {
  return Genre;
}

string Classics::getTitle() const {
  return Title;
}

int Classics::getYear() const {
  return Year;
}

// Decreases stock
void Classics::borrowMovie() {
  if(Stock > 0) {
    Stock--;
  }
}

// Increases stock
void Classics::returnMovie() {
  Stock++;
}

// operator==. Checks if Actor, Month, and Year are equal
// return true if equal, false otherwise
bool Classics::isEqual(const Movie *Mv) const{
  const auto* Cl = dynamic_cast<const Classics*>(Mv);
  return ((Year == Cl->Year) && (Month == Cl->Month) && (Actor == Cl->Actor));
}

// operator>. Sorts Classics based on Actor, Month, Year
// returns true if one is more than the other, false otherwise
bool Classics::moreThan(const Movie *Mv) const{
  const auto* Cl = dynamic_cast<const Classics*>(Mv);
  return ((Year > Cl->Year) || ((Year == Cl->Year) && (Month > Cl->Month)) ||
         ((Year == Cl->Year) && (Month == Cl->Month) && (Actor > Cl->Actor)));
}
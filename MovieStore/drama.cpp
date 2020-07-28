//
// Created by Sarah Wehelie on 3/8/20.
// Drama Movies class. Inherits from Movie Class. Implements
// its own sorting attributes.

#include "drama.h"
#include <iostream>
#include <sstream>

// Constructor. Initializes title and year
Drama::Drama(const string& Director, const string& Title) {
  this->Director = Director;
  this->Title = Title;
}

// Constructor. Initializes all local variables
Drama::Drama(const int& Stock, const string& Director, const string& Title,
        const int& Year) {
  this->Stock = Stock;
  this->Director = Director;
  this->Title = Title;
  this->Year = Year;
  this->Genre = "Drama";
}

// prints in its own format ex : D, 10, Barry Levinson,
// Good Morning Vietnam, 1988
string Drama::getFormat() const {
  ostringstream Os;
  Os << "D, "  << this->Stock << ", " << this->Director << ", "
     << this->Title << ", " << this->Year << endl;
  return Os.str();
}

// ======= GETTERS =======
int Drama::getStock() const {
  return Stock;
}

string Drama::getDirector() const {
  return Director;
}

string Drama::getGenre() const {
  return Genre;
}

string Drama::getTitle() const {
  return Title;
}

int Drama::getYear() const {
  return Year;
}

// Decreases stock
void Drama::borrowMovie() {
  if(Stock > 0) {
    Stock--;
  }
}

// Increases stock
void Drama::returnMovie() {
  Stock++;
}

// operator>. Sorts Drama based on Title and Director
// returns true if one is more than the other, false otherwise
bool Drama::moreThan(const Movie *Mv) const{
  const auto* Dm = dynamic_cast<const Drama*>(Mv);
  return ((Director > Dm->Director) ||
         ((Director == Dm->Director) && (Title > Dm->Title)));
}

// operator==. Checks if Title and Director are equal to object
// return true if equal, false otherwise
bool Drama::isEqual(const Movie *Mv) const{
  const auto* Dm = dynamic_cast<const Drama*>(Mv);
  return (this->Director == Dm->Director && this->Title == Dm->Title);
}
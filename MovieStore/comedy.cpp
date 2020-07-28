//
// Created by Sarah Wehelie on 3/8/20.
// Comedy Movies class. Inherits from Movie Class. Implements
// its own sorting attributes.
#include "comedy.h"
#include <iostream>
#include <sstream>

// Constructor. Initializes title and year
Comedy::Comedy(const string& Title, const int& Year) {
  this->Title = Title;
  this->Year = Year;
}

// Constructor. Initializes all local variables
Comedy::Comedy(const int& Stock, const string& Director, const string& Title,
        const int& Year) {
  this->Stock = Stock;
  this->Director = Director;
  this->Title = Title;
  this->Year = Year;
  this->Genre = "Comedy";
}

// prints in its own format ex : D, 10, Barry Levinson,
// Good Morning Vietnam, 1988
string Comedy::getFormat() const {
  ostringstream Os;
  Os << "F, "  << this->Stock << ", " << this->Director << ", "
     << this->Title << ", " << this->Year << endl;
  return Os.str();
}

// ======= GETTERS =======
int Comedy::getStock() const {
  return Stock;
}

string Comedy::getDirector() const {
  return Director;
}

string Comedy::getGenre() const {
  return Genre;
}

string Comedy::getTitle() const {
  return Title;
}

int Comedy::getYear() const {
  return Year;
}

// Decreases stock
void Comedy::borrowMovie() {
  if(Stock > 0) {
    Stock--;
  }
}

// Increases stock
void Comedy::returnMovie() {
  Stock++;
}

// operator==. Checks if Title and year are equal to object
// return true if equal, false otherwise
bool Comedy::isEqual(const Movie *Mv) const{
  const auto* Cm = dynamic_cast<const Comedy*>(Mv);
  return (this->Year == Cm->Year && this->Title == Cm->Title);
}

// operator>. Sorts Comedy based on Title and year
// returns true if one is more than the other, false otherwise
bool Comedy::moreThan(const Movie *Mv) const{
  const auto* Cm = dynamic_cast<const Comedy*>(Mv);
  return ((Title > Cm->Title) || ((Title == Cm->Title) && (Year > Cm->Year)));
}
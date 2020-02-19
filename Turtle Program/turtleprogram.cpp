/**
 * To practice dynamically allocated arrays and operator overloading,
 * create a TurtleProgram class that supports the following functionality.
 * For simplicity, we will use “F” instead of “Forward” and “R” instead of
 * “Right”, but assume any string or series of strings is a valid program.
 *
 * @author Sarah Wehelie
 * @date 1/17/2020
 */

#include "turtleprogram.h"
#include <cassert>

// Constructors with no parameter
TurtleProgram::TurtleProgram() {
  length = 0;
  arr = nullptr;
}

// Constructor with one parameter
TurtleProgram::TurtleProgram(const string &Command) {
  arr = new string[1];
  arr[0] = Command;
  length = 1;
}

// Constructor with two parameters
TurtleProgram::TurtleProgram(const string &Command, const string &Times) {
  arr = new string[2];
  arr[0] = Command;
  arr[1] = Times;
  length = 2;
}

// Copy constructor
TurtleProgram::TurtleProgram(const TurtleProgram &Tp) {
  length = Tp.getLength();
  arr = new string[Tp.getLength()];
  for (int I = 0; I < Tp.getLength(); I++) {
    arr[I] = Tp.arr[I];
  }
}

// accessors
// returns the number of strings in the program
int TurtleProgram::getLength() const { return length; }

// returns the nth string in the program
string TurtleProgram::getIndex(const int &I) const {
  // return index of array
  assert(length > 0 && I >= 0 && I < length);
  return arr[I];
}

// mutators
// replace the string at the given index
void TurtleProgram::setIndex(const int &I, const string &Str) {
  assert(I < this->getLength() && I >= 0);
  this->arr[I] = Str;
}

// inequality, returns true if not equal
bool TurtleProgram::operator!=(const TurtleProgram &Rhs) const {
  if (getLength() == Rhs.getLength()) {
    for (int I = 0; I < getLength(); I++) {
      if (arr[I] != Rhs.arr[I]) {
        return true;
      }
    }
  } else {
    return true;
  }
  return false;
}

// equality, returns true if equal
bool TurtleProgram::operator==(const TurtleProgram &Rhs) const {
  if (getLength() == Rhs.getLength()) {
    for (int I = 0; I < getLength(); I++) {
      if (arr[I] != Rhs.arr[I]) {
        return false;
      }
    }
  } else {
    return false;
  }
  return true;
}

// + and +=
TurtleProgram TurtleProgram::operator+(const TurtleProgram &Tp) const {
  TurtleProgram Bigger;
  Bigger.length = getLength() + Tp.getLength();
  Bigger.arr = new string[Bigger.getLength()];
  for (int I = 0; I < getLength(); I++) {
    Bigger.setIndex(I, getIndex(I));
  }
  for (int I = getLength(); I < Bigger.getLength(); I++) {
    Bigger.setIndex(I, Tp.getIndex(I - getLength()));
  }
  return Bigger;
}

TurtleProgram &TurtleProgram::operator+=(const TurtleProgram &Tp) {
  *this = (*this + Tp);
  return *this;
}

// * and *=
TurtleProgram TurtleProgram::operator*(const int &Times) const {
  assert(Times > 0 && this->arr != nullptr);
  TurtleProgram Bigger;
  for (int I = 0; I < Times; I++) {
    Bigger += *this;
  }
  return Bigger;
}

TurtleProgram &TurtleProgram::operator*=(const int &Times) {
  assert(Times > 0 && this->arr != nullptr);
  *this = (*this * Times);
  return *this;
}

// Copy assignment operator
// copies data into new object
TurtleProgram &TurtleProgram::operator=(const TurtleProgram &Rhs) {
  // copy assignment
  if (this != &Rhs) {
    delete[] this->arr;
    this->arr = nullptr;
    this->length = Rhs.getLength();
    this->arr = new string[this->length];
    for (int I = 0; I < this->length; I++) {
      this->arr[I] = Rhs.arr[I];
    }
  }
  return *this;
}

// destructor
TurtleProgram::~TurtleProgram() {
  delete[] arr;
  arr = nullptr;
  length = 0;
}

// --------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class Array
ostream &operator<<(ostream &Out, const TurtleProgram &Tp) {
  Out << "[";
  for (int I = 0; I < Tp.getLength() - 1; I++) {
    Out << Tp.arr[I] << " ";
  }
  Out << Tp.arr[Tp.getLength() - 1] << "]";
  return Out; // e.g., enables cout << x << y;
}

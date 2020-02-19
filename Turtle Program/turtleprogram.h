/**
 * TODO file documentation
 *
 * @author TODO
 * @date TODO
 */

#ifndef TURTLEPROGRAM_H
#define TURTLEPROGRAM_H

#include <iostream>
#include <string>

using namespace std;

class TurtleProgram {
    // operator<<
    // Overloaded output operator for class Array
    friend ostream &operator<<(ostream &Out, const TurtleProgram &Tp);

public:
  // Constructor with no parameter
  TurtleProgram();
  // Constructor with one parameter
  explicit TurtleProgram(const string &Command);
  // Constructor with two parameter
  TurtleProgram(const string &Command, const string &Times);
  // Copy Constructor
  TurtleProgram(const TurtleProgram &Tp);
  // Destructor
  virtual ~TurtleProgram();

  // accessors
  int getLength() const;
  string getIndex(const int &I) const;
  // mutator
  void setIndex(const int &I, const string &Str);

  // Equality and inequality operators
  bool operator==(const TurtleProgram &Rhs) const;
  bool operator!=(const TurtleProgram &Rhs) const;

  // Copy assignment operator
  TurtleProgram &operator=(const TurtleProgram &Rhs);
  // Addition operator : +, +=
  TurtleProgram operator+(const TurtleProgram &Tp) const;
  TurtleProgram &operator+=(const TurtleProgram &Tp);
  // Multiplication Operator : *, *=
  TurtleProgram operator*(const int &Times) const;
  TurtleProgram &operator*=(const int &Times);

private:
    // local variables
    int length;
    string* arr;

};

#endif // TURTLEPROGRAM_H

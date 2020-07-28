//
// Created by Sarah Wehelie on 3/8/20.
// Classic movie class. Inherits from Movie Class.
// Implements unique sorting attributes.

#ifndef MOVIESTORE_CLASSICS_H
#define MOVIESTORE_CLASSICS_H
#include <string>
#include "movie.h"
using namespace std;

class Classics : public Movie{
public:
    // Constructor. Initializes actor, month, year
    Classics(const string& Actor, const int& Month, const int& Year);
    // Constructor. Initializes all local variables
    Classics(const int& Stock, const string& Director, const string& Title,
            const string& Actor, const int& Month, const int& Year);
    ~Classics() override = default;
    // prints in its own format ex: C, 10, Hal Ashby, Harold and Maude,
    // Ruth Gordon 3 1971
    string getFormat() const override;
    // operator>. Sorts Classics based on Actor, Month, Year
    // returns true if one is more than the other, false otherwise
    bool moreThan(const Movie *Mv) const override;
    // operator==. Checks if Actor, Month, and Year are equal
    // return true if equal, false otherwise
    bool isEqual(const Movie *Mv) const override;

    // ======= GETTERS =======
    int getStock() const override;
    int getYear() const override;
    string getDirector() const override;
    string getTitle() const override;
    string getGenre() const override;
    // Decreases stock
    void borrowMovie() override;
    // Increases stock
    void returnMovie() override;

private:
    // local variables
    int Stock;
    string Director;
    string Title;
    string Actor;
    int Month;
    int Year;
    string Genre;
};
#endif //MOVIESTORE_CLASSICS_H

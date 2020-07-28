//
// Created by Sarah Wehelie on 3/8/20.
// Drama Movies class. Inherits from Movie Class. Implements
// its own sorting attributes.

#ifndef MOVIESTORE_DRAMA_H
#define MOVIESTORE_DRAMA_H
#include <string>
#include "movie.h"
using namespace std;

class Drama : public Movie{
public:
    // Constructor. Initializes title and year
    Drama(const string& Director, const string& Title);
    // Constructor. Initializes all local variables
    Drama(const int& Stock, const string& Director, const string& Title,
            const int& Year);
    ~Drama() override = default;
    // prints in its own format ex : D, 10, Barry Levinson,
    // Good Morning Vietnam, 1988
    string getFormat() const override;
    // operator>. Sorts Drama based on Title and Director
    // returns true if one is more than the other, false otherwise
    bool moreThan(const Movie *Mv) const override;
    // operator==. Checks if Title and Director are equal to object
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
    int Year;
    string Genre;
};

#endif //MOVIESTORE_DRAMA_H

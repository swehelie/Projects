//
// Created by Sarah Wehelie on 3/8/20.
// Abstract class of Comedy, Classics, and Drama.
// Child Classes will implement all the virtual functions.

#ifndef MOVIESTORE_MOVIE_H
#define MOVIESTORE_MOVIE_H
#include <string>
#include <iostream>

using namespace std;
class Movie{
public:
    // constructor
    Movie() = default;
    // destructor
    virtual ~Movie() = default;
    // Creates movie objects
    // returns movie* of object if successful, nullptr otherwise
    static Movie* create(string Line);

    // VIRTUAL functions that Child classes wil implement
    virtual string getFormat() const = 0;
    virtual bool isEqual(const Movie *Mv) const = 0;
    virtual bool moreThan(const Movie *Mv) const = 0;
    virtual int getStock() const = 0;
    virtual int getYear() const = 0;
    virtual string getDirector() const = 0;
    virtual string getTitle() const = 0;
    virtual string getGenre() const = 0;
    virtual void borrowMovie() = 0;
    virtual void returnMovie() = 0;

};
#endif //MOVIESTORE_MOVIE_H

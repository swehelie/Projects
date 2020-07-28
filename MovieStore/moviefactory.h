//
// Created by Sarah Wehelie on 3/8/20.
// Abstract class of Movie. Has virtual function that creates
// the movie objects (C, D, F).

#ifndef MOVIESTORE_MOVIEFACTORY_H
#define MOVIESTORE_MOVIEFACTORY_H
#include <string>
#include "movie.h"

using namespace std;
class Movie;
class MovieFactory{
    // not implemented
virtual Movie* create() const = 0;
};
#endif //MOVIESTORE_MOVIEFACTORY_H

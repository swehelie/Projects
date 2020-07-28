//
// Created by Sarah Wehelie on 3/8/20.
// Abstract class of Comedy, Classics, and Drama.
// Child Classes will implement all the virtual functions.
#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classics.h"
#include <iostream>
#include<sstream>
using namespace std;

// Creates movie objects
// returns movie* of object if successful, nullptr otherwise
Movie* Movie::create(string Line) {
  Movie* Mv = nullptr;
  char MovieType = Line[0];
  switch(MovieType){
    case 'C': {
      // print out the movie type, stock, director, title, major
      // actor, release month, and release year
      stringstream ss(Line);
      int Stock = 0;
      string Space;
      getline(ss, Space, ' ');
      ss >> Stock;
      getline(ss, Space, ' ');
      string Director;
      getline(ss, Director, ',');
      ss.get();
      string Title;
      getline(ss, Title, ',');
      getline(ss, Space, ' ');
      string ActorF, ActorL, ActorFull;
      getline(ss, ActorF, ' ');
      getline(ss, ActorL, ' ');
      ActorFull = ActorF + " " + ActorL;
      int Month, Year;
      ss >> Month;
      ss >> Year;
      Mv = new Classics(Stock, Director, Title, ActorFull, Month, Year);
      break;
    }
    case 'D' : {
      stringstream ss(Line);
      int Stock = 0;
      string Space;
      getline(ss, Space, ' ');
      ss >> Stock;
      getline(ss, Space, ' ');
      string Director;
      getline(ss, Director, ',');
      ss.get();
      string Title;
      getline(ss, Title, ',');
      getline(ss, Space, ' ');
      int Year;
      ss >> Year;
      Mv = new Drama(Stock, Director, Title, Year);
      break;
    }
    case 'F' : {
      stringstream ss(Line);
      int Stock = 0;
      string Space;
      getline(ss, Space, ' ');
      ss >> Stock;
      getline(ss, Space, ' ');
      string Director;
      getline(ss, Director, ',');
      ss.get();
      string Title;
      getline(ss, Title, ',');
      getline(ss, Space, ' ');
      int Year;
      ss >> Year;
      Mv = new Comedy(Stock, Director, Title, Year);
      break;
    }
    default:
      return Mv;
  }
  return Mv;
}
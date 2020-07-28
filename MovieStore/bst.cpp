//
// Created by Sarah Wehelie on 3/8/20.
// A Binary Search Tree class that is responsible for containing
// and sorting the Movie Types. Each Node contains a Movie pointer.
#include "bst.h"
#include "movie.h"
#include <iostream>
using namespace std;

// ===== Constructor =====
BinarySearch::BinarySearch(){
  Root = nullptr;
}

// ===== Destructor =====
BinarySearch::~BinarySearch() {
  clear();
}

// Checks if tree is Empty, true if empty
// false otherwise
bool BinarySearch::isEmpty() const {
  return (Root == nullptr);
}

// Deletes all the nodes from the tree
void BinarySearch::clear() {
  clearH(Root);
}

// clear function helper
void BinarySearch::clearH(Node* Curr){
  if(Curr == nullptr){
    return;
  }
    clearH(Curr->Left);
    clearH(Curr->Right);
    delete Curr->Data;
    Curr->Data = nullptr;
    delete Curr;
}

// Adds movie pointers into tree depending on sorting attributes
// returns true when added, false if already present
bool BinarySearch::insert(Movie *Mv) {
  return insertH(Root, Mv);
}

// insert function helper
bool BinarySearch::insertH(Node *&Curr, Movie *Mv) {
  if(Curr == nullptr){
    Curr = new Node();
    Curr->Data = Mv;
    Curr->Left = Curr->Right = nullptr;
    return true;
  }
  if(Curr->Data->isEqual(Mv)){
    Curr->Data->returnMovie();
    delete Mv;
    return true;
  }
  if(Curr->Data->moreThan(Mv)){
    return insertH(Curr->Left, Mv);
  }
  else{
    return insertH(Curr->Right, Mv);
  }
}

// Searches for Movie pointer in tree,
// returns movie pointer if found, nullptr otherwise
Movie* BinarySearch::retrieve(const Movie *Mv) {
  return retrieveH(Root, Mv);
}

// retrieve function helper, used in Transaction class
Movie* BinarySearch::retrieveH(Node *&Curr,
                               const Movie *Mv) const {
  if (Curr == nullptr) {
    return nullptr;
  }
  if (Curr->Data->isEqual(Mv)) {
    return Curr->Data;
  } else if (Curr->Data->moreThan(Mv)) {
    return retrieveH(Curr->Left, Mv);
  } else {
    return retrieveH(Curr->Right, Mv);
  }
}

// Prints all movies in the tree
void BinarySearch::printOutput() {
  inOrder(Root);
}

// prints movies inOrder
void BinarySearch::inOrder(Node *Curr) const {
  if(Curr == nullptr) { return; }
  inOrder(Curr->Left);
  cout << Curr->Data->getFormat();
  inOrder(Curr->Right);
}
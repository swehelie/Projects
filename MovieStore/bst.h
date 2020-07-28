//
// Created by Sarah Wehelie on 3/8/20.
// A Binary Search Tree class that is responsible for containing
// and sorting the Movie Types. Each Node contains a Movie pointer.

#ifndef MOVIESTORE_BST_H
#define MOVIESTORE_BST_H

#include "movie.h"

class Movie;
class BinarySearch{
    struct Node{
        Movie* Data;
        Node* Left;
        Node* Right;
    };
public:
    // ===== Constructor =====
    BinarySearch();
    // ===== Destructor =====
    ~BinarySearch();
    // Deletes all the nodes from the tree
    void clear();
    // Checks if tree is Empty, true if empty
    // false otherwise
    bool isEmpty() const;
    // Searches for Movie pointer in tree,
    // returns movie pointer if found, nullptr otherwise
    Movie* retrieve(const Movie* Mv);
    // Adds movie pointers into tree depending on sorting attributes
    bool insert(Movie* Mv);
    // Prints all movies in the tree
    void printOutput();

private:
    // local variable
    Node* Root;
    // clear function helper
    void clearH(Node* Curr);
    // retrieve function helper
    Movie* retrieveH(Node*& Curr, const Movie* Mv) const;
    // prints movies inOrder
    void inOrder(Node* Curr) const;
    // insert function helper
    bool insertH(Node*& Curr, Movie* Mv);
};
#endif //MOVIESTORE_BST_H

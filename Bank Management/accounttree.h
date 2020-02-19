
#include "account.h"
#include <iostream>
using namespace std;
#ifndef ACCOUNTTREE_H
#define ACCOUNTTREE_H

class AccountTree {
public:
  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, Account *&Account) const;

  // Display information on all accounts
  void display() const;

  // // delete all information in AccountTree
  // void clear();

  // check if tree is empty
  bool isEmpty() const;

    // delete all information in AccountTree
  void clear();

private:
  struct Node {
    Account *Acc;
    Node *Right;
    Node *Left;
  };
  Node *Root;

    //binary search function using the account number, root Node, and *account
    //returns false when account is not present in tree
  bool recursiveSearch(Node *Curr, const int &ID, Account *&Acc) const;
  //starting from the root
//recursively inserts node on either left or right of BST
//returns true when after inserting false if already inserted
  bool recursiveInsert(Account *Acc, Node *&Curr);
    // Display information on all accounts using in order
  void printInOrder(Node* Curr) const;
   // delete all information in AccountTree
  void Delete(Node *Curr);
};
#endif
// ACCOUNTTREE_H

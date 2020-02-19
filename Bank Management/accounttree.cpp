#include "accounttree.h"
#include <iostream>
#include <ostream>
using namespace std;

//constructor
AccountTree::AccountTree(){
  Root = nullptr;
}

// Delete all nodes in BST
AccountTree::~AccountTree(){
  AccountTree::clear();
}

// Insert new account
bool AccountTree::insert(Account *Account) {
  if(Root != nullptr) {
    return recursiveInsert(Account, Root);
  }
  //if root is null, creates new root
  else{
      Root = new Node;
      Root->Acc = Account;
      Root->Left = nullptr;
      Root->Right = nullptr;
      return true;
  }
}
//creates new parent on the tree

//starting from the root
//recursively inserts node on either left or right of BST
//returns true when after inserting false if already inserted
bool AccountTree::recursiveInsert(Account *Acc, Node *&Curr){
  //if ID given is less than the parent, place it on left
  //else create new left node
    if (Acc->getID() < Curr->Acc->getID()) {
        if (Curr->Left != nullptr) {
            return recursiveInsert(Acc, Curr->Left);
        }
        //if left node is null, created new node
        //and connects to account info
        else {
            Curr->Left = new Node;
            Curr->Left->Acc = Acc;
            Curr->Left->Left = nullptr;
            Curr->Right->Right = nullptr;
            return true;
        }
    }
    else if(Acc->getID()>Curr->Acc->getID()) {
        if (Curr->Right != nullptr) {
            return recursiveInsert(Acc, Curr->Right);
        }
        //if right node is null, created new node
        //and connects to account info
        else {
            Curr->Right = new Node;
            Curr->Right->Acc = Acc;
            Curr->Right->Left = nullptr;
            Curr->Right->Right = nullptr;
            return true;
        }
    }
    else{
        return false;
    }
}
// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
    return Root == nullptr ? false : recursiveSearch(Root, AccountNumber,
                                                     Account);
}

//binary search function using the account number, root Node, and *account
//returns false when account is not present in tree
bool AccountTree::recursiveSearch(Node *Curr, const int &ID, Account *&Acc)
                                                                       const{
    if (Curr != nullptr){
        //checks if ID given matches the ID in node, return true if found
        //connects account to node
        if (Curr->Acc->getID() == ID) {
            Acc = Curr->Acc;
            return true;
        }
        //if ID given is less than the one on the binary search tree,
        // then checks the left
        else if (ID < Curr->Acc->getID()) {
            return recursiveSearch(Curr->Left, ID, Acc);
        }
        //if ID given is more than the one on the binary search tree,
        // then checks the right
        else {
            return recursiveSearch(Curr->Right, ID, Acc);
        }
    }
    return false;
}

// Display information on all accounts
void AccountTree::display() const {
  printInOrder(Root);
}
//uses in order pattern to display the tree
void AccountTree::printInOrder(Node* Curr) const{
  if(Curr!= nullptr){
    printInOrder(Curr->Left);
    cout << *(Curr->Acc) << endl;
    printInOrder(Curr->Right);
  }
}
// delete all information in AccountTree
void AccountTree::Delete(Node *Curr) {
  if(Curr != nullptr){
    Delete(Curr->Left);
    Delete(Curr->Right);
    delete Curr->Acc;
    Curr->Acc = nullptr;
    Curr->Left = nullptr;
    Curr->Right = nullptr;
    delete Curr;
    Curr = nullptr;
  }
}
//calls on delete to remove individual nodes
void AccountTree::clear(){
    AccountTree::Delete(Root);
}

// check if tree is empty
bool AccountTree::isEmpty() const {
    return Root == nullptr;
}
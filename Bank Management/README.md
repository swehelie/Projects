# JollyBanker


## Purpose
This lab will serve a few purposes. First, it will provide hands-on experience using both queues and binary search trees. It will also provide an opportunity for further program/class design as the project does not specifically delineate class structure or design.

There are aspects of the spec below which allow interpretation—please read/design and ask questions early to clarify any ambiguity.
A peer design review will be required to help with the latter aspect. This design review will require a deliverable to canvas and will be part of the final grade for the lab.

Problem Overview:
You will build a banking application which processes transactions. This banking application consists of three phases.
1) The program will read in a string of transactions from a file into an in-memory queue. These transactions can open accounts, withdraw funds, deposit funds, transfer funds, or ask for the transactional history to be printed.
2) The program will next read from the queue and process the transactions in order.
3) When the queue has been depleted the program will print out all open accounts and balances in those accounts.


## Compile and Run

```
g++ -std=c++14 -g -Wall -Wextra *.cpp
valgrind ./a.out
```

#Explanation

Funds.cpp and Funds.H file were created to accomodate a string vector and help the functions in the Account file. The Funds object was called in the "Funds" vector in Account.h. This is used to collect the fund name and push the messages into the vector so that they could later be printed. It also aids in depositing and withdrawing the balance with proper error messages.

The Info struct is supposed to act as collecting information for the transaction in the Bank class. It is stored in the queue during processTransactions and then accessed during handleQueue, while it is unloading the queue. 

The Account class has the bulk of the operations in the program, which is responsible for Deposit, Withdraw, and Transfer.

BanTransIn1.txt is one of our text files that tests some of the requirements that are not included in the original file.

I've tried my best to indent and follow the 80 column requirement.



## Misc

This file is part of a repository located at
https://github.com/pisan342/ass5-banker-starter


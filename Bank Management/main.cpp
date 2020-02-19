
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;
//int Argc, char *Argv[]
int main() {
    Bank Bank;
//    Note that tests were done in BankTransIn.txt
//     for(int I = 1; I < Argc; ++I) {
//         cout << "The command line argument(s) was " << Argv[I] << std::endl;
//         string FileName = Argv[I];
//         Bank.processTransactions("BankTransIn.txt");
//     }
    Bank.processTransactions("BankTransIn.txt");
    Bank.handleQueue();
    cout << endl;
    cout << "Processing done. Displaying all balances..." << endl;
    Bank.displayAllBankBalances();
    return 0;
}
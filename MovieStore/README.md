# Movie Store

## Replace all TODO with actual information

Author(s): Sarah Wehelie

GitHub URL: https://github.com/uwbclass/uwb2020wi343b-movies-sarahyw10/tree/74f40674d318501dc081a72bb6d03431c43e83fc

Expected Mark: ~110

## Checklist

Development Platform: CLion

Tested on CSS Linux Lab: Yes

Tested on Travis: Yes

clang-tidy messages:

<<<<<<< HEAD
-cert-err58-cpp: Using static variable which may cause throw

-cppcoreguidelines-avoid-magic-numbers: magic numbers needed for testing

-cppcoreguidelines-owning-memory: not using gsl, so assigning new owners

-cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert

-cppcoreguidelines-pro-bounds-constant-array-index: array index not constant

-cppcoreguidelines-pro-bounds-pointer-arithmetic: need to use array indexes

-cppcoreguidelines-special-member-functions: no move constructor or move assignment for now

-fuchsia-*: Checks specific to fuschia system

-google-build-using-namespace: for simplicity allow using namespace std;

-google-global-names-in-headers: OK to say using namespace std; for class code

-google-readability-braces-around-statements: allow compact code without {

-hicpp-braces-around-statements: want compact code

-hicpp-no-array-decay: allow assert

-hicpp-special-member-functions: no move constructor or move assignment for now

-llvm-header-guard: header guards do not have full directory name

-modernize-pass-by-value: Not using move for objects

-modernize-use-trailing-return-type: not ready for auto func() -> int format yet

-readability-braces-around-statements: allow compact code without { (this option 9.0.0) is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using

-readability-magic-numbers: needed for testing

-llvm-include-order - shouldn't affect program

-hicpp-use-auto - more modern form of iterations

-modernize-use-auto - using for iterations

-readability-else-after-return - need for functions

-readability-redundant-string-init - initializes string

-google-runtime-references - doesn't affect program

-readability-identifier-naming - not enough time to change

=======
cert-err58-cpp: Using static variable which may cause throw
cppcoreguidelines-avoid-magic-numbers: magic numbers needed for testing
cppcoreguidelines-owning-memory: not using gsl, so assigning new owners
cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
cppcoreguidelines-pro-bounds-constant-array-index: array index not constant
cppcoreguidelines-pro-bounds-pointer-arithmetic: need to use array indexes
cppcoreguidelines-special-member-functions: no move constructor or move assignment for now
fuchsia-*: Checks specific to fuschia system
google-build-using-namespace: for simplicity allow using namespace std;
google-global-names-in-headers: OK to say using namespace std; for class code
google-readability-braces-around-statements: allow compact code without {
hicpp-braces-around-statements: want compact code
hicpp-no-array-decay: allow assert
hicpp-special-member-functions: no move constructor or move assignment for now
llvm-header-guard: header guards do not have full directory name
modernize-pass-by-value: Not using move for objects
modernize-use-trailing-return-type: not ready for auto func() -> int format yet
readability-braces-around-statements: allow compact code without { (this option 9.0.0) is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using
readability-magic-numbers: needed for testing
llvm-include-order - shouldn't affect program
hicpp-use-auto - more modern form of iterations
modernize-use-auto - using for iterations
readability-else-after-return - need for functions
readability-redundant-string-init - initializes string
google-runtime-references - doesn't affect program
readability-identifier-naming - not enough time to change
>>>>>>> 71e1f8caf50071a41e555e31acd69ec03c8a5ae2
-cppcoreguidelines-pro-type-member-init - didn't need to change it to default

valgrind messages: 
definitely lost: 0 bytes in 0 blocks
1609==4293==    indirectly lost: 0 bytes in 0 blocks
1610==4293==      possibly lost: 0 bytes in 0 blocks
1611==4293==    still reachable: 72,704 bytes in 1 blocks
1612==4293==         suppressed: 0 bytes in 0 blocks

## Command Functionality Checklist

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: [transaction.cpp] create(string& Line)
ERR:: INVALID COMMAND - Z

invalid movie type: [transaction.cpp] create(string& Line)
ERR:: INVALID MOVIE CODE - Z

invalid customer ID: [transaction.cpp] create(string& Line)
 ERR:: CUSTOMER ID 1234 IS NOT VALID.
 
 invalid movie: [transaction.cpp] create(string& Line)

ERR:: THE MOVIE D: Bogus Title Steven Spielberg DOES NOT EXIST. 

factory classes: moviefactory.h and transactionfactory.h

hashtable: The hashtable is used for keeping track of the Customers and making sure that they're ID's are valid.
[hashtable.h] [hashtable.cpp]

container used for comedy movies: Binary Search Tree

function for sorting comedy movies: insert() and retrieve() in [bst.cpp]
also isEqual and moreThan in Comedy, Classics, and Drama classes.

function where comedy movies are sorted: insert() and retrieve() in [bst.cpp]
also isEqual and moreThan

functions called when retrieving a comedy movie based on title and year: [transaction.cpp] create(string& Line)
in the MovieC if statements

functions called for retrieving and printing customer history: in History Class,
calls transact() and printTransactions() function from Customer class

container used for customer history: queue used keep record of transactions

functions called when borrowing a movie: getStock(), addMovie from BST,
addTransaction from Customer, and borrowMovie to update stock

explain borrowing a movie that does not exist: Should return error that
the movie does not exist.

explain borrowing a movie that has 0 stock: prints Out of stock error

explain returning a movie that customer has not checked out: prints error
that states that the movie does not exist in customer history

any static_cast or dynamic_cast used: Movie pointers in Comedy, Classics, and Drama were dynamically casted for the overloading operators, isEqual and moreThan.



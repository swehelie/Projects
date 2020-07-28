cmake_minimum_required(VERSION 3.5)
project(moviestore)

set(CMAKE_CXX_STANDARD 14)

# have compiler give warnings, but not for signed/unsigned
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-sign-compare")

# need to load data files from current directory as cpp files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(moviestore.exe main.cpp store_test.cpp store.cpp store.h customer.cpp
        customer.h moviefactory.h comedy.h comedy.cpp drama.h drama.cpp classics.h
        classics.cpp hashtable.h hashtable.cpp transaction.h transaction.cpp borrow.h
        borrow.cpp return.h return.cpp movie.h movie.cpp bst.h bst.cpp inventory.h history.h history.cpp inventory.cpp transactionfactory.h)
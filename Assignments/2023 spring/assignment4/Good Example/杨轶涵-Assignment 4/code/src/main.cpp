#include "gtest/gtest.h"
#include "../include/login.h"
using namespace login;

#include <iostream>

int main (int argc, char *argv[]) {

    if (false) // make false to run unit tests  
    { 
        Login L;
        L.readFile( "./users.txt" );
        std::cout << "Check if user1 is in user lists:  ";
        std::cout << ( L.getUser( "user1" ) != nullptr ? "Yes" : "No" ) << std::endl;
        std::cout << "Check if user4 is in user lists:  ";
        std::cout << ( L.getUser( "user4" ) != nullptr ? "Yes" : "No" ) << std::endl;
        std::cout << "Check if user5 is in user lists:  ";
        std::cout << ( L.getUser( "user5" ) != nullptr ? "Yes" : "No" ) << std::endl;

        std::cout << "Check if user1 is logged in:  ";
        std::cout << ( L.checkLoggedin( "user1" ) ? "Yes" : "No" ) << std::endl;
        std::cout << "Check if user2 is logged in:  ";
        std::cout << ( L.checkLoggedin( "user3" ) ? "Yes" : "No" ) << std::endl;
    } 
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}
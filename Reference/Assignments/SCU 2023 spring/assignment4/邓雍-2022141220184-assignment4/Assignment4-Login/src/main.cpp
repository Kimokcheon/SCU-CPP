#include "gtest/gtest.h"
#include "../include/login.h"


#include <iostream>

int main (int argc, char *argv[]) {

    if (false) // make false to run unit tests  
    { 
        // debug section 
    } 
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}
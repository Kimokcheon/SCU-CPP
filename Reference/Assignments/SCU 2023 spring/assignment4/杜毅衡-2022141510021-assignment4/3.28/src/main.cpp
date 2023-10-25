#include "gtest/gtest.h"
#ifndef _login_h
#define _login_h
#include "../include/login.h"
#endif


#include <fstream>
#include <iostream>
using namespace std;

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
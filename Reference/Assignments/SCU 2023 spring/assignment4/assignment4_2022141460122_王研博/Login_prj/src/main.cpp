//#include "gtest/gtest.h"
#include "../include/login.h"


int main (int argc, char *argv[]) {

    if(true) // make false to run unit tests
    {


    }
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}
#include <iostream>
#include "assignment5.h"
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    // auto table = read_csv("dataset.csv");
    // std::cout<<table.size()<<std::endl;
    // auto books = defineBooks(&table);
    // std::cout<<books.size();
    // std::cout<<books[4].getAuthorName()<<std::endl;


    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
        std::cout << "<<<SUCCESS>>>" << std::endl;
    else
        std::cout << "FAILED" << std::endl;
    return 0;

    
}

#include <iostream>
#include "../h/linkedlist.h"
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
        std::cout << "<<<SUCCESS>>>" << std::endl;
    else
        std::cout << "FAILED" << std::endl;
//    LinkedList a = LinkedList{1, 2, 3};
//    std::cout << a[2];
    return 0;
}

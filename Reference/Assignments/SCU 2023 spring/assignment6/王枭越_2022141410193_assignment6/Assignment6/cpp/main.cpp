#include <iostream>
#include "gtest/gtest.h"
#include "../h/linkedlist.h"

int main(int argc, char **argv)
{
    if(false){
        LinkedList list;
        std::cout<<list.getSize()<<std::endl;
        list.show();
        list.push_front(1919);
        list.push_back(114);
        list.push_back(514);
        list.show();
        std::cout<<list.pop_back()<<std::endl;
        list.show();
        std::cout<<list.pop_front()<<std::endl;
        list.show();
        std::cout<<list.empty()<<std::endl;
        std::cout<<list.getSize()<<std::endl;
        // list.clear();
        // std::cout<<list.getSize()<<std::endl;
        LinkedList list_(list);
        LinkedList list_2{1,2,3,4,5};
        list_.show();
        // list_.clear();
        list_.push_back(514);
        list.push_back(514);
        list_.extend(list);
        list_.extend(list_2);
        list_.show();
    }else{
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
        return 0;
    }
}

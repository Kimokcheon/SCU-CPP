#include "gtest/gtest.h"
#include "../include/login.h"


#include <iostream>

int main (int argc, char *argv[]) {

    if (false) // make false to run unit tests  
    { 
        // debug section 
        // Login l;
        // l.readFile("./src/users.txt");
        // for(auto it:l.users){
        //     std::cout<<std::setw(10)<<std::left<<it->username<<it->password<<it->email<<std::endl;
        // }
        // l.removeUser("user2");
        // for(auto it:l.users){
        //     std::cout<<std::setw(10)<<std::left<<it->username<<it->password<<it->email<<std::endl;
        // }
        // l.changeUsername("user1","114");
        // for(auto it:l.users){
        //     std::cout<<std::setw(10)<<std::left<<it->username<<it->password<<it->email<<std::endl;
        // }
    } 
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}
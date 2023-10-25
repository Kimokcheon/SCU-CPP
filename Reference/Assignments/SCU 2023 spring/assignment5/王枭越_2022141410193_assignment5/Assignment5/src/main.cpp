#include <iostream>
#include "../include/assignment5.h"
#include "gtest/gtest.h"

int main(int argc, char **argv)
{   
    if(false){
        Dataframe tmp=read_csv("../dataset.csv");
        // for(int i=0;i<tmp.size();++i){
        //     for(int j=0;j<tmp[i].size();++j){
        //         std::cout<<tmp[i][j]<<" ";
        //     }
        //     std::cout<<std::endl;
        // }
        std::vector<Book> t=defineBooks(&tmp);
        // for(auto it:t){
        //     std::cout<<it.gettitle()<<std::endl;
        // }
        std::cout<<tmp.size()<<std::endl;
        showTable(&tmp,0,20);
    }else{
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}

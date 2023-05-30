#include <gtest/gtest.h>
#include <iostream>
#include <map.h>

int main( int argc, char **argv ) {
    if( false ) {
        Project::map<int,int> M;
        M[3] = 4;
        M.erase( 3 );
        std::cout << M[5] << std::endl;
        std::cout << M.count( 5 ) << std::endl;
        auto it = M.lower_bound( 4 );
        M[7] = 4;
        M[10] = 5;
        M[8] = 33;
        std::cout << ( it -> first ) << std::endl;
        it += 2;
        std::cout << ( it -> first ) << std::endl;
    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
}
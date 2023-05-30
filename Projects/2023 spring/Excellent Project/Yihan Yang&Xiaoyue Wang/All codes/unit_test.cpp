#include "gtest/gtest.h"
#include "_SB_tree.h"
#include <set>
#include <map>
#include <random>
#include <map.h>
std::mt19937 rng( std::chrono::steady_clock::now().time_since_epoch().count() );

namespace {

template<typename Key,typename Value>
void fill_in( Project::map<Key,Value>& T , std::map<Key,Value>& S ) {
    for( int i = 1 ; i <= 510 ; ++ i ) 
        T[i * 2 + 3] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 ) , S[i * 2 + 3] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 );
    for( int i = 250 ; i >= 40 ; -- i ) 
        T[i * 4 + 3] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 ) , S[i * 4 + 3] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 );
}

template<typename Key,typename Value>
void insert_random( Project::map<Key,Value>& T , std::map<Key,Value>& S , int num = 1 ) {
    T.try_debug( );
    for( int i = 1 ; i <= num ; ++ i ) {
        int key = rng() % 1024 , val = rng() % 1024;
        T[key] = val;
        S[key] = val;
    }
}

TEST( size_balanced_tree , insert_small_int_1 ) {
    _Sb_tree::_Sb_tree<int,int,std::_Identity<int>,std::less<int>> T;
    std::set<int> S;
    S.insert( 3 );
    S.insert( 5 );
    S.insert( 2147483647 );
    S.insert( 1004535809 );
    S.insert( 998244353 );
    S.insert( 114514 );
    for( int x : S ) T._M_insert_unique( x );
    auto itr = T.begin();
    for( auto it = S.begin() ; it != S.end() ; ++ it , ++ itr ) {
        EXPECT_EQ( *it , *itr );
    }
}

TEST( size_balanced_tree , copy_construct ) {
    _Sb_tree::_Sb_tree<int,int,std::_Identity<int>,std::less<int>> T , F;
    std::set<int> S , G;

    for( int i = 1 ; i <= 70 ; ++ i ) T._M_insert_unique( i ) , S.insert( i );
    for( int i = 200 ; i >= 40 ; -- i ) T._M_insert_unique( i ) , S.insert( i );
    for( int i = 1 ; i <= 90 ; ++ i ) {
        int v = rng() % 1000;
        T._M_insert_unique( v );
        S.insert( v );
    }

    auto its = S.begin();
    auto itt = T.begin();
    while( its != S.end() ) {
        EXPECT_EQ( *its , *itt );
        ++ its , ++ itt;
    }

    G = S , F = T;

    its = G.begin();
    itt = F.begin();
    while( its != G.end() ) {
        EXPECT_EQ( *its , *itt );
        ++ its , ++ itt;
    }

}

TEST( size_balanced_tree , copy_construct_map ) {
    Project::map<int,int> T , F;
    std::map<int,int> S , G;

    for( int i = 1 ; i <= 70 ; ++ i ) T[i] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 ) , S[i] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 );
    for( int i = 70 ; i >= 40 ; -- i ) 
        T[i] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 ) , S[i] = ( ( i * 3 ^ 1047 ) + 6242 ^ 4921 );

    auto its = S.begin();
    auto itt = T.begin();
    while( its != S.end() ) {
        EXPECT_EQ( *its , *itt );
        ++ its , ++ itt;
    }

    G = S , F = T;

    its = G.begin();
    itt = F.begin();
    while( its != G.end() ) {
        EXPECT_EQ( *its , *itt );
        ++ its , ++ itt;
    }

    std::map<int,int> pS( S );
    auto pT( T );

    its = pS.begin();
    itt = pT.begin();
    while( its != pS.end() ) {
        EXPECT_EQ( *its , *itt );
        ++ its , ++ itt;
    }
}

TEST( size_balanced_tree , basic_info ) {
    Project::map<int,int> T , F;
    std::map<int,int> S , G;

    fill_in( T , S );

    for( int t = 1 ; t <= 1000 ; ++ t ) {
        EXPECT_EQ( T.size() , S.size() );
        EXPECT_EQ( *S.begin() , *T.begin() );
        EXPECT_EQ( *S.rbegin() , *( -- T.end() ) );
        insert_random( T , S , rng( ) % 3 );
        // std::cout << t << std::endl;
    }
    

}

TEST( size_balanced_tree , iterator ) {
    Project::map<int,int> T , F;
    std::map<int,int> S , G;
    
    for( int k = 1 ; k <= 5 ; ++ k )
        insert_random( T , S );
    // Test ++ / --
    for( int t = 1 ; t <= 100 ; ++ t ) {
        int val = rng() % 150;
        auto itt = T.lower_bound( val );
        auto its = S.lower_bound( val );
        if( its != S.begin() ) {
            -- its;
            -- itt;
        }
        EXPECT_EQ( *its , *itt );
        for( int i = 0 ; i < rng() % 3 ; ++ i ) {
            insert_random( T , S );
        }
    }

    // Test +=k , -=k

    for( int t = 1 ; t <= 100 ; ++ t ) {
        int v = rng() % 1024;
        auto itt = T.lower_bound( v );
        auto its = S.lower_bound( v );
        int times = 0 , ext = rng() % 20;
        while( its != S.end() && times < ext ) {
            ++ times , ++ its;
        }
        // for( int tim = 0 ; tim < times ; ++ tim )
        //     itt ++;
        // std::cerr << t << ' ' << times << ' ' << ( its == S.end() ) << std::endl;
        itt += times;
        // std::cerr << t << std::endl;
        if( its != S.end() )
            EXPECT_EQ( *its , *itt );
        insert_random( T , S );
    }

    // Test distance

    for( int t = 1 ; t <= 10 ; ++ t ) {
        int vl = rng() % 1024 , vr = rng() % 1024;
        auto ittl = T.lower_bound( vl ) , ittr = T.lower_bound( vr );
        auto itsl = S.lower_bound( vl ) , itsr = S.lower_bound( vr );
        int g = rng( ) % 1024;
        if( vr > vl ) {
            // std::cout << ittl -> first << ' ' << ittr -> first << std::endl;
            EXPECT_EQ( ittl <= ittr , 1 );
            if( itsl != itsr ) 
                EXPECT_EQ( ittl < ittr , 1 );
            else 
                EXPECT_EQ( ittl == ittr , 1 );
        }
        if( vl > vr ) {
            EXPECT_EQ( ittl >= ittr , 1 );
            if( itsl != itsr )
                EXPECT_EQ( ittl > ittr , 1 );
            else 
                EXPECT_EQ( ittl == ittr , 1 );
            swap( ittl , ittr );
            swap( itsl , itsr );
        }
        
        EXPECT_EQ( ittr - ittl , std::distance( itsl , itsr ) );
    }

}

TEST( size_balanced_tree , functions ) {
    Project::map<int,int> T , F;
    std::map<int,int> S , G;

    fill_in( T , S );

    for( int t = 1 ; t <= 1000 ; ++ t ) {
        int v = rng() % 1000;
        EXPECT_EQ( *S.lower_bound( v ) , *T.lower_bound( v ) );
        auto its = S.find( v );
        auto itt = T.find( v );
        if( itt != T.end( ) )
            EXPECT_EQ( *its , *itt );
        insert_random( T , S , rng( ) % 3 );
        // std::cout << t << std::endl;
    }

}

TEST( size_balanced_tree , time ) {
    Project::map<int,int> T;
    std::map<int,int> S;
    for( int i = 1 ; i <= 1000000 ; ++ i ) 
        S[rng()] = i;
    
}

}
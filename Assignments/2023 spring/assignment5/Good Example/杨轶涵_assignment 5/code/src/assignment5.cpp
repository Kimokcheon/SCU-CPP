#include "../include/assignment5.hpp"
#include <iostream>
#include <map>
#include "../include/publication.hpp"
#include "../include/author.hpp"
#include "../include/book.hpp"
#include "algorithm"
#include <iomanip>
#include <cstring>
#include <fstream>

std::map<std::string,std::shared_ptr<Publisher>> all_publishers; 
// std::map<std::string,std::shared_ptr<Author>> all_authors;
std::map<std::string,std::shared_ptr<Author>> all_authors;

Dataframe read_csv(std::string filename) {
    std::ifstream input( filename );

    std::string title , author , genre , price , publisher;
    std::getline( input , title );
    Dataframe ret;

    auto deal_with_mark = [&] ( std::string& S ) {
        while( S[0] == '"' && S.back() != '"' ) {
            static std::string temp; temp.clear();
            std::getline( input , temp , ',' );
            S = S + "," + temp;
        }
        if( S[0] == '"' ) {
            S.erase( S.begin() );
            S.erase( -- S.end() );
        }
    };

    while( std::getline( input , title , ',' ) ) {
        deal_with_mark( title );
        std::getline( input , author , ',' );
        deal_with_mark( author );
        std::getline( input , genre , ',' );
        deal_with_mark( genre );
        std::getline( input , price , ',' );
        deal_with_mark( price );
        std::getline( input , publisher );
        deal_with_mark( publisher );
        ret.push_back( { title , author , genre , price , publisher } );
        // std::cerr << author << std::endl;
        
    }
    return ret;
}

std::vector<Book> defineBooks(Dataframe* Table) {
    std::vector<Book> books;
    for( const auto& t : ( *Table ) ) {
        std::string title = t[0];
        std::string author = t[1];
        std::string genre = t[2];
        std::string price = t[3];
        price.erase( price.begin() );
        while( !isdigit( price.back() ) ) price.pop_back();
        double Price = std::stod( price );

        std::string publisher = t[4];

        std::shared_ptr<Publisher> pub( nullptr );
        if( all_publishers.count( publisher ) ) pub = all_publishers[publisher];
        else pub = std::make_shared<Publisher>( publisher ) , all_publishers[publisher] = pub;

        if( !all_authors.count( author ) ) all_authors[author] = std::make_shared<Author>( author );
        std::shared_ptr<Author> auth ( all_authors[author] );

        books.emplace_back( title , genre , Price , auth , pub );
    }
    return books;
}



void sortBooksByPrice(std::vector<Book> & list_of_books ) {
    std::sort( list_of_books.begin() , list_of_books.end() );
}

void showTable(Dataframe* table,int start, int stop) {
    std::cout << std::setiosflags( std::ios::left );
    std::cout << std::setw( 60 ) << "Title";
    std::cout << std::setw( 30 ) << "Author(s)";
    std::cout << std::setw( 20 ) << "Genre";
    std::cout << std::setw( 10 ) << "Price";
    std::cout << std::setw( 20 ) << "Publisher";
    std::cout << std::endl;
    std::cout << std::setprecision( 2 );
    
    for( const auto& t : ( *table ) ) {
        std::cout << std::setw( 60 ) << t[0];
        std::cout << std::setw( 30 ) << t[1];
        std::cout << std::setw( 20 ) << t[2];
        std::cout << std::setw( 10 ) << t[3];
        std::cout << std::setw( 20 ) << t[4];
        std::cout << std::endl;
    }
}
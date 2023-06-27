#include "../include/book.hpp"
#include "../include/author.hpp"
#include "../include/publication.hpp"
#include <iostream>
#include <iomanip>

Book::Book( std::string _title , std::string _genre , double _price , std::shared_ptr<Author> author , std::shared_ptr<Publisher> publisher ) :
    title(_title) , genre(_genre) , price(_price) , author( author ) , publisher( publisher ) {}


bool operator < ( const Book& a , const Book& b ) {
    return a.price < b.price;
}

std::string Book::getAuthorName( ) {
    return author -> name;
}

std::string Book::getPublisherName( ) {
    return publisher -> name;
}

void Book::output() {
    std::cout << std::setw( 60 ) << title;
    std::cout << std::setw( 30 ) << author -> name;
    std::cout << std::setw( 20 ) << genre;
    std::cout << std::setw( 10 ) << '$' << price;
    std::cout << std::setw( 20 ) << publisher -> name;
    std::cout << std::endl;
}
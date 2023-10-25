// #include "../include/book.h"
// #include "author.h"
// #include "Publication.h"
#include "../include/assignment5.h"

Book::Book( std::string _title,
            std::string _genre,
            double _price,
            Author author,
            std::shared_ptr<Publisher> publisher):
            title(_title),
            genre(_genre),
            price(_price),
            author(author),
            publisher(publisher){};

std::string Book::getAuthorName(){
    return author.getname();
}
std::string Book::getPublisherName(){
    return (*publisher).getname();
}

bool operator < (const Book &x,const Book & y){
    return x.price<y.price;
}
#include<bits/stdc++.h>
// #include"assignment5.h"
#include "book.h"
Book::Book(std::string _title,
            std::string _genre,
            double _price,
            Author* _author,
            std::shared_ptr<Publisher> _publisher):title(_title),genre(_genre),price(_price),author(_author),publisher(_publisher){}
bool Book::operator ==(Book& y){
    return title==y.title&&genre==y.genre&&price==y.price&&getAuthorName()==y.getAuthorName()&&getPublisherName()==y.getPublisherName();
}
bool Book::operator<(Book& y){
    return price<y.price;
}
std::string Book::getAuthorName(){ return author->getAuthorName(); }
std::string Book::getPublisherName(){ return publisher->getPublisherName(); }
void sortBooksByPrice(std::vector<Book>& list_of_books ){
    std::sort(list_of_books.begin(),list_of_books.end());
}

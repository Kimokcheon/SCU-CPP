#include<bits/stdc++.h>
// #include"assignment5.h"
#include "author.h"
Author:: Author(std::string _name):name(_name){}
void Author::add_one_book(Book* x){ list_of_books.push_back(x); }
bool Author::operator ==(const Author& y){ return name==y.name; }
void Author::setListOfBooks(std::vector<Book*> all_books){ list_of_books=all_books; }
std::string Author::getAuthorName(){ return name; }
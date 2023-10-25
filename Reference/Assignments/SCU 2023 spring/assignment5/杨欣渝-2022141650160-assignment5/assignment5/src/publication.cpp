#include<bits/stdc++.h>
// #include"assignment5.h"
#include "publication.h"
Publisher:: Publisher(std::string _name):name(_name){}
void Publisher::add_one_book(Book* x){ list_of_books.push_back(x); }
void Publisher:: setListOfBooks(std::vector<Book*> all_books){ list_of_books=all_books; }
bool Publisher::operator ==(const Publisher& y){ return name==y.name; }
std::string Publisher::getPublisherName(){ return name; }
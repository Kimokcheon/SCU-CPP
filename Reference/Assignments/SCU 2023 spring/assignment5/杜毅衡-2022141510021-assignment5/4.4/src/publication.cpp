// #include "../include/publication.h"
#include "../include/assignment5.h"

Publisher::Publisher(std::string _name):name(_name){}
void Publisher::setListOfBooks(std::vector<Book> all_books){
    list_of_books=all_books;
    return ;
}
std::string Publisher::getname(){
    return name;
}
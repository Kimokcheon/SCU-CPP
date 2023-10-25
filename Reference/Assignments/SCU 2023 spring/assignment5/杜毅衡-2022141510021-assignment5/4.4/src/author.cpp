// #include "../include/author.h"
// #include "../include/book.h"
#include "../include/assignment5.h"

Author::Author(std::string _name): name(_name) {}
void Author::setListOfBooks(std::vector<Book> all_books){
    list_of_books=all_books;
    return ;
}
std::string Author::getname(){
    return name;
}
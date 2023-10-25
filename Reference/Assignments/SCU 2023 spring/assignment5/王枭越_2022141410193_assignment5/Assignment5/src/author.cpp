#include "../include/author.h"
#include "../include/publication.h"
#include "../include/book.h"

Author::Author(std::string _name):name(_name){}
void Author::setListOfBooks(std::vector<Book*> all_books){
    for(auto it:all_books){
        list_of_books.push_back(it);
    }
}
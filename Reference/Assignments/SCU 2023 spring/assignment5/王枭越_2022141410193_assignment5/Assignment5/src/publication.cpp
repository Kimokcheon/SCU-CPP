#include "../include/author.h"
#include "../include/publication.h"
#include "../include/book.h"

Publisher::Publisher(std::string _name):name(_name){};
void Publisher::setListOfBooks(std::vector<Book*> all_books){
    for(auto it:all_books){
        list_of_books.push_back(it);
    }
}
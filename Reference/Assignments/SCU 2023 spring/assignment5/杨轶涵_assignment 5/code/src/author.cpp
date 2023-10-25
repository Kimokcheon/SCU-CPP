#include "../include/author.hpp"
#include <memory>

Author::Author( std::string _name ) : name(_name) {}

void Author::setListOfBooks( std::vector<std::shared_ptr<Book>> all_books ) {
    list_of_books = all_books;
}
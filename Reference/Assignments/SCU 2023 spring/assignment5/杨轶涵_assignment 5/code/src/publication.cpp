#include "../include/publication.hpp"

Publisher::Publisher( std::string _name ) : name(_name) {}

void Publisher::setListOfBooks( std::vector<std::shared_ptr<Book>> all_books ) {
    list_of_books = all_books;
}
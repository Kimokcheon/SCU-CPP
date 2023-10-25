#include "../include/author.h"

Author::Author(const std::string& _name) {
    this->name = _name;
}

void Author::setListOfBooks(const std::vector<Book*>& all_books) {
    this->list_of_books = all_books;
}

std::string Author::getName() const {
    return this->name;
}

void Author::setName(const std::string& _name) {
    this->name = _name;
}



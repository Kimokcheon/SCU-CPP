#include "../include/publication.h"
#include "../include/author.h"
#include "../include/book.h"

Publisher::Publisher(std::string _name) {
    this->name = std::move(_name);
}

void Publisher::setListOfBooks(const std::vector<Book*>& all_books) {
    for (auto& book : all_books) {
        if (book->getPublisherName() == this->name) {
            this->list_of_books.push_back(book);
        }
    }
}

std::string Publisher::getName() const {
    return this->name;
}

void Publisher::setName(const std::string& _name) {
    this->name = _name;
}
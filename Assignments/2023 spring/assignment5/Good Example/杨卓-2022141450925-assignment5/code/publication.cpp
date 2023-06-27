#include "publication.h"
#include <vector>
#include <string>

Publisher::Publisher(std::string _name) {
    name = _name;
}

void Publisher::setListOfBooks(std::vector<Book*> all_books) {
    for (auto book : all_books) {
        if (book->getPublisherName() == this->name)
            list_of_books.push_back(book);
    }
}

std::string Publisher::getPublisherName() {
    return this->name;
}

#include "author.h"
#include <string>
#include <vector>

Author::Author(std::string _name) {
    name = _name;
}

void Author::setListOfBooks(std::vector<Book*> all_books) {
    for (auto book : all_books) {
        if (book->getAuthorName() == this->name)
            list_of_book.push_back(book);
    }
}

std::string Author::getAuthorName() {
    return this->name;
}

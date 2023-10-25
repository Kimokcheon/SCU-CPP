#include "book.h"
#include <string>
#include <memory>
#include "publication.h"
#include "author.h"

Book::Book(std::string _title,
        std::string _genre,
        double _price,
        Author* author,
        std::shared_ptr<Publisher> publisher) {
    title = _title;
    genre = _genre;
    price = _price;
    this->author = author;
    this->publisher = publisher;
}

double Book::getPrice() {
    return this->price;
}

std::string Book::getAuthorName() {
    return this->author->getAuthorName();
}

std::string Book::getPublisherName() {
    return this->publisher->getPublisherName();
}

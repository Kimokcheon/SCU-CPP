#include <utility>

#include "../include/book.h"

Book::Book(std::string _title,
           std::string _genre,
           double _price,
           Author author,
           std::shared_ptr<Publisher> publisher) :
        title(std::move(_title)),
        genre(std::move(_genre)),
        price(_price),
        author(author),
        publisher(std::move(publisher)){}

std::string Book::getAuthorName() {
    return this->author.getName();
}

std::string Book::getPublisherName() {
    return this->publisher->getName();
}

std::string Book::getTitle() {
    return this->title;
}

std::string Book::getGenre() {
    return this->genre;
}

double Book::getPrice() const {
    return this->price;
}

void Book::setAuthor(Author author1) {
    this->author = author1;
}

void Book::setPublisher(std::shared_ptr<Publisher> publisher1) {
    this->publisher = std::move(publisher1);
}

void Book::setTitle(std::string _title) {
    this->title = std::move(_title);
}

void Book::setGenre(std::string _genre) {
    this->genre = std::move(_genre);
}

void Book::setPrice(double _price) {
    this->price = _price;
}


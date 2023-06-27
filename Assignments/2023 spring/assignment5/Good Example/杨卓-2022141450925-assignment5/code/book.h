#ifndef BOOK
#define BOOK

#include <string>
#include <memory>
#include "publication.h"
#include "author.h"

class Publisher;

class Author;

class Book {
    public:
    Book(std::string _title,
        std::string _genre,
        double _price,
        Author* author,
        std::shared_ptr<Publisher> publisher);
    double getPrice();
    std::string getAuthorName();
    std::string getPublisherName();
    private:
    std::string title;
    std::string genre;
    double price;

    Author* author;
    std::shared_ptr<Publisher> publisher;
};


#endif
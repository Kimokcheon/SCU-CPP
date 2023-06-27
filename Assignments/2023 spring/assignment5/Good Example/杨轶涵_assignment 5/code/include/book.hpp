#pragma once

#include <vector>
#include <string>
#include <memory>

class Author;
class Publisher;

class Book{
    public:
        Book(std::string _title,
             std::string _genre,
             double _price,
             std::shared_ptr<Author> author,
             std::shared_ptr<Publisher> publisher);
        friend bool operator < ( const Book& a , const Book& b );
        std::string getAuthorName( );
        std::string getPublisherName();
        void output();
    private:
        std::string title;
        std::string genre;
        double price;

        std::shared_ptr<Author> author;
        std::shared_ptr<Publisher> publisher;
};
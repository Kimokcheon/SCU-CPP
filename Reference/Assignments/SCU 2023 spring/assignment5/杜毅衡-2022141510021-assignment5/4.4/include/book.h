#pragma once
#include <algorithm>
#include <string>
#include <memory>
#include <iostream>

class Publisher;
class Author;

class Book{
public:
    Book() = default;
    Book(std::string _title,
        std::string _genre,
        double _price,
        Author author,
        std::shared_ptr<Publisher> publisher);
    friend class Publisher;
    friend class author;
    friend bool operator < (const Book &x,const Book & y);
    std::string getAuthorName();
    std::string getPublisherName();
private:
    std::string title;
    std::string genre;
    double price;
    Author author;
    std::shared_ptr<Publisher> publisher;

};
#ifndef BOOK_H
#define BOOK_H

#include <bits/stdc++.h>
#include "../include/author.h"
#include "../include/publication.h"


class Book{
public:
    Book(){
        publisher = std::make_shared<Publisher>();
    }
    Book(std::string _title,
         std::string _genre,
         double _price,
         Author author,
         std::shared_ptr<Publisher> publisher);

    std::string getAuthorName();
    std::string getPublisherName();
    std::string getTitle();
    std::string getGenre();
    double getPrice() const;

    void setAuthor(Author author1);
    void setPublisher(std::shared_ptr<Publisher> publisher);
    void setTitle(std::string _title);
    void setGenre(std::string _genre);
    void setPrice(double _price);


private:
    std::string title;
    std::string genre;
    double price{};

    Author author;
    std::shared_ptr<Publisher> publisher;
};

#endif //BOOK_H
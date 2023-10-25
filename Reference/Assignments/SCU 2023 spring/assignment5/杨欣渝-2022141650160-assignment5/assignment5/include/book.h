#ifndef BOOK_H
#define BOOK_H

#include<bits/stdc++.h>
#include "author.h"
#include "publication.h"
typedef std::vector<std::vector<std::string>> Dataframe;
class Book{
    public:
        Book();
        Book(std::string _title,
             std::string _genre,
             double _price,
             Author* _author,
             std::shared_ptr<Publisher> _publisher);//书的初始化
        std::string getAuthorName();
        std::string getPublisherName();
        bool operator ==(Book& y);
        bool operator<(Book& y);//排序sort的重载<
        
    private:
        friend Book add_book(Book* x);
        friend void sortBooksByPrice(std::vector<Book> & list_of_books );

        std::string title;
        std::string genre;
        double price;
        
        Author* author;
        std::shared_ptr<Publisher> publisher;
};

#endif
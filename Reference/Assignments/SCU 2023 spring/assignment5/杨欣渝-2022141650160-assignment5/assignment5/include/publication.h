#ifndef PUBLICATION_H
#define PUBLICATION_H

#include<bits/stdc++.h>
class Book;
class Publisher{
    public:
        Publisher(std::string _name);
        void setListOfBooks(std::vector<Book*> all_books);
        bool operator ==(const Publisher& y);
        void add_one_book(Book* x);
        std::string getPublisherName();
        
    private:
        friend std::shared_ptr<Publisher> get_pub(std::string _name);//判断出版社是否出现过的函数，需要访问private

        std::string name;
        std::vector<Book*> list_of_books;
        
};

#endif
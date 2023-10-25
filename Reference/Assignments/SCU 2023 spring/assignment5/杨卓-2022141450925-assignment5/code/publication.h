#ifndef PUBLICATION
#define PUBLICATION

#include <string>
#include <vector>
#include "book.h"

class Book;

class Publisher{
    public:
    Publisher(std::string _name);
    void setListOfBooks(std::vector<Book*> all_books);
    std::string getPublisherName();
    private:
    std::string name;
    std::vector<Book*> list_of_books;
        
};


#endif
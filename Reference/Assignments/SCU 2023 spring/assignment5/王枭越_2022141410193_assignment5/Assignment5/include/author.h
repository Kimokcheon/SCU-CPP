#pragma once

#include <vector>
#include <string>

// #include "book.h"
class Book;

class Author{
    public:
        Author(std::string _name);
        void setListOfBooks(std::vector<Book*> all_books);
        std::string getname(){
            return name;
        }
    private:
        std::string name;
        std::vector<Book*> list_of_books;
};
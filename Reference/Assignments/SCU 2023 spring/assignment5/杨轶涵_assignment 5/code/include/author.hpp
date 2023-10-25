#pragma once

#include <vector>
#include <string>
#include <memory>

class Book;

class Author{
    public:
        Author(std::string _name);
        void setListOfBooks(std::vector<std::shared_ptr<Book>> all_books);
        friend class Book;
    private:
        std::string name;
        std::vector<std::shared_ptr<Book>> list_of_books;
};
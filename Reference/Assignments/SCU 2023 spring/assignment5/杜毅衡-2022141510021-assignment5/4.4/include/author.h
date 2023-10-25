#pragma once
#include<algorithm>
#include<string>

class Book;

class Author{
public:
    Author() = default;
    Author(std::string _name);
    void setListOfBooks(std::vector<Book> all_books);
    std::string getname();
    friend class Book;
private:
    std::string name;
    std::vector<Book> list_of_books;
};

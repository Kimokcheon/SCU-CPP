#ifndef AUTHOR_H
#define AUTHOR_H

#include <bits/stdc++.h>

class Book;

class Author{
public:
    explicit Author(const std::string& _name);
    Author() = default;
    void setListOfBooks(const std::vector<Book*>& all_books);
    std::string getName() const;
    void setName(const std::string& _name);
private:
    std::string name;
    std::vector<Book*> list_of_books{};
};

#endif //AUTHOR_H
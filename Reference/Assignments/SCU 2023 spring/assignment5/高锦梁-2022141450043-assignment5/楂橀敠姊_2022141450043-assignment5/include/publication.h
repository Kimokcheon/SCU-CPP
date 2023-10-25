#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <bits/stdc++.h>

class Book;

class Publisher{
public:
    Publisher() = default;
    explicit Publisher(std::string _name);
    void setListOfBooks(const std::vector<Book*>& all_books);
    std::string getName() const;
    void setName(const std::string& _name);

private:
    std::string name;
    std::vector<Book*> list_of_books;

};

#endif //PUBLICATION_H
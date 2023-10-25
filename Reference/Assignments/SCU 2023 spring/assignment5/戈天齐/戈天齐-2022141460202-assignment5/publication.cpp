#include "../include/publication.h"
Publisher::Publisher(std::string _name)
{
    name = _name;
}
void Publisher::setListOfBooks(std::vector<Book*> all_books)
{
    list_of_books = all_books;
}
std::string Publisher::getPublisherName() {
    return name;
}

#include "../include/author.h"

Author::Author(std::string _name)
{
    name = _name;
}
void Author::setListOfBooks(std::vector<Book*> all_books)
{
    list_f_Books = all_books;
}
std::string Author::getAuthorName() {
    return name;
}
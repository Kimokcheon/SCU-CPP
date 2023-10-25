#include "../include/book.h"
Book::Book(std::string _title,std::string _genre,std::string _price,Author & _author,std::string _publisher):author(_author)//这两个author有什么区别
{
    title = _title;
    genre = _genre;
    price = std::stod(&_price[1]);
    publisher = std::make_shared<Publisher>(_publisher);
}
std::string Book::getAuthorName() {
    return author.getAuthorName();
}
std::string Book::getPublisherName() {
    return publisher->getPublisherName();

}

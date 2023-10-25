#include "../include/author.h"
#include "../include/publication.h"
#include "../include/book.h"

Book::Book(std::string _title,
           std::string _genre,
           double _price,
           Author* author,
           std::shared_ptr<Publisher> publisher):title(_title),
                                                 genre(_genre),
                                                 price(_price),
                                                 author(author),
                                                 publisher(publisher)
                                                 {}

#pragma once

#include <vector>
#include <string>
#include <memory>

class Author;
class Publisher;

class Book{
    public:
        Book(std::string _title,
             std::string _genre,
             double _price,
             Author* author,
             std::shared_ptr<Publisher> publisher);
        
        std::string gettitle(){
            return title;
        }
        
        std::string getgenre(){
            return genre;
        }

        double getprice(){
            return price;
        }

        std::string getAuthorName(){
            return author->getname();
        }
        
        std::string getPublisherName(){
            return publisher->getname();
        }
        
    private:
        std::string title;
        std::string genre;
        double price;

        Author* author;
        std::shared_ptr<Publisher> publisher;
};
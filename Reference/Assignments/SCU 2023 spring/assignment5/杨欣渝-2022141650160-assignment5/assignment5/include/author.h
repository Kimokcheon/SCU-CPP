#ifndef AUTHOR_H
#define AUTHOR_H

#include<bits/stdc++.h>
class Book;
class Author{
    public:
        Author(std::string _name);//初始化
        void setListOfBooks(std::vector<Book*> all_books);//对作者的书单进行初始化
        bool operator ==(const Author& y);//这里重载==是用于判断是否出现过该作者
        void add_one_book(Book* x);//往这个作者的书单里加一本书
        std::string getAuthorName();//返回作者名字
        
    private:
        friend Author* get_author(std::string _name);//判断作者是否出现过的函数，需要访问private
        
        std::string name;//作者名字
        std::vector<Book*> list_of_books;//作者的书单
};

#endif
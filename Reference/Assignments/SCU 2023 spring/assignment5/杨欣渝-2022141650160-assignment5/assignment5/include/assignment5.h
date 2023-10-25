#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include<bits/stdc++.h>
#include"author.h"
#include"book.h"
#include"publication.h"
typedef std::vector<std::vector<std::string>> Dataframe;

Dataframe read_csv(std::string filename);//从.csv中读取
Book add_book(Book x);//加入总书单
Author* get_author(std::string _name);//判断作者是否已经出现过了，有就直接返回Author指针，没有则先创建再返回
std::shared_ptr<Publisher> get_pub(std::string _name);//判断出版社是否已经出现过了，有就直接返回指针，没有则先创建再返回
std::vector<Book> defineBooks(Dataframe* Table);
void sortBooksByPrice(std::vector<Book>* list_of_books );//用书记的价格排序，升序（注意排序的类对象的成员变量中不能有其他类的引用
void showTable(Dataframe* table,int start, int stop);
#endif
#pragma once
#include "author.h"
#include "book.h"
#include "publication.h"
#include <algorithm>
#include <string>



double getprice(std::string s);

void getauthor(std::string authorname);

void getpublisher(std::string publishername);

typedef std::vector<std::vector<std::string>> Dataframe;

Dataframe read_csv(std::string filename);

std::vector<Book> defineBooks(Dataframe* Table);

void sortBooksByPrice(std::vector<Book> & list_of_books );

void showTable(Dataframe* table,int start, int stop);

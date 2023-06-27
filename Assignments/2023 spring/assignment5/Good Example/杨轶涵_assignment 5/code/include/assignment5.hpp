#pragma once
#include <vector>
#include "book.hpp"

typedef std::vector<std::vector<std::string>> Dataframe;

Dataframe read_csv(std::string filename);

std::vector<Book> defineBooks(Dataframe* Table);   

void sortBooksByPrice(std::vector<Book> & list_of_books );

void showTable(Dataframe* table,int start, int stop);
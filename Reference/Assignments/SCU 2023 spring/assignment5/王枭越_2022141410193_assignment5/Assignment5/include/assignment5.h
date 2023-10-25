#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "author.h"
#include "publication.h"
#include "book.h"

typedef std::vector<std::vector<std::string>> Dataframe;
Dataframe read_csv(std::string filename);
std::vector<Book> defineBooks(Dataframe* Table);
void sortBooksByPrice(std::vector<Book> & list_of_books );
void showTable(Dataframe* table,int start, int stop);
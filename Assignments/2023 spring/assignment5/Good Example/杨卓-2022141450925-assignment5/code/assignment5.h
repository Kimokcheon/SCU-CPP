// assignment5.h
#ifndef ASSGIENMENT
#define ASSGIENMENT

#include "book.h"
#include "publication.h"
#include "author.h"

typedef std::vector<std::vector<std::string>> Dataframe;

Dataframe read_csv(std::string filename);

double getPrice(std::string pri);

std::vector<Book> defineBooks(Dataframe* Table);

void sortBooksByPrice(std::vector<Book> & list_of_books );

void showTable(Dataframe* table,int start, int stop);

#endif

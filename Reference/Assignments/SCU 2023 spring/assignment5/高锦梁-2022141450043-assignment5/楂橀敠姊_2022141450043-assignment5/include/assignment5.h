#ifndef ASSIGNMENT5_H
#define ASSIGNMENT5_H

#include <bits/stdc++.h>
#include "../include/publication.h"
#include "../include/author.h"
#include "../include/book.h"

typedef std::vector<std::vector<std::string>> Dataframe;

Dataframe read_csv(const std::string& filename);

void showDataframe(Dataframe* table,int start, int stop);

void showTable(Dataframe* table,int start, int stop);

std::vector<Book> defineBooks(Dataframe* Table);

#endif //ASSIGNMENT5_H
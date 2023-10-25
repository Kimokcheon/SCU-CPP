// assignment5.cpp
#include "assignment5.h"
#include "book.h"
#include "publication.h"
#include "author.h"
#include <memory>
#include <vector>
#include <regex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

Dataframe read_csv(std::string filename) {
    std::ifstream fin(filename);
	// title author genre price publisher
    Dataframe table;
    std::string line;
    std::getline(fin, line);
    while (std::getline(fin, line)) {
        std::string cell;
        int len = line.length();
        int pos = 0;
        std::vector<std::string> info;
        // using regular expression to get books
        std::regex match_mode("(\\\"([^\\\"]*)\\\")|([\\w][&\\w\\s]*[\\w])|([\\w])|(\\$[\\d]*\\.[\\d]*)|(,[\\s]*,)");
        auto begin = std::sregex_iterator(line.begin(), line.end(), match_mode);
        auto end = std::sregex_iterator();
        for (auto m = begin; m != end; ++m) {
            std::string str = (*m).str();
            if (str[0] == '\"') str = (*m)[2].str();
            if (str[0] == ',') str = "";
            info.push_back(str);
        }
        table.push_back(info);
    }
    return table;
}

double getPrice(std::string pri) {
    std::stringstream ss; // using stringstream to get double from string
    double result = 0;
    std::regex mode("[\\d]*\\.[\\d]*");
    std::smatch str;
    std::regex_search(pri, str, mode);
    ss = std::stringstream(str.str());
    ss >> result;
    return result;
}

std::vector<Book> defineBooks(Dataframe* Table) {
    std::vector<Book> books;
    for (auto book : *Table) { // initialize a book
        Book *single_book;
        Author *author;
        std::shared_ptr<Publisher> publisher;
        std::string title = book[0];
        std::string gener = book[2];
        double price = getPrice(book[3]);
        author = new Author(book[1]);
        publisher = std::make_shared<Publisher>(book[4]);
        single_book = new Book(title, gener, price, author, publisher);
        books.push_back(*single_book);
    }
    return books;
}

void sortBooksByPrice(std::vector<Book> &list_of_books) {
    auto cmpF = [](Book A, Book B) { // sort order
        return A.getPrice() > B.getPrice();
    };
    std::sort(list_of_books.begin(), list_of_books.end() ,cmpF);
}

void showTable(Dataframe* table, int start, int stop) {
    size_t maxlen_name = 0;
    size_t maxlen_author = 0;
    size_t maxlen_genre = 0;
    for (int i = start; i <= stop; ++i) {
        maxlen_name = std::max(maxlen_name, table->at(i)[0].length());
        maxlen_author = std::max(maxlen_author, table->at(i)[1].length());
        maxlen_genre = std::max(maxlen_genre, table->at(i)[2].length());
    }
    ++maxlen_name;
    ++maxlen_author;
    ++maxlen_genre; // set margin
    std::cout << std::left;
    std::cout << std::setw(maxlen_name) << "Title";
    std::cout << std::setw(maxlen_author) << "Author(s)";
    std::cout << std::setw(maxlen_genre) << "Genre"; 
    std::cout << std::setw(8) << "Price";
    std::cout << "Publisher" << std::endl; // print title
    for (int i = start; i <= stop; ++i) { // print infomation about book
        std::cout << std::setw(maxlen_name) << table->at(i)[0];
        std::cout << std::setw(maxlen_author) << table->at(i)[1];
        std::cout << std::setw(maxlen_genre) << table->at(i)[2];
        std::cout << std::setw(8) << table->at(i)[3];
        std::cout << table->at(i)[4] << std::endl;
    }
}

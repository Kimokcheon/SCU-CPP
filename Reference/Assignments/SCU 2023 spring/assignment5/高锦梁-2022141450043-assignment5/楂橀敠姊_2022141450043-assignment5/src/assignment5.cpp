#include "../include/assignment5.h"
#include "../include/book.h "
#include <bits/stdc++.h>

Dataframe read_csv(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "File not found" << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(file,line);
    std::vector<std::vector<std::string>> data;
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;
        while(std::getline(ss,cell,',')){
            row.push_back(cell);
        }
        data.push_back(row);
    }
    for(int i = 0; i < data.size(); i++){
        int k = 0;
        for(int j = 0; j < data[i].size(); j++){
            if(data[i][j][0] == '"'){
                data[i][j].erase(0,1);
                k = j;
            }
            if(data[i][j][data[i][j].size()-1] == '"'){
                data[i][j].erase(data[i][j].size()-1,1);
                if(k != j){
                    data[i][k] += "," + data[i][j];
                    data[i].erase(data[i].begin()+j);
                    j--;
                }
            }
        }
    }
    return data;
}

void showDataframe(Dataframe* table,int start, int stop){
    for(int i = start; i < stop; i++){
        for(const auto & j : table->at(i)){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void showTable(Dataframe* table,int start, int stop){
    for(int i = start; i < stop; i++){
        std::cout << std::left << std::setw(50) << table->at(i)[0]
                << std::left << std::setw(25) << table->at(i)[1]
                << std::left << std::setw(20) << table->at(i)[2]
                << std::left << std::setw(10) << table->at(i)[3]
                << std::left << std::setw(20) << table->at(i)[4]
                << std::endl;
    }
}

std::vector<Book> defineBooks(Dataframe* Table){
    std::vector<Book> books;
    for(auto & i : *Table){
        Book book;
        book.setTitle(i[0]);
        Author author(i[1]);
        book.setAuthor(author);
        book.setGenre(i[2]);
        book.setPrice(std::stod(i[3].erase(0,1)));
        Publisher publisher(i[4]);
        book.setPublisher(std::make_shared<Publisher>(publisher));
        books.push_back(book);
    }
    return books;
}

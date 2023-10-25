#include "../include/assignment5.h"

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
    for(auto & i : data){
        int k = 0;
        for(int j = 0; j < i.size(); j++){
            if(i[j][0] == '"'){
                i[j].erase(0,1);
                k = j;
            }
            if(i[j][i[j].size()-1] == '"'){
                i[j].erase(i[j].size()-1,1);
                if(k != j){
                    i[k] += "," + i[j];
                    i.erase(i.begin()+j);
                    j--;
                }
            }
        }
    }
    return data;
}

std::vector<Author*> storage;

std::vector<Book> defineBooks(Dataframe* Table){
    std::vector<Book> books;
    for( const auto & i : *Table){
        storage.emplace_back(new Author(i[1]));
        books.emplace_back(i[0],i[2],i[3],*storage.back(),i[4]);
    }
    return books;
}

void showTable(Dataframe* table,int start, int stop){
    for(int i = start; i < stop; i++){
        for(const auto & j : (*table)[i]){
            std::cout << std::left << std::setw(50)<< j;
        }
        std::cout << std::endl;
    }
}
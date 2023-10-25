#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;
typedef std::vector<std::vector<std::string>> Dataframe;
Dataframe read_csv(std::string filename){
    Dataframe table;
    std::ifstream fin(filename);
    std::vector<std::string> data;
    std::string Title,Author,Genre,Price,Publisher;
    std::string line;
    getline(fin,line);
    while(getline(fin,line)){
        std::istringstream sin(line);
        getline(sin, Title, ',');
        getline(sin, Author, ',');
        getline(sin, Genre, ',');
        getline(sin, Price, ',');
        getline(sin, Publisher, ',');
        data.push_back(Title);
        data.push_back(Author);
        data.push_back(Genre);
        data.push_back(Price);
        data.push_back(Publisher);
        table.push_back(data);
    }
    fin.close();
    return table;
}
int main(){

    Dataframe table = read_csv("dataset.csv");

    cout<<table[0][0];

    return 0;
}
#include "../include/assignment5.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <map>

Dataframe table = read_csv("dataset.csv");

std::map<std::string,Author>authorlist;

std::map<std::string,Publisher>publisherlist;

std::string get(std::string line,int &s){
    std::string res;
    int len=line.size()-1,t=0;
    if(line[s]=='"'){
        for(int i=s+1;i<len;++i){
            t=i;
            if(line[i]=='"') break;
            res+=line[i];
        }
        s=t+2;
    }
    else{
        for(int i=s;i<len;++i){
            t=i;
            if(line[i]==',') break;
            res+=line[i];
        }
        s=t+1;
    }
    return res;
}

Dataframe read_csv(std::string filename){
    Dataframe table;
    std::ifstream fin(filename);
    std::vector<std::string> data;
    std::string Title,Author,Genre,Price,Publisher;
    std::string line;
    getline(fin,line);
    while(getline(fin,line)){
        int s=0;
        
        Title=get(line,s);
        Author=get(line,s);
        Genre=get(line,s);
        Price=get(line,s);
        Publisher=get(line,s);

        data.clear();
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

double getprice(std::string s){
    int len=s.size(),fl=0;
    double price=0,tmp=0;
    for(int i=0 ; i<len ; ++i){
        if(s[i]=='.') {
            fl=1;
            tmp=1;
        }
        if(!isdigit(s[i])) continue;
        if(fl) {
            tmp=tmp*0.1;
            price=price+(s[i]-'0')*tmp;
        }
        else {
            price=price*10+s[i]-'0';
        }
    }
    return price;
}

void getauthor(std::string authorname){
    Author u(authorname);
    if(authorlist.count(authorname)==0){
        authorlist[authorname]=u;
    }
    return ;
}

void getpublisher(std::string publishername){
    Publisher u(publishername);
    if(publisherlist.count(publishername)==0){
        publisherlist[publishername]=u;
    }
    return ;
}

std::vector<Book> defineBooks(Dataframe* Table){
    std::vector<Book> Books;
    std::vector<std::vector<Book>>list1;
    std::vector<std::vector<Book>>list2;
    std::map<std::string,int>mp1;
    std::map<std::string,int>mp2;
    std::vector<Book>t;
    int cnt1=0,cnt2=0;
    for(auto u: *Table ){
        
        // u[0] Title
        // u[1] Author
        // u[2] Genre
        // u[3] Price
        // u[4] Publisher

        getauthor(u[1]);
        getpublisher(u[4]);
        
        double price=getprice(u[3]);
        Author author=authorlist[u[1]];
        std::shared_ptr<Publisher> pt;
        pt=std::make_shared<Publisher>(publisherlist[u[4]]);

        Book cur(u[0],u[2],price,author,pt);

        if(!mp1[u[1]]) mp1[u[1]]=cnt1++,list1.push_back(t);
        if(!mp2[u[4]]) mp2[u[4]]=cnt2++,list2.push_back(t);
        
        list1[mp1[u[1]]].push_back(cur);
        list2[mp1[u[4]]].push_back(cur);

        Books.push_back(cur);
    }

    for(auto it=authorlist.begin();it!=authorlist.end();++it){
        (*it).second.setListOfBooks(list1[mp1[(*it).first]]);
    }

    for(auto it=publisherlist.begin();it!=publisherlist.end();++it){
        (*it).second.setListOfBooks(list2[mp2[(*it).first]]);
    }

    return Books;
}

void sortBooksByPrice(std::vector<Book> & list_of_books ){

    std::sort(list_of_books.begin(),list_of_books.end());
    return ;
}
std::ofstream fout("assignment5.out");
void opt(std::string word,int len){
    len=len-word.size();
    fout<<word;
    for(int i=1;i<=len;++i) fout<<' ';
    return ;
}
void showTable(Dataframe* table,int start, int stop){
    std::string Title,Author,Genre,Price,Publisher;
    Title="Title";
    Author="Author(s)";
    Genre="Genre";
    Price="Price";
    Publisher="Publisher";
    opt(Title,60);
    opt(Author,30);
    opt(Genre,20);
    opt(Price,10);
    opt(Publisher,0);
    fout<<'\n';
    for(int i=start;i<=stop;++i){
        auto u=(*table)[i];
        Title=u[0];
        Author=u[1];
        Genre=u[2];
        Price=u[3];
        Publisher=u[4];
        opt(Title,60);
        opt(Author,30);
        opt(Genre,20);
        opt(Price,10);
        opt(Publisher,0);
        fout<<'\n';
    }
    return ;
}

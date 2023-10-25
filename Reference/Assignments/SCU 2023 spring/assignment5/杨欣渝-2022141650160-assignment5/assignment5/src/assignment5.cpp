#include<bits/stdc++.h>
#include"assignment5.h"

std::vector<Book*> book_all;
std::vector<Author*> author_all;
std::vector<std::shared_ptr<Publisher>> pub_all;//all books, authors, publishers

Dataframe read_csv(std::string filename){
    std::ifstream in;
    filename="../"+filename;
    in.open(filename);
    std::string s,c;
    Dataframe res;
    getline(in,s,'\n'); //read the first line
    std::vector<std::string> B; //one book's info
    int tag=0; //tag=1 when in ""
    while(getline(in,s,'\n')){
        int l=s.size();
        for(int i=0;i<l;i++){
            if(s[i]=='\"'){ tag^=1; continue; }
            if(s[i]==','&&tag==0) B.push_back(c), c="";
            else c=c+s[i];
        }
        B.push_back(c), res.push_back(B); 
        B.clear(), tag=0, c="";

    }
    in.close();
    return res;
}

Book add_book(Book* x){
    for(auto y : book_all) if(*y==*x) return *y;
    book_all.push_back(x);
    x->publisher->add_one_book(x);
    x->author->add_one_book(x);
    return *x;
}

double get_price(std::string number){
    double val=0,dot=1; int tag=0;
    for(int j=0;j<number.size();j++){
        if(number[j]==' '||number[j]=='$') continue;
        if(number[j]=='.') tag=1;
        else val=val*10.0+number[j]-'0',dot=tag?dot*0.1:dot;
    }
    return val*dot;
}

Author* get_author(std::string _name){
    for(auto y : author_all) if(y->name==_name) return y; 
    Author *p=new Author(_name);
    author_all.push_back(p);
    return p;
}

std::shared_ptr<Publisher> get_pub(std::string _name){
    for(auto y : pub_all) if(y->name==_name) return y;
    std::shared_ptr<Publisher> p(new Publisher(_name));
    pub_all.push_back(p);
    return p;
}

std::vector<Book> defineBooks(Dataframe* Table){
    std::vector<Book> res; 
    int n=Table->size(); if(!n) return res;
    for(int i=0;i<n;i++){
        auto s=Table->at(i);
        res.push_back(add_book(new Book(s[0],s[2],get_price(s[3]),get_author(s[1]),get_pub(s[4]))));
        // title genre price author pub
    }
    return res;
}

void showTable(Dataframe* table,int start, int stop){
    size_t sw[5]={5,9,5,5,9};
    for(int i=start;i<=stop;i++){
        int cnt=0;
        for(auto j : table->at(i)) sw[cnt]=std::max(sw[cnt],j.size()), cnt++;
    }
    for(int i=0;i<5;i++) sw[i]+=5;
    std::cout<< std::setiosflags(std::ios::left)<<std::setw(sw[0])<<"Title";
    std::cout<< std::setiosflags(std::ios::left)<<std::setw(sw[1])<<"Author(s)";
    std::cout<< std::setiosflags(std::ios::left)<<std::setw(sw[2])<<"Genre";
    std::cout<< std::setiosflags(std::ios::left)<<std::setw(sw[3])<<"Price";
    std::cout<< std::setiosflags(std::ios::left)<<std::setw(sw[4])<<"Publisher";
    std::cout<<std::endl;
    for(int i=start;i<=stop;i++){
        auto s=table->at(i);
        for(int j=0;j<5;j++)
            std::cout<< std::setiosflags(std::ios::left)<<std::setw(sw[j])<<s[j];
        std::cout<<std::endl;
    }
}
//lackness: getAuthorName, getPublicasherName, showTable

/*
Title,Author,Genre,Price,Publisher
Fundamentals of Wavelets,"Goswami, Jaideva",signal_processing,$22.80 ,Wiley
Data Smart,"Foreman, John",data_science,$23.50 ,Wiley
*/
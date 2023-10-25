#include "../include/assignment5.h"

Dataframe read_csv(std::string filename){
    Dataframe ret;
    std::ifstream in(filename);
    std::string tmp,line;
    std::getline(in,tmp);
    while(std::getline(in,line)){
        //处理引号中逗号
        int pos=line.find('"');
        int pos_=line.find('"',pos+1);
        while(pos!=-1){
            int po=line.find(',',pos+1);
            while(po>pos&&po<pos_){
                line[po]='+';
                po=line.find(',',po+1);
            }
            pos=line.find('"',pos_+1);
            pos_=line.find('"',pos+1);
        }

        std::stringstream ss;
        ss<<line;
        std::string Title,Author,Genre,Price,Publisher;
        std::getline(ss,Title,',');
        if(Title[0]=='"')Title=Title.substr(1,Title.size()-2);
        std::getline(ss,Author,',');
        if(Author[0]=='"')Author=Author.substr(1,Author.size()-2);
        std::getline(ss,Genre,',');
        if(Genre[0]=='"')Genre=Genre.substr(1,Genre.size()-2);
        std::getline(ss,Price,',');
        if(Price[0]=='"')Price=Price.substr(1,Price.size()-2);
        std::getline(ss,Publisher);
        if(Publisher[0]=='"')Publisher=Publisher.substr(1,Publisher.size()-2);

        //还原引号中逗号
        int q=Title.find('+');
        while(q!=-1){
            Title[q]=',';
            q=Title.find('+',q+1);
        }

        q=Author.find('+');
        while(q!=-1){
            Author[q]=',';
            q=Author.find('+',q+1);
        }

        q=Genre.find('+');
        while(q!=-1){
            Genre[q]=',';
            q=Genre.find('+',q+1);
        }

        q=Price.find('+');
        while(q!=-1){
            Price[q]=',';
            q=Price.find('+',q+1);
        }

        q=Publisher.find('+');
        while(q!=-1){
            Publisher[q]=',';
            q=Publisher.find('+',q+1);
        }

        //存储
        std::vector<std::string> tt{Title,Author,Genre,Price,Publisher};
        ret.push_back(tt);
    }
    in.close();
    return ret;
}

std::vector<Book> defineBooks(Dataframe* Table){
    std::vector<Book> ret;
    for(auto line:*Table){
        std::string title,author,genre,price,publisher;
        title=line[0];
        author=line[1];
        genre=line[2];
        price=line[3];
        publisher=line[4];
        Author* p=new Author(author);
        std::shared_ptr<Publisher> q(new Publisher(publisher));
        Book* t=new Book(title,genre,std::stod(price.substr(1)),p,q);
        std::vector<Book*> tmp{t};
        p->setListOfBooks(tmp);
        q->setListOfBooks(tmp);
        ret.push_back(*t);
    }
    return ret;
}

bool cmp(Book a,Book b){
    return a.getprice()<b.getprice();
}

void sortBooksByPrice(std::vector<Book> & list_of_books ){
    std::sort(list_of_books.begin(),list_of_books.end(),cmp);
}

void showTable(Dataframe* table,int start, int stop){
    std::vector<Book> t=defineBooks(table);
    std::cout<<std::setw(50)<<std::left<<"Title";
    std::cout<<std::setw(30)<<std::left<<"Author(s)";
    std::cout<<std::setw(30)<<std::left<<"Genre";
    std::cout<<std::setw(30)<<std::left<<"Price";
    std::cout<<std::setw(30)<<std::left<<"Publisher"<<std::endl;
    for(int i=start;i<stop;++i){
        std::cout<<std::setw(50)<<std::left<<t[i].gettitle();
        std::cout<<std::setw(30)<<std::left<<t[i].getAuthorName();
        std::cout<<std::setw(30)<<std::left<<t[i].getgenre();
        std::string tt=std::to_string(t[i].getprice());
        std::cout<<std::setw(30)<<std::left<<"$"+tt.substr(0,tt.find('.')+3);
        std::cout<<std::setw(30)<<std::left<<t[i].getAuthorName()<<std::endl;
    }
}
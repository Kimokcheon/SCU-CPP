#include "../include/login.h"

User::User(std::string name, std::string pass, std::string mail){
    username=name;
    password=pass;
    email=mail;
}
User::~User(){

}

Login::Login(){
    
}

Login::~Login(){
    users.clear();
    LoginedUsers.clear();
}

void Login::registerUser(std::string username, std::string password, std::string email){
    if(!checkUsername(username)&&!checkEmail(email)){
        User *p=new User(username,password,email);
        users.push_back(p);
    }
}

bool Login::checkUsername(std::string &new_username){
    for(int i=0;i<users.size();i++){
        if(new_username==users[i]->username){
            std::cout<<"username already taken"<<std::endl;
            return true;
        }
    }
    return false;
}

bool Login::checkEmail(std::string &new_email){
    for(int i=0;i<users.size();i++){
        if(new_email==users[i]->email){
            return true;
        }
    }
    return false;
}

void Login::loginUser(std::string username, std::string password){
    // for(int i=0;i<users.size();i++){
    //     if(users[i]->username==username&&users[i]->password==password){
    //         LoginedUsers.push_back(users[i]);
    //         break;
    //     }
    // }
    User *p=getUser(username);
    if(p!=nullptr){
        if(p->password==password){
            LoginedUsers.push_back(p);
        }
    }
}

User* Login::getUser(std::string username){
    for(int i=0;i<users.size();i++){
        if(users[i]->username==username){
            return users[i];
        }
    }
    return nullptr;
}

void Login::removeUser(std::string username){
    User *p=getUser(username);
    if(p!=nullptr){
        users.erase(find(users.begin(),users.end(),p));
        if(find(LoginedUsers.begin(),LoginedUsers.end(),p)!=LoginedUsers.end())
        LoginedUsers.erase(find(LoginedUsers.begin(),LoginedUsers.end(),p));
        delete p;
        p=nullptr;
    }
}

void Login::changeUsername(std::string username, std::string newUsername){
    User *p=getUser(username);
    p->username=newUsername;
}

void Login::changePassword(std::string username, std::string newPassword){
    User *p=getUser(username);
    p->password=newPassword;
}

void Login::changeMail(std::string username, std::string newMail){
    User *p=getUser(username);
    p->email=newMail;
}

void Login::readFile(std::string path){
    std::ifstream in(path);
    std::string tmp,username,password,email,islogin;
    std::getline(in,tmp);
    while(in>>username>>password>>email>>islogin){
        registerUser(username,password,email);
        if(islogin=="yes"){
            loginUser(username,password);
        }
    }
}
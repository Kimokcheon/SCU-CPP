#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#ifndef _login_h
#define _login_h
#include "../include/login.h"
#endif
using namespace std;

User::User(std::string name, std::string pass, std::string mail):
    username(name),password(pass),email(mail){}

Login::Login(){
    users.clear();
    LoginedUsers.clear();
}

Login::~Login(){
    users.clear();
    LoginedUsers.clear();
}


void Login::readFile(std::string path){
    freopen(path.c_str(),"r",stdin);
    string username,password,email,login=0;
    cin>>username>>password>>email>>login;
    while(cin>>username){
        cin>>password>>email>>login;
        registerUser(username,password,email);
        if(login=="yes") loginUser(username,password);
    }
    return ;
}

bool Login::checkUsername(std::string &new_username){
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==new_username) return 1;
    return 0;
}

bool Login::checkEmail(std::string &new_email){
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->email==new_email) return 1;
    return 0;    
}
 
void Login::changeUsername(std::string username, std::string newUsername){
    if(checkUsername(newUsername)) return ;
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==username){
            (*it)->username=newUsername;
            break;
        } 
    for(auto it=LoginedUsers.begin();it!=LoginedUsers.end();++it)
        if((*it)->username==username){
            (*it)->username=newUsername;
            break;
        } 
    return ;
}

void Login::changePassword(std::string username, std::string newPassword){
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==username){
            (*it)->password=newPassword;
            break;
        } 
    for(auto it=LoginedUsers.begin();it!=LoginedUsers.end();++it)
        if((*it)->username==username){
            (*it)->password=newPassword;
            break;
        } 
    return ;
}

void Login::changeMail(std::string username, std::string newMail){
    if(checkEmail(newMail)) return ;
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==username){
            (*it)->email=newMail;
            break;
        } 
    for(auto it=LoginedUsers.begin();it!=LoginedUsers.end();++it)
        if((*it)->username==username){
            (*it)->email=newMail;
            break;
        } 
    return ;
}
    
void Login::registerUser(std::string username, std::string password, std::string email){
    if( checkUsername (username) )  return ;
    if( checkEmail (email) ) return ;

    User *p=new User(username,password,email);
   
   users.push_back(p);

   return ;
} // function to creat a user

void Login::loginUser(std::string username, std::string password){
    for(auto it=LoginedUsers.begin();it!=LoginedUsers.end();++it)
        if((*it)->username==username){
            return ;
        }   
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==username && (*it)->password==password ){
            LoginedUsers.push_back(*it);
            return ;
        }
    return ;
}

void Login::removeUser(std::string username){
    for(auto it=LoginedUsers.begin();it!=LoginedUsers.end();++it)
        if((*it)->username==username){
            LoginedUsers.erase(it);
            break;
        }
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==username){
            users.erase(it);
            break;
        }
    return ;
}

User* Login::getUser (std::string username){
    for(auto it=users.begin();it!=users.end();++it)
        if((*it)->username==username){
            return *it;
        }
    return nullptr;
} // returns the usernames using the same email, returns false if that email doesnt exist


#include "../include/login.h"

#include<vector>
#include<fstream>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;

User::User(std::string name, std::string pass, std::string mail){username=name,password=pass,email=mail;}
User::~User(){username.clear(),password.clear(),email.clear();}
Login::Login()
{
    users.clear();
    LoginedUsers.clear();
}
Login::~Login()
{
    users.clear();
    LoginedUsers.clear();
}

void Login::readFile(string path)
{
    ifstream fin(path);
    string a,b,c;
    fin>>a>>b>>c;
    for(int i=1;i<=8;i++) fin>>a>>b>>c;
}

bool Login::checkUsername(std::string &new_username)
{
    for(auto x:users) if(x->username==new_username) return 1;
    return 0;
}

bool Login::checkEmail(std::string &new_email)
{
    for(auto x:users) if(x->email==new_email) return 1;
    return 0;
}

void Login::changeUsername(std::string username, std::string newUsername)
{
    if(checkUsername(newUsername)) return ;
    for(auto x:users) if(x->username==username) x->username=newUsername;
    return ;
}

void Login::changePassword(std::string username, std::string newPassword)
{
    for(auto x:users) if(x->username==username) x->password=newPassword;
    return ;
}

void Login::changeMail(std::string username, std::string newMail)
{
    if(checkEmail(newMail)) return ;
    for(auto x:users) if(x->username==username) x->email=newMail;
    return ;
}

void Login::registerUser(std::string username, std::string password, std::string email)
{
    if(checkUsername(username)) return ;
    if(checkEmail(email)) return ;
    User x(username,password,email);
    users.push_back(&x);
}

void Login::loginUser(std::string username, std::string password)
{
    for(auto x:users) if(x->username==username) LoginedUsers.push_back(x);
    return ;
}

void Login::removeUser(std::string username)
{
    for(auto x:users) if(x->username==username) delete x;
    return ;
}

User* Login::getUser (std::string username)
{
    for(auto x:users) if(x->username==username) return x;
    return nullptr;
}
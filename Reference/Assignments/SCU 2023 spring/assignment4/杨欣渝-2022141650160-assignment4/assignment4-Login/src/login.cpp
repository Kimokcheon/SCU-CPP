#include "../include/login.h"
#include <bits/stdc++.h>
using namespace std;
User:: User(string name, string pass, string mail):username(name),email(mail),password(pass){}
User:: ~User(){}
Login::Login(){}
Login::~Login(){}
void Login::readFile(string path){
    ifstream infile; 
    infile.open(path);
    string s[4];
    infile>>s[0]>>s[1]>>s[2]>>s[3];
    while(1){
        infile>>s[0]>>s[1]>>s[2]>>s[3];
        if(s[2]=="") break;
        registerUser(s[0],s[1],s[2]);
        if(s[3]=="yes") loginUser(s[0],s[1]);
    }
    infile.close();
} 
// reads the .txt file, then register the user inside readFile using the registerUser function

bool Login::checkUsername(string &new_username){
    for(User* i: users) if(i->username==new_username){ printf("username already taken"); return 1; }
    return 0;
} //checks if the user is already taken, if so, it returns true and the username shouldn't be created
//and prints "username already taken"

bool Login::checkEmail(string &new_email){
    for(User* i: users) if(i->email==new_email) return 1;
    return 0;
} // only new emails may be pushedback to "emails" vector

void Login::changeUsername(string username, string newUsername){
    for(User* i: users) if(i->username==username) i->username=newUsername;
}

void Login::changePassword(string username, string newPassword){
    for(User* i: users) if(i->username==username) i->password=newPassword;
}

void Login::changeMail(string username, string newMail){
    for(User* i: users) if(i->username==username) i->email=newMail;
}

void Login::registerUser(string username, string password, string email){
    if(checkUsername(username)||checkEmail(email)) return;
    users.push_back(new User(username,password,email));
} // function to creat a user

void Login::loginUser(string username, string password){ 
    for(User* i: users) if(i->username==username&&i->password==password) LoginedUsers.push_back(i);
}

void Login::removeUser(std::string username){ 
    stack<User*> st;
    while(users.size()&&users[users.size()-1]->username!=username) 
        st.push(users[users.size()-1]), users.pop_back();
    if(users.size()) users.pop_back();
    while(!st.empty()) users.push_back(st.top()), st.pop();

    while(LoginedUsers.size()&&LoginedUsers[LoginedUsers.size()-1]->username!=username) 
        st.push(LoginedUsers[LoginedUsers.size()-1]), LoginedUsers.pop_back();
    if(LoginedUsers.size()) LoginedUsers.pop_back();
    while(!st.empty()) LoginedUsers.push_back(st.top()), st.pop();
}

User* Login::getUser (std::string username){ for(User* i: users) if(i->username==username) return i; return nullptr; }
// returns the usernames using the same email, returns false if that email doesnt exist

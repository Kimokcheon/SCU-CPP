#include "login.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

User::User(std::string username, std::string password, std::string email)
{
    this->username = username;
    this->password = password;
    this->email = email;
}

User::~User() = default;


Login::Login()
{
    this->users = std::vector<User*>();
    this->LoginedUsers = std::vector<User*>();
}

Login::~Login() = default;

// reads the .txt file, then register the user inside readFile using theregisterUser function
void Login::readFile(const std::string path){
    std::ifstream file(path);
    std::map<std::string, bool> users;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            users[line] = false;
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
        return;
    }
    // 输出所有用户及其登录状态
    for (auto const& user : users) {
        std::cout << user.first << " " << user.second << std::endl;
    }
}
//这样需要手动释放吗
void Login::registerUser(std::string username, std::string password, std::string email) {
    if (checkUsername(username) && checkEmail(email)) {
        User* user = new User(username, password, email);
        this->users.push_back(user);
    }
}

void Login::loginUser(std::string username, std::string password) {
    User* user = getUser(username);
    if (user != nullptr && user->password == password) {
        this->LoginedUsers.push_back(user);
    }
}

User* Login::getUser(std::string username) {
    for (auto user : this->users) {
        if (user->username == username) {
            return user;
        }
    }
    return nullptr;
}



void Login::changeUsername(std::string username, std::string newUsername) {
    User* user = getUser(username);
    if (user != nullptr && checkUsername(newUsername)) {
        user->username = newUsername;
    }
}

void Login::changePassword(std::string username, std::string newPassword) {
    User* user = getUser(username);
    if (user != nullptr) {
        user->password = newPassword;
    }
}

void Login::changeMail(std::string username, std::string newMail){
    User* user = getUser(username);
    if (user != nullptr && checkEmail(newMail)) {
        user->email = newMail;
    }
}


bool Login::checkEmail(std::string &new_email)
{
    for (auto user : this->users) {
        if (user->email == new_email) {
            return false;
        }
    }
    return true;
}

bool Login::checkUsername(std::string &new_username)
{
    for (auto user : this->users) {
        if (user->username == new_username) {
            return false;
        }
    }
    return true;
}

void Login::removeUser(std::string username) {
    User* user = getUser(username);
    if (user != nullptr) {
        this->users.erase(std::remove(this->users.begin(), this->users.end(), user), this->users.end());
        delete user;
        for(auto it = this->LoginedUsers.begin(); it != this->LoginedUsers.end(); it++) {
            if (*it == user) {
                this->LoginedUsers.erase(it);
                break;
            }
        }
    }


}







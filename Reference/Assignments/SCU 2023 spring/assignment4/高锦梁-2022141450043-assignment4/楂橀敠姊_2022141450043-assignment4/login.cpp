#include "login.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <algorithm>

User::User(std::string username, std::string password, std::string email){
    this->username = std::move(username);
    this->password = std::move(password);
    this->email = std::move(email);
}

User::~User() = default;

Login::Login() = default;

Login::~Login() = default;

void Login::registerUser(std::string username, std::string password, std::string email) {
    if (checkUsername(username) && checkEmail(email)) {
        users.push_back(new User(std::move(username), std::move(password), std::move(email)));
    }
}

void Login::loginUser(const std::string& username, const std::string& password){
    for (auto &user : users) {
        if (user->username == username && user->password == password) {
            LoginedUsers.push_back(user);
            return;
        }
    }
}

User* Login::getUser (const std::string& username){
    for (auto &user : users) {
        if (user->username == username) {
            return user;
        }
    }
    return nullptr;
}

void Login::removeUser(const std::string& username) {
    auto it1 = std::find_if(users.begin(), users.end(),
                            [&](User *user) { return user->username == username; });
    if (it1 != users.end()) {
        auto it2 = std::find(LoginedUsers.begin(), LoginedUsers.end(), *it1);
        if (it2 != LoginedUsers.end()) {
            LoginedUsers.erase(it2);
        }
        users.erase(it1);
    }
}

void Login::readFile(const std::string& path){
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

bool Login::checkUsername(std::string &new_username){
    for (auto &user : users) {
        if (user->username == new_username) {
            return false;
        }
    }
    return true;
}

bool Login::checkEmail(std::string &new_email){
    for (auto &user : users) {
        if (user->email == new_email) {
            return false;
        }
    }
    return true;
}

void Login::changeUsername(const std::string& username, std::string newUsername){
    for (auto &user : users) {
        if (user->username == username) {
            user->username = std::move(newUsername);
            return;
        }
    }
}

void Login::changePassword(const std::string& username, std::string newPassword){
    for (auto &user : users) {
        if (user->username == username) {
            user->password = std::move(newPassword);
            return;
        }
    }
}

void Login::changeMail(const std::string& username, std::string newMail, const std::string& password){
    for (auto &user : users) {
        if (user->username == username && user->password == password) {
            if(newMail != user->email) {
                user->email = std::move(newMail);
            }
            return;
        }
    }
}


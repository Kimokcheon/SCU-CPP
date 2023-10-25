#include "../include/login.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

User::User(std::string name, std::string pass, std::string mail){
    username = name;
    email = mail;
    password = pass;
}

User::~User() {
    username.clear();
    password.clear();
    email.clear();
}

void User::print() { // print name, password and email in one line
	std::cout << std::setw(10) << std::left;
	std::cout << username << password << std::setw(10) << email << std::endl;
}

Login::Login() {
    users.clear();
    LoginedUsers.clear();
}

Login::~Login() {
	for (auto user : users) {
		if (user != NULL) {
			delete user;
		}
	}
    users.clear();
    LoginedUsers.clear();
}

void Login::readFile(std::string path) { // read data from path
	std::ifstream fin(path);
	std::string str;
	std::getline(fin, str); // ignore the header
	std::string name, pass, mail, isLogged;
	while (fin >> name >> pass >> mail >> isLogged) {
		registerUser(name, pass, mail);
		if (isLogged == "yes")
			loginUser(name, pass);
	}
}

bool Login::checkUsername(std::string &new_username) {
    for (auto user : users) {
        if (user->username == new_username) {
            std::cout << "username already taken" << std::endl;
			return false;
        }
    }
    return true;
}

bool Login::checkEmail(std::string &new_email) {
    for (auto user : users) {
        if (user->email == new_email) {
            return false;
        }
    }
    return true;
}

void Login::registerUser(std::string username, std::string password, std::string email) { // function to creat a user
	if (checkUsername(username) == false) return;
	if (checkEmail(email) == false) return;
	User *p = new User(username, password, email);
	users.push_back(p);
}

void Login::loginUser(std::string username, std::string password) {
	for (auto user : users) {
		if (user->username == username) {
			if (user->password == password) {
				LoginedUsers.push_back(user);
				break;
			}
		}
	}
}

void Login::changeUsername(std::string username, std::string newUsername) {
	int hasExsist = 0;
	for (auto user : users) {
		if (user->username == newUsername) {
			hasExsist = 1;
			break;
		}
	}
	if (hasExsist == 1) return;
	for (auto &user : users) {
		if (user->username == username) {
			user->username = newUsername;
			break;
		}
	}
}

void Login::changePassword(std::string username, std::string newPassword) {
	for (auto &user : users) {
		if (user->username == username) {
			user->password = newPassword;
			break;
		}
	}
}

void Login::changeMail(std::string username, std::string newMail) {
	for (auto &user : users) {
		if (user->username == username) {
			user->email = newMail;
			break;
		}
	}
}

User* Login::getUser (std::string username) {
	for (auto user : users) {
		if (user->username == username) return user;
	}
	return nullptr;
}

void Login::removeUser(std::string username) {
	User *p = getUser(username);
	if (p != nullptr) {
		auto it = std::find(LoginedUsers.begin(), LoginedUsers.end(), p);
		if (it != LoginedUsers.end()) LoginedUsers.erase(it);
		users.erase(std::find(users.begin(), users.end(), p));
		delete p;
	}
}

void Login::printUsers() {
	for (auto user : users) {
		user->print();
	}
	for (auto user : LoginedUsers) {
		user->print();
	}
}
#include "../include/login.h"
#include <iostream>
#include <fstream>

namespace login {

User::User( const std::string& name, const std::string& pass, const std::string& mail ) : username(name) , password(pass) , email(mail) {}

User::~User() = default;

Login::Login() = default;

Login::~Login() {
    for( auto& t : users )
        delete t;
}

bool Login::checkUsername( const std::string& new_username ) {
    for( const auto& t : users ) {
        if( t -> username == new_username ) 
            return true;
    }
    return false;
}

bool Login::checkEmail( const std::string &new_email ) {
    for( const auto& t : users ) {
        if( t -> email == new_email ) 
            return true;
    }
    return false;
}

void Login::changeUsername(const std::string& username, const std::string& newUsername) {
    for( const auto& t : users ) {
        if( t -> username == username ) {
            t -> username = newUsername;
            return;
        }
    }
}

void Login::changePassword(const std::string& username, const std::string& newPassword) {
    for( const auto& t : users ) {
        if( t -> username == username ) {
            t -> password = newPassword;
            return;
        }
    }
}

void Login::changeMail(const std::string& username, const std::string& newMail) {
    for( const auto& t : users ) {
        if( t -> username == username ) {
            t -> password = newMail;
            return;
        }
    }
}

void Login::registerUser(const std::string& username, const std::string& password, const std::string& email) {
    if( checkUsername( username ) ) return;
    if( checkEmail( email ) ) return;
    User *p = new User( username , password , email );
    users.push_back( p );
}

bool Login::checkLoggedin( const std::string& username ) {
    for( const auto& t : LoginedUsers ) {
        if( t -> username == username ) return true;
    }
    return false;
}

void Login::loginUser(const std::string& username, const std::string& password) {
    if( checkLoggedin( username ) ) return;
    for( const auto& t : users ) if( t -> username == username ) {
        if( t -> password == password ) {
            LoginedUsers.push_back( t );
            return;
        }
    }
}

void Login::removeUser(const std::string& username) {
    for( auto& t : LoginedUsers ) {
        if( t -> username == username ) {
            std::swap( t , LoginedUsers.back() );
            LoginedUsers.pop_back();
            break;
        }
    }
    // std::cout << username << ' ' << LoginedUsers.size() << ' ' << ( getUser( username ) == nullptr ) << std::endl;
    for( auto& t : users ) {
        if( t -> username == username ) {
            std::swap( t , users.back() );
            users.pop_back();
            return;
        }
    }
}

User* Login::getUser( const std::string& username ) {
    for( const auto& t : users ) if( t -> username == username )
        return t;
    return nullptr;
}

void Login::readFile( std::string path ) {
    std::ifstream fin;
    fin.open( path );
    std::string got;
    std::getline( fin , got );
    std::string username , password , email , state;
    while( fin >> username >> password >> email >> state ) {
        // std::cout << username << ' ' << password << ' ' << email << std::endl;
        registerUser( username , password , email );
        if( state == "yes" ) loginUser( username , password );
    }
}

}
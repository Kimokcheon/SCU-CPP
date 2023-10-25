#include "../include/login.h"
User::User(std::string name, std::string password, std::string mail)
{
    username = name;
    this->password = password;
    email = mail;
}
bool Login::checkUsername(std::string &new_username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == new_username)
        {
            return true;
        }
    }
    return false;
}
bool Login::checkEmail(std::string &new_email)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->email == new_email)
        {
            return true;
        }
    }
    return false;
}
void Login::changeUsername(std::string username, std::string newUsername)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == username)
        {
            users[i]->username = newUsername;
        }
    }
}
void Login::changePassword(std::string username, std::string newPassword)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == username)
        {
            users[i]->password = newPassword;
        }
    }
}
void Login::changeMail(std::string username, std::string newMail)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == username)
        {
            users[i]->email = newMail;
        }
    }
}
void Login::registerUser(std::string username, std::string password, std::string email)
{
    if (!checkUsername(username) && !checkEmail(email))
    {
        User* newUser = new User(username, password, email);
        Login::users.push_back(newUser);
    }
}
void Login::loginUser(std::string username, std::string password)
{
    for(auto i : LoginedUsers)
    {
        if(i->username == username)
        {
            return;
        }
    }
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == username && users[i]->password == password)
        {
            Login::LoginedUsers.push_back(users[i]);
        }
    }
}
User* Login::getUser(std::string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == username)
        {
            return users[i];
        }
    }
    return nullptr;
}
void Login::removeUser(std::string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->username == username)
        {
            users.erase(users.begin() + i);
        }
    }
    for(int i = 0; i < LoginedUsers.size(); i++)
    {
        if(LoginedUsers[i]->username == username)
        {
            LoginedUsers.erase(LoginedUsers.begin() + i);
        }
    }
}
void Login::logoutUser(std::string username)
{
    for (int i = 0; i < LoginedUsers.size(); i++)
    {
        if (LoginedUsers[i]->username == username)
        {
            LoginedUsers.erase(LoginedUsers.begin() + i);
        }
    }
}
void Login::readFile(std::string path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
    }
    else
    {
        std::string line;
        std::string firstLine;
        std::getline(file, firstLine);
        while (std::getline(file, line))
        {
            std::string email, username, password, judge;
            int i = 0;
            while (line[i] != ' ')
            {
                username += line[i];
                i++;
            }
            while(line[i] == ' ')
            {
                i++;
            }
            while (line[i] != ' ')
            {
                password += line[i];
                i++;
            }
            while(line[i] == ' ')
            {
                i++;
            }
            while (line[i] != ' ')
            {
                email += line[i];
                i++;
            }
            while(line[i] == ' ')
            {
                i++;
            }
            while(line[i] != ' ' && i < line.size())
            {
                judge += line[i];
                i++;
            }
            registerUser(username, password, email);
            if(judge == "no")
            {
                logoutUser(username);
            }
            else if(judge == "yes")
            {
                loginUser(username, password);
            }
        }
    }
    file.close();
}
void Login::printUsers()
{
    for (int i = 0; i < users.size(); i++)
    {
        std::cout << users[i]->email << " " << users[i]->username << " " << users[i]->password << std::endl;
    }
}
void Login::printLoginedUsers()
{
    for (int i = 0; i < LoginedUsers.size(); i++)
    {
        std::cout << LoginedUsers[i]->email << " " << LoginedUsers[i]->username << " " << LoginedUsers[i]->password << std::endl;
    }
}
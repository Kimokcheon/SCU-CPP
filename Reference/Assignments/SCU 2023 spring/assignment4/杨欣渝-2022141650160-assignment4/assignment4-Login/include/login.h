#include <string>
#include <vector>

struct User{
    User(std::string name, std::string pass, std::string mail);
    ~User();
    std::string username;
    std::string email;
    std::string password;

    //----------------- other variables. you can add variables in this area
    };

struct Login {

    Login();

    ~Login();
    
    void readFile(std::string path); // reads the .txt file, then register the user inside readFile using theregisterUser function
    
    
    bool checkUsername(std::string &new_username); // checks if the user is already taken, if so, it returns true and the username shouldn't be created
    //and prints "username already taken"

    bool checkEmail(std::string &new_email); // only new emails may be pushedback to "emails" vector
    
    void changeUsername(std::string username, std::string newUsername);

    void changePassword(std::string username, std::string newPassword);

    void changeMail(std::string username, std::string newMail);
    
    void registerUser(std::string username, std::string password, std::string email); // function to creat a user

    void loginUser(std::string username, std::string password);

    void removeUser(std::string username);

    User* getUser (std::string username); // returns the usernames using the same email, returns false if that email doesnt exist



    std::vector<User*> users;
    std::vector<User*> LoginedUsers;


};

/*
a@gmail.com,ali,1234
a@gmail.com,alireza,1234   DOESN'T CREATE A NEW EMAIL
b@gmail.com,alireza,1234   DOESNT CREATE A NEW EMAIL NOR NEW USERNAME AS "alireza" IS ALREADY TAKEN
c@gmail.com,reza,4444
c@gmail.com,reza007,4444
c@gmail.com,reza11,4444

*/
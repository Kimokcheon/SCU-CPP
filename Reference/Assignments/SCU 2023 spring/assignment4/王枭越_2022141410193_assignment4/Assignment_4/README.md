# Assignment4 - Login

## Outline

In this homework we are going to implement a **Login and Register** class in c++. 
We will be implementing all our functions in `login.cpp` and `login.h`. remember you should put all declarations in the `.h` and all the implementations in the `.cpp` file.
We have two struct, Login and User. Login Struct has two vector of pointers of user to store users and registered users.

# Functions
Now, lets discuss each functions and see how they should be implemented. 

 - **User constructor and Destructor**
implement this functions in login.cpp.

 - **User constructor and Destructor**
implement this functions in login.cpp.


 - **registerUser**
implement this function so that it will create a user if doesn't exist another user with this username and password. for check this, implement checkEmail and checkUsername.
	```cpp
	void registerUser(std::string username, std::string password, std::string email);
	```

- **loginUser**
implement this function so that it will user logged in.
    ```cpp
       void loginUser(std::string username, std::string password);
    ```

- **getUser**

  implement this function so that it returns pointer of user with given username.
    ```cpp
    User* getUser (std::string username);
    ```
	
- **removeUser**  

  implement this function so that it remove user from our lists.
    ```cpp
    void removeUser(std::string username);
    ```
	
- **changeMail, changePassword, changeUsername**


- **readFile**
  implement this function so that it will read data from txt file and generate users and loggined status.
    ```cpp
    void readFile(std::string path);
    ```

# Finally
As mentioned before, keep all your implementations in `login.cpp` and `login.h`. do not alter other files at all. In case you want to test your code you may only use the `debug` section of the `main.cpp`.

```cpp
if (true) // make false to run unit tests  
{ 
    // debug section 
} 
else {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << RUN_ALL_TESTS() << std::endl;
}
```
<br/>

<p  align="center"> <b>GOOD LUCK</b> </p>

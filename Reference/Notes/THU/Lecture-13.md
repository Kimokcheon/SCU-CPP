# Lecture 13
##  Operator overloading
#### 1.  Please state the essence (本质) of operator overloading.

- Operator overloading provides a way to use operators for user-defined data types (classes). It is actually function overloading, where the operators are regarded as functions.

#### 2. Please state the restrictions on operator overloading.

- Cannot change the usage;
- Cannot define new operators by yourself;
- Cannot change precedence rules (运算符优先级);
- Cannot change the number of operands.
- Operators that cannot be overloaded: “`.`”, “`.*`”, “`::`”, “`?:`”

#### 3. Assume @ is an operator overloaded as member function, please write down the declaration of the functions corresponding to the following statements. Here, x, and y are objects of class TYPE. a) x @ y; b) @x; c) y@;

- x @ y: `return-type opeator@(const TYPE &right);`
- @x: `TYPE operator@();`
- y@: `TYPE operator@(int);`

#### 4. Assume @ is an operator overloaded as friend function, please write down the declarations of functions corresponding to the following statements. Here, x, and y are objects of class TYPE. a) x @ y; b) @x; c) y@;

- x @ y: `friend return-type opeator@(const TYPE &left, const TYPE &right);`
- @x: `friend TYPE operator@(TYPE &x);`
- y@: `friend TYPE operator@(TYPE &x, int);`

#### 5. When are you supposed to overload operators as member functions? And when are you supposed to overload operators as friend functions?

- For a binary operator, if the left-hand operand (左操作数) is NOT object of the user-defined class, i.e., it is of system-defined type, the operator cannot be overloaded as a member function. For example, the stream operator "`<<`" in "`cout <<`" cannot be overloaded as a member function. It can only be overloaded as a friend function.
- For a binary operator, if the left-hand operand is an object of the user-defined class, the operator can be overloaded as a member function.
- For an overloaded friend operator, the keyword **`friend`** may be removed if there is no need to access the private members.
- Moreover, overloaded member functions are preferred if we want to emphasize (强调) the association between the operator and the class.


#### 6. Why should the stream operators “<<” and “>>” be overloaded as friend functions?

- Because we want to use operator “`<<`” as in the form of “`cout << obj;`”, the operator is located before the object. However, if we overload the stream operator as a member functions, we can only use it as in the form of “`obj << cout`”. This is not allowed, because we are changing the usage of the stream operator.

#### 7. Please write down the declaration of the member function that is called for the following statement. (Note that v1 and v2 are well-defined objects.)
```cpp
  Vector3 v1, v2;
  v1 = v2;
```

- `Vector3& operator = (const Vector3& vec_);`


#### 8. Please write down a declaration of stream operator “<<” for vec3 (object of class Vector3), making the following statements legal.
```cpp
  a)  std::cout << vec3 << std::endl;
  b)  std::cout << std::left << std::setw  << vec3 << std::endl;
```

- `friend ostream & operator << (ostream &os, const Vector3 & vec3);`

#### 9. Why is bit-copy dangerous, especially when there are pointer members in the class? Please give an example where bit-copy is adopted by the compiler, which potentially causes bugs.

- When we do not define the assignment operator, the synthesized assignment operator uses the bitcopy to copy the member data. When there are pointer members in the copied objects, these objects share the same pointer value. This will cause bugs to programs.

```cpp
/* example */
#include <iostream>

using namespace std;
class A
{
private:
  string* m_s;
public:
  A() {
    m_s = NULL;
  }
  A(const string &s) {
    m_s = new string(s.c_str());
  }
  void modify() { *m_s += "?"; }
  ~A() {
    delete m_s;
  }
  void output() { cout << *m_s << endl; }
};

int main()
{
  A a("hello, world");
  A b;
  b = a;
  //do something to b to modify m_s
  b.modify();
  b.output();
  //a is also modified
  a.output();    
  //Moreover, the pointer m_s will be relased twice before exit.
  return 0;
}
```

#### 10. Please explain why self-assignment checking is important in overloaded assignment operator. How to check self-assignment?

- If there is pointer member in the class, the assignment process will first delete the original pointer to free the memory. If it is self-assignment, deleting the pointer first will cause data lost and errors.
- Self-assignment is meaningless but consumes more runtime.  
- We check self-assignment as follows:
```cpp
TYPE& operator = (const TYPE& src)
{
    if (&src != this)//check self-assignment
    {   
        //assignment …
    }
    return *this;
}
```

#### 11. Please state the difference between operator postfix ++ (--) and prefix ++ (--). Please write down the function body of operator postfix ++ and prefix ++ for the following class.
```cpp
  class Integer
  {
  public:
      Integer (int x = 0): _x (x) {}
  private:
      int _x;
  };
```

- Using postfix, the returned value is the original one before modification. Whereas using prefix, the returned value is the one after modification.
```cpp
// Prefix
const Integer& operator++ () {
    _x++;
    return *this;
}
// Postfix
const Integer operator++ (int) {
    Integer before (_x);
    _x++;
    return before;
}
```

##  Function object (函数对象)
#### 12. What is a function object? What is the difference between function objects and normal functions?

- Function object is an object of a class with overloaded function call operator “`()`”.
- Function object is essentially an object that is unitity of member data and member functions.
- Normal functions can only perform computation tasks.

#### 13. What is the difference between function objects and normal objects?

- A function object "`fo`" is different from a normal object "`no`" in that we can use the function "`fo(args)`". But we cannot use the function "`no(args)`".

#### 14. Please state the advantages of function object over function pointer (函数指针).
- Function object can store and pass data (存储和传递数据). But function pointer cannot.
- Function objects enable type checking for safe usage. Integrated with template, functional objects are much more powerful, and are thus used in STL, Boost, CGAL, etc.
- For tuning the functionality (功能), different function objects  could be created with different parameters passed to the constructor. Function pointer can only point to an existing function with fixed functionality.

#### 15. Please complete the missing code (e.g., add constructor, copy constructor, move assignment operator, and functional call operator) in the following program such that we can obtain the sum of the integers in array arr.
```cpp
#include <iostream>
#include <array>
#include <algorithm>
#include <random>
const size_t size = 1 << 5;

std::ostream& operator << (std::ostream& os, const Sum& sum)
{
    os << "sum:" << sum._x << std::endl;
    return os;
}
int main ()
{
    std::random_device rd;
    std::mt19937 mt (rd ());
    std::uniform_int_distribution<> dis (0, size);
    std::array<int, size> arr;
    for (auto& element: arr) {
        element = dis (mt);
        std::cout << element << " ";
    }
    std::cout << std::endl;

    Sum s (0);
    //from C++11, for_each returns std::move(s).
    s = std::for_each (std::begin (arr), std::end (arr), s);
    std::cout << s;
    return 0;
}
```
  - Answer is given as follows:

```cpp
//To compile, type "g++ main.cpp -std=c++11"
//main.cpp
#include <iostream>
#include <array>
#include <algorithm>
#include <random>
const size_t size = 1 << 5;

class Sum {
    private:
        int _x;
    public:
        Sum(int s = 0): _x(s) {}
        //copy constructor
        Sum(const Sum& a):_x(a._x) {
            std::cout<<"Copy constructor" << std::endl;
        }
        //move assignment
        Sum& operator=(Sum&& a) {
            std::cout<<"Move assignment" << std::endl;
            if (&a == this)
                return *this;
            this->_x = a._x;
            a._x = 0;
            return *this;
        }
        void operator()(int x) {
            this->_x += x;
        }
        friend std::ostream& operator << (std::ostream&, const Sum&);
};

std::ostream& operator << (std::ostream& os, const Sum& sum)
{
    os << "sum:" << sum._x << std::endl;
    return os;
}
int main ()
{
    std::random_device rd;
    std::mt19937 mt (rd ());
    std::uniform_int_distribution<> dis (0, size);
    std::array<int, size> arr;
    for (auto& element: arr) {
        element = dis (mt);
        std::cout << element << " ";
    }
    std::cout << std::endl;

    Sum s (0);
    //from C++11, for_each returns std::move(s).
    s = std::for_each (std::begin (arr), std::end (arr), s);
    std::cout << s;
    return 0;
}
```

## Lambda Expressions
#### 16. What is a lambda expression in C++?
- Lambda 表达式用来定义和创建匿名的函数对象。
- Lambda 表达式形如：
```
[函数对象参数]（操作符重载函数参数）mutable 或 exception 声明或不加 -> 返回值类型 {函数体}
```
- 例如以下程序可以完成 int a[5] 的排序，其中lambda表达式实现了比较运算。
```
sort(a, a + 5, [](int x, int y)->bool{return x < y;});
```

# This page lists the useful C++ grammars, especially for C++11, C++14, C++17 and C++20.

## If Statement with Initializer (since C++17)

Add an initializer to the *if* statement. It allows you to declare arrays and arbitrary many variables in the *if* statement itself, and ensures that they don't leak out of the *if* scope.

Grammar: 

```c++
if (init-statement condition) {
    // Do something when condition is true
} else {
    // Do something when condition is false
}
```

Example:

```c++
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));
  if (int number = rand(); number % 2 == 0) {
    std::cout << number << " is an even number" << std::endl;
  } else {
    std::cout << number << " is an odd number" << std::endl;
  }
  return 0;
}
```

## tuple

​	C++11 introduced tuple, an extension of pair, to simply package several values into a structure.

```c++
tuple<int, double, char> t(1, 2.0, 'a');
// return the reference
get<0>(t) = 2;
cout << get<0>(t) << endl;  // 2

std::tuple<int, double, std::string> f() {
  return std::make_tuple(1, 2.3, "456");
}
auto [x, y, z] = f();  // structured binding (C++17)
```

## noexcept

​	Starting with C++11, we've seen a lot of code with the keyword noexcept. This keyword tells the compiler that no exceptions will occur in the function, which is conducive to the compiler to do more optimization of the program. If the noexcept function throws an exception outward (if the exception isn't caught inside the function and handled), the program terminates directly, calling the std::terminate() function, which internally calls std::abort() to abort the program.

```c++
constexpr initializer_list() noexcept
: _M_array(0), _M_len(0) { }

// It means that if the operation x.swap (y) does not have an exception, then the function swap(Type& x, Type& y) will not have an exception
void swap(Type& x, Type& y) noexcept(noexcept(x.swap(y))) //C++11
{
	x.swap(y);
}
```

Use of noexcept is encouraged in the following situations:

- move constructor
- move assignment
- destructor (default)
- Leaf Function

## Zero Initialization

For fundamental types such as int, double, or pointer types, there is no default constructor that initializes them with a useful default value. Instead, any noninitialized local variable has an undefined value:

```cpp

void foo() {
  int x;    // x has undefined value
  int* ptr; // ptr points to anywhere
}

```

Then the following code is undefined if T is a fundamental type:

```cpp

#include<iostream>
template<typename T>
void foo() {
  T x;
  std::cout<<x<<std::endl; // x is undefined
}

```

C++ introduces the following mechanism to call explicitly a default constructor for built-in types that initializes them with zero (or false, nullptr). As a consequence, you can ensure proper initialization even for built-in types by writing:

```cpp

template<typename T>
void foo() {
  T x{}; // x is zero/false/nullptr
}

template<typename T>
void bar(T p = T{}) { // the default value of p is not undefined
  ...
}

```

## Argument-Dependent Lookup

ADL applies primarily to unqualified names that look like they name a nonmember function ina function call or operator invocation. ADL does not happen if ordinary look up finds

- the name of a member function
- the name of a variable
- the name of a type
- the name of a block-scope function declaration

ADL is also inhibited if the name of the function to be called is enclosed in parentheses.

Otherwise, if the name if followed by a list of argument expressions enclosed in parentheses, ADL proceeds by looking up the name in namespaces and classes associated with the types of the call arguments, ie. assoceated namespaces and associated classes:

- for built-in types, this is the empty set
- for pointer and array types -> of the underlying type
- for enumeration types, the namespace in which the enumeration is declared
- for class members, the enclosing class
- for class types, itself, the enclosing class, and base classes
- for template classes, add that of the template parameters
- for function types, add that of the parameter types and return type

example:

```cpp

#include<iostream>

namespace X {
  template<typename T> void f(T);
}

namespace N {
  using namespace X;
  enum E {e1};
  void f(E) {
    std::cout << "N::f(N::E) called\n";
  }
}

void f(int) {
  std::cout << "::f(int) called\n";
}

int main() {
  ::f(N::e1); // qualified function name: no ADL
  f(N::e1);   // ordinary lookup finds ::f() and ADL finds N::f(), the latter is preferred
}

```

## Reference Qualifier

C++ introduces a new feature called reference qualifier to constrain member functions to be used only when the class is a lvalue or a rvalue.

Example 1

```cpp

class Widget {
  public:
  void doWork() &;  // called when *this is a glvalue
  void doWork() &&; // called when *this is a prvalue
}

Widget makeWidget();
Widget w;

w.doWork();            // w is a lvalue, calls the glvalue version
makeWidget().doWork(); // makeWidget() is a prvalue, calls the prvalue version

```

Example 2

```cpp

#include <iostream>

class W {
 public:
  void f() & { std::cout << "f() & called.\n"; }
  void f() && { std::cout << "f() && called.\n"; }
};

int main() {
  W w1;
  W w2 = std::move(w1);
  w2.f();  // calls f() & because w2 is an xvalue
}

```

## Value Categories Explained

The core categries since C++11 are lvalue, prvalue(pure rvalue) and xvalue. The composite categories are: glvalue(generalized lvalue), ie. lvalue and xvalue, and rvalue, ie. xvalue and prvalue.

- A glvalue is an expression whose evaluation determines the identiy of an object, bit-field, or function(ie. an entity that has storage)
- A prvalue is an expression whose evaluation initializes an object or a bit-field, or computes the value of the operand of an operator
- An xvalue is a glvalue designation an object or bit-field whose resources can be reused(usually because it is about to eXpire)
- An lvalue is a glvalue that is not an xvalue
- An rvalue is an expression that is either a prvalue or an xvalue

Examples of lvalues:

- Expressions that designate variables or functions
- Applications of the built-in unary * operator
- An expression that is just a string literal
- A call to a function with a return type that is an lvalue reference

Examples of prvalues:

- Expressions that consist of a literal that is not a string literal or a user-defined literal
- Applications of the built-in unary & operator
- Applications of built-in arithmetic operators
- A call to a function with a return type that is not a reference type
- Lambda expressions

Examples of xvalues:

- A call to a function with a return type that is an rvalue reference to an object type(eg. std::move())
- A cast to an rvalue reference to an object type

Example:

```cpp

int x = 3; // x here is a variable, not an lvalue. 3 is a prvalue initializing the variable x.

int y = x; // x here is an lvalue. The evaluation of that lvalue expression does not produce
           // the value 3, but a designation of an object containing the value 3. That lvalue
           // is then converted to a prvalue, which is that initializes y.

```

## Use [Regular Expressions](https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expressions) in C++11

Include header `<regex>` for type `regex` which records the regex string, and `smatch` which manages match results.

```cpp
string baseString("OOP_QA");
regex myRegex("([A-Z]+)");  //match strings including only uppercase letters
smatch result;

for(int i=0;regex_search(baseString,result,myRegex);i++){  //search for all matched substrings
  cout<<"Group "<<i<<":"<<result[0]<<endl;  //result
  baseString=result.suffix().str();  //skip the present substring
}
```


[Reference](http://www.cplusplus.com/reference/regex/)


## Measure Time Accurately in C++11


Header `<chrono>` should be included.

```cpp
//An example from reference

using namespace chrono;
steady_clock::time_point t1=steady_clock::now();

//do sth

steady_clock::time_point t2=steady_clock::now();

duration<double>diff=duration_cast<duration<double>>(t2-t1);
cout<<diff.count()<<" seconds.";
```

[Reference](http://www.cplusplus.com/reference/regex/)

## three-way comparison

Before C++20, when we want to make a class comparable, we have to overload many operators (`==`, `!=`, `<`, `<=`, `>`, `>=`). Though [Boost](https://www.boost.org/ "Boost C++ Libraries") uses a tricky way to implement a helper `boost/operators.hpp`：

```c++
#include <boost/operators.hpp>
#include <cassert>

class Foo : public boost::less_than_comparable<Foo> {
 public:
  Foo(int x) : m_x(x) {}
  friend bool operator<(Foo lhs, Foo rhs) { return lhs.m_x < rhs.m_x; }

 private:
  int m_x;
};

int main() {
  Foo a(1), b(2);
  assert(b > a); // We only overloaded operator<.
}
```

It is still very inconvenient.

C++20 introduces a new operator `<=>` called three-way comparison operator or spaceship operator (because it looks like a spaceship). Now, we only need to overload this three-way operator or even simply set as default (`=default`). The compiler will generate other comparison operators automatically and correctly.
**Note**: If `<=>` is not defaulted, `==` and `！=` won’t be generated. Here is the [reason](https://stackoverflow.com/questions/58780829/equality-operator-does-not-get-defined-for-a-custom-spaceship-operator-implement "Stack Overflow").

There are three available return types (declared in header file `compare`):

- `std::strong_ordering`
- `std::weak_ordering`
- `std::partial_ordering`

They represent for different ordering types as their names show. We have learned these three ordering types in Discrete Mathematics (1). So I will just give three examples to show how it works.

- strong ordering

  ```c++
  #include <cassert>
  #include <compare>
  
  struct Foo {
    int x;
    friend std::strong_ordering operator<=>(Foo lhs, Foo rhs) {
      return lhs.x <=> rhs.x;
    }
    friend bool operator==(Foo lhs, Foo rhs) { return (lhs <=> rhs) == 0; }
  };
  
  int main() {
    Foo a{0}, b{1};
    assert(!(a == b)); assert(a != b);
    assert(a < b); assert(a <= b);
    assert(b > a); assert(b >= a);
  }
  ```

- weak ordering

  ```c++
  #include <cassert>
  #include <compare>
  
  struct Foo {
    int x, y;
    friend std::weak_ordering operator<=>(Foo lhs, Foo rhs) {
      return lhs.x <=> rhs.x;
    }
    friend bool operator==(Foo lhs, Foo rhs) { return (lhs <=> rhs) == 0; }
  };
  
  int main() {
    Foo a{0, 1}, b{0, 2};
    assert(a == b); assert(!(a != b));
    assert(!(a < b)); assert(a <= b);
    assert(!(b > a)); assert(b >= a);
  }
  ```

- partial ordering

  ```c++
  #include <cassert>
  #include <compare>
  
  struct Foo {
    int x, y;
    friend std::partial_ordering operator<=>(Foo lhs, Foo rhs) {
      auto cmp_x = (lhs.x <=> rhs.x);
      auto cmp_y = (lhs.y <=> rhs.y);
      if (cmp_x == cmp_y)
        return cmp_x;
      else
        return std::partial_ordering::unordered;
    }
    friend bool operator==(Foo lhs, Foo rhs) { return (lhs <=> rhs) == 0; }
  };
  
  int main() {
    Foo a{0, 1}, b{1, 0};
    assert(!(a == b)); assert(a != b);
    assert(!(a < b)); assert(!(a <= b));
    assert(!(b > a)); assert(!(b >= a));
  }
  ```

You can find more information on [cppreference.com](https://en.cppreference.com/ "cppreference.com"):

- [comparison operators](https://en.cppreference.com/w/cpp/language/operator_comparison "cppreference.com")
- [default comparisons](https://en.cppreference.com/w/cpp/language/default_comparisons "cppreference.com")

## `decltype` in C++11

Just like its name "declared type", it is an operator that can check the declared type of an expression. 

Unlike `auto`, `decltype` can distinguish `const` varaible and reference. Besides, it won't execute the expression. It will just infer the type.

```cpp
int func();

int main()
{
    int var = 2;
    
    decltype(var) type1;  // type1 is int
    decltype(func()) type2;  // func is not defined, but decltype just analyze the type, won't execute the function

    return 0;
}
```

*Author* : Biru Yang    *Date*: 2020.6.24

***decltype***与我们在课上曾介绍过的关键字***auto***功能较为相似：**类型推断**。

*auto*可以让我们无需指定表达式的类型，直接用其值初始化新变量；

而**decltype**则可以让我们从表达式类型推断出变量类型，而具体初始化的值则可不指定/另外指定。

示例用法如下：

```c++
int function();
const float a = 4.0;
int B = 0, &refB = B, *ptrB = &B;

int main()
{
    int a = 20;
    
    /*用变量:temp_1为const float类型*/
    decltype(a) temp_1 = 4.0;
    
    /*用函数返回值：temp_2为int类型*/
    decltype(function()) temp_2;  //尽管function()并未定义，该程序同样可以运行，这与auto不同
    
    /*用引用：temp_3为引用*/
    decltype(refB) temp_3 = B;
    
    /*用指针：temp_4为int*的指针*/
    decltype(ptrB) temp_4;
    
    return 0;
}
```

**decltype**与**auto**在功能上类似，但具体使用时有以下几点不同：

> 1.  ***auto***忽略顶层***const***，***decltype***保留顶层***const***。
> 2.  对引用操作，***auto***推断出原有类型，***decltype***推断出引用。
> 3.  ***auto***推断时会实际执行，***decltype***只做分析。


## 条件分支语句初始化

*Author* : Biru Yang    *Date*: 2020.6.24


往常只能在 ***for*** 语句中进行变量初始化，如今可以在 ***if*** 和 ***switch*** 语句中进行初始化：

```c++
int main()
{
    int num = 2;
    if (int i = 0; i == num) { //if中初始化
        /*do something*/
    }
    switch (int k = 0; k) { //switch中初始化
        case 0: /*do something*/ break;
        default: /*do something else*/ break;
    }
}
```


## 聚合初始化

*Author* : Biru Yang    *Date*: 2020.6.24


可使用**嵌套的花括号**对**嵌套的结构体**进行初始化：

```C++
struct Struct1 {
    int a;
    double b;
}

struct Struct2 {
    char c;
    Struct1 s1;
}

int main()
{
    Struct1 st_1{10, 3.14};
    Struct2 st_2{'e',{0, 2.71}};  //嵌套花括号
}
```



### Reference :

+ [C++11新标准学习：decltype关键字](https://www.cnblogs.com/ghbjimmy/p/10636030.html)
+ [C++17新特性个人总结](https://blog.csdn.net/qq811299838/article/details/90371604)


## Concept

**Concepts** in C++ are an extension to templates feature. A concept, associated with a template, provides a constraint to the template, which limits the set of arguments that are accepted as template parameters.ii That is, A concept is a set of requirements that a set of related types) must fulfill to be used correctly in generic algorithm. Template instantiations which don’t follow corresponding concepts will lead to errors when compiling. So concepts feature simplifies compiler diagnostics for failed template instantiations.

```c++
1. concept ChannelConcept<typename T> : EqualityComparable<T>
2. {
3. typename value_type = T; // use channel_traits<T>::value_type to access it
4. where ChannelValueConcept<value_type>;
5. typename reference = T&; // use channel_traits<T>::reference to access it
6. typename pointer = T*; // use channel_traits<T>::pointer to access it
7. typename const_reference = const T&; // use channel_traits<T>::const_reference to acce ss it
8.
typename const_pointer = const T*; // use channel_traits<T>::const_pointer to access it
9. static const bool is_mutable; // use channel_traits<T>::is_mutable to access it
10.
11. static T min_value(); // use channel_traits<T>::min_value to access it
12. static T max_value(); // use channel_traits<T>::min_value to access it
13. };
14.
15. concept MutableChannelConcept<ChannelConcept T> : Swappable<T>, Assignable<T> {};
16.
17. concept ChannelValueConcept<ChannelConcept T> : Regular<T> {};
```

## "auto" in C++11

### auto的原理是根据变量后面的取值，来推测变量的类型
### 使用auto可以简化变量初始化

```C++
    std::vector<std::string> ve;
    std::vector<std::string>::iterator it = ve.begin();
    auto it1 = ve.begin();
```

此外，如果是可用迭代器的对象的话，还可以这样操作：

```C++
    int main() {
        vector<int> v;
        v.push_back(1);v.push_back(2);v.push_back(3);
        for(auto i:v) cout<<i<<" ";
        return 0;
    }
```

auto在这里替代的就是int

### 使用 auto 可以避开 private class name 的限制

 ```cpp
 class A{
   private:
     class B{
       private:
         int a;
         char b;
       public:
         B(int _a,char _b) : a(_a) , b(_b) {}
     };
   public:
     B getB(int _a = 0, char _b = '0'){
         return B{_a, _b};
     }
 };
 
 int main(){
     A A_var;
     // A::B B_var = A_var.getB(); // compile error!
     auto B_var = A_var.getB();
     return 0;
 }
 ```

### Argument Packs（参数包）

Have you wondered why printf can accept any number of parameters?

Actually, it isn't a quite complex grammar, and you can implement a `printf` by yourself in only 10 lines.

This grammar is called "argument packs", supported since C++11.

Let's see a example:

```cpp
#include <iostream>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           std::cout << value;
           tprintf(format+1, Fargs...); // recursive call
           return;
        }
        std::cout << *format;
    }
}
 
int main()
{
    tprintf("% world% %\n","Hello",'!',123);
    return 0;
}
```

In short, we use `...xxx` to give a parameter pack in arguments, and we use `args...` to use it in somewhere.

The most comfortable way to "open" a parameter pack is to use a recursive function like above.

## "nullptr" in C++11

为了区分NULL和0，C++11引入了空指针nullptr。nullptr的类型为std::nullptr_t而非指针或int，可以保证nullptr表示空指针而不是0。
在使用空指针时，应该尽量使用nullptr而不是NULL。


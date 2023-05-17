[TOC]

# c++学习笔记

## 1.Template Functions

### 1.1 **generic C++**

C++ is strongly typed, but ==generic C++== lets you parametrize data types

==e.g. code==

```c++
template<typename T, typename U>
auto Min(T a, U b)
{
	return a > b ? b : a;
}
```

### 1.2 **Template Metaprogramming**（模板元编程）

Remember: like in template classes, **template functions** **are not compiled until used!**

● For each instantiation with different parameters（参数）, the compiler generates a new specific version of your template

● After compilation, it will look like you wrote each version yourself

**The code doesn’t exist until you instantiate it, which runs quicker.**

Can we take advantage of this behavior?

==e.g. code==

**TMP**使用的过程中，只编译一次，相当于递归的过程。大大地减少了运行时间。

Normally, code runs during **runtime**.

With template metaprogramming, code runs **once** during **compile time**!

```c++
template <int N>
struct Fibonacci 
{
  static const int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template <>
struct Fibonacci<0> 
{
  static const int value = 0;
};

template <>
struct Fibonacci<1> 
{
  static const int value = 1;
};

```

**TMP**用在不定量参数模板递归

```c++
template<typename T>
T sum(T t) {
  return t;
}

template<typename T, typename... Args>
T sum(T t, Args... args) {
  return t + sum(args...);
}

int result = sum(1, 2, 3, 4, 5);
```

TMP isn’t used that much, but it has some interesting implications:（**具体应用**）

● Optimizing matrices/trees/other mathematical structure operations

● Policy-based design

● Game graphics

==Advantages==

● Template functions allow you to parametrize（**参数化**） the type of a function to be anything without changing functionality

● Generic programming can solve a complicated conceptual（**概念性的**） problem for any specifics – powerful and flexible!

● Template code is instantiated at compile time; template metaprogramming takes advantage of this to run code at compile time

==By the way== : There are few universal, scientifically proven pieces of wisdom that will lead to a happier life:

1. Look both ways before crossing the street.
2. Never tell a pre-med you’re stressed.
3. When coding, never reinvent the wheel.

**That's why we need template!**

### 1.3 **Predicate Functions**（谓词函数）

UniPred is what’s called a **function pointer!**

● Function pointers can be treated just like other pointers

● They can be passed around like variables as parameters or in template functions!

● They can be called like functions!

==e.g. code== 

下面是一个简单的示例，其中定义了一个谓词函数 `is_odd`，用于测试一个整数是否为奇数

```c++
bool is_odd(int n) {
    return n % 2 == 1;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto odd_num = std::find_if(nums.begin(), nums.end(), is_odd);
    if (odd_num != nums.end()) {
        std::cout << "The first odd number is: " << *odd_num << std::endl;
    } else {
        std::cout << "No odd numbers found." << std::endl;
    }
    return 0;
}
```

### 1.4 Lambda Functions

We want our function to know more information about our predicate.

●However, we can’t pass in more than one parameter.

●How can we pass along information without needing another parameter?

Lambdas are **inline**, anonymous（**匿名的**） functions that can know about functions declared in their same scope!

```c++
[capture list] (parameter list) -> return type { function body }
```

You can capture any outside variable, both by reference and by value.

● Use just the **=** symbol to capture everything by value, and just the **&** symbol to capture everything by reference

![图片1](.\c++学习笔记src\图片1.png)

Lambdas are pretty computationally（**在计算上**） cheap and a great tool!

● Use a lambda when you need a short function or to access local variables in your function.

● If you need more logic or overloading, use function pointers.

![图片2](.\c++学习笔记src\图片2.png)

A **functor**（**仿函数**） is any class that provides an implementation of operator().

● They can create **closures** of  “customized” functions!

● Lambdas are just a reskin（**改头换面**） of functors!

![图片3](.\c++学习笔记src\图片3.png)



## 2.1 c++ keywords

### 2.1 this pointer

Every object has access to its own address through the const pointer **this**

Explicit usage is not mandatory（**强制性的**） (and not suggested) 

this is necessary when:

• The name of a local variable is equal to some member name

• Return reference to the calling object

```c++
#include <iostream>
class Rectangle {
private:
    int width, height;
public:
    Rectangle(int w, int h) {
        this->width = w;
        this->height = h;
    }
    int area() {
        return this->width * this->height;
    }
};

int main() {
    Rectangle rect(5, 10);
    std::cout << "Area of rectangle: " << rect.area() << std::endl;
    return 0;
}
```

==Explanation==

- The `Rectangle` constructor takes two arguments, `w` and `h`, and initializes the `width` and `height` data members using the `this` pointer. This is done to disambiguate between the constructor arguments and the data members with the same name.

- The `area()` function calculates and returns the area of the rectangle using the `width` and `height` data members. Again, the `this` pointer is used to access the data members of the current object.

### 2.2 static

**The keyword** **static** **declares members (fields or methods) that are not bound to class instances. A** **static** **member is shared by** **all** **objects of the class**

- A **static member function** can only access static class members

- A **non- static member function** can access static class members

- Non-const static data members cannot be directly initialized **inline**...before C++17

### 2.3 const

**Const member functions (inspectors or observer) are functions marked with** **const** **that are not allowed to change the object state**

Member functions without a const suffix（**后缀**） are called non-const member functions or **mutators**. The compiler prevents from inadvertently（**无意中的**） mutating/changing the data members of observer functions

If an instance of a class is declared as `const`, then you can only call `const` member functions on that instance. This is because a `const` instance of a class is considered to be read-only, and any attempt to modify its state would violate（**违反**） the `const` contract.

```c++
class MyClass {
public:
    int getValue() const {
        return value;
    }

    void setValue(int newValue) {
        value = newValue;
    }

private:
    int value;
};

int main() {
    const MyClass myConstObject;
    int value = myConstObject.getValue(); // OK
    myConstObject.setValue(42); // Error: cannot modify a const object
    return 0;
}

```

- In this example, we declare an instance of `MyClass` as `const`, which means that we can only call `const` member functions on it. We can call the `getValue()` function, which is declared as `const`, but we cannot call the `setValue()` function, which modifies the state of the object, because it is not declared as `const`.

- If you attempt to call a non-`const` member function on a `const` instance of a class, the compiler will generate an error.

### 2.4 mutable

**mutable** **members of** **const** **class instances are modifiable**

In C++, the `mutable` keyword is used to declare a member variable of a class that can be modified even if the containing object is declared as `const`. This is useful when you have a member variable that logically belongs to the class, but does not affect its external behavior.

```c++
class MyClass {
public:
    int getValue() const {
        return value;
    }

    void setValue(int newValue) const {
        mutableValue = newValue;
    }

private:
    int value;
    mutable int mutableValue;
};

int main() {
    const MyClass myConstObject;
    int value = myConstObject.getValue(); // OK
    myConstObject.setValue(42); // OK: mutable variable can be modified
    return 0;
}
```

- In this example, we have a `MyClass` class with two member variables: `value` and `mutableValue`. The `getValue()` function returns the value of the `value` member variable, and is declared as `const` to indicate that it does not modify the state of the object.

- The `setValue()` function, on the other hand, modifies the `mutableValue` member variable, which is declared as `mutable`. This means that even though `myConstObject` is declared as `const`, we can still call `setValue()` on it and modify the value of `mutableValue`.

### 2.5 using

The using keyword is used to declare a *type alias*（**别名**） tied to a specific class

```c++
#include <iostream>

namespace myNamespace {
    void myFunction() {
        std::cout << "Hello, world!" << std::endl;
    }
}

int main() {
    using myNamespace::myFunction;
    myFunction(); // prints "Hello, world!"
    return 0;
}
```

- In this example, we have a namespace called `myNamespace` that contains a function called `myFunction`. In `main()`, we use the `using` keyword to introduce `myFunction` into the current scope. This means that we can call `myFunction()` without having to qualify it with the `myNamespace::` prefix（**前缀**）.

- Note that you can also use `using namespace` to bring all names from a namespace into the current scope. However, this can be dangerous if the namespace contains names that conflict with names in the current scope, **so it should be used with caution**. It's generally better to use `using` to bring in only the names you need, and to qualify them with the namespace prefix to avoid naming conflicts.

### 2.6 delete

**The** **delete** **keyword explicitly marks a member function as deleted and any use results in a compiler error. When it is applied to** **copy/move** **constructor** **or** **assignment, it prevents the compiler from implicitly generating these functions**

```c++
class MyClass {
public:
    MyClass() {
        // constructor code here
    }

    // disable copy constructor
    MyClass(const MyClass&) = delete;

    // disable move constructor
    MyClass(MyClass&&) = delete;

    // disable copy assignment
    MyClass& operator=(const MyClass&) = delete;

    // disable move assignment
    MyClass& operator=(MyClass&&) = delete;

private:
    // member variables here
};
```

- In this example, we have a `MyClass` class that has a default constructor, but all other member functions are marked as `delete`. This means that copying or moving objects of the class will result in a compiler error.

- Note that you can also use `delete` to mark other member functions as deleted, such as specific overloaded functions or functions that take specific arguments. This can be useful when you want to prevent certain uses of a class, or when you want to provide more informative error messages to users of your code.

## 3. Polymorphism

**In Object-Oriented Programming (OOP),** **polymorphism** **(meaning “having multiple forms”) is the capability of an object of mutating its behavior in accordance（按照） with the specific usage** **context**

-  At run-time, objects of a *base class* behaves as objects of a *derived class*

- A **Base** class may define and implement polymorphic methods, and **derived** classes can **override（覆盖）** them, which means they provide their own implementations, invoked（**被调用的**） at run-time depending on the context

### 3.1 Virtual methods

==Example==

![图片4](.\c++学习笔记src\图片4.png)

**The virtual keyword is not *necessary* in derived classes, but it improves *readability* and clearly advertises the fact to the user that the function is virtual**

![图片5](.\c++学习笔记src\图片5.png)

### 3.2 Virtual Table

**The** **virtual table** (**vtable**) is a lookup table of functions used to resolve function calls and support **dynamic dispatch**（**动态调度**） **(late binding)**

- A *virtual table* contains one entry for each virtual function that can be called by objects of the class. Each entry in this table is simply a function pointer that points to the *most-derived* function accessible by that class

- The compiler adds a *hidden* pointer to the base class which points to the virtual table for that class (sizeof considers the vtable pointer)

```c++
class Animal {
public:
    virtual void speak() {
        cout << "I am an animal" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() {
        cout << "I am a dog" << endl;
    }
};

int main() {
    Animal* a = new Animal();
    Animal* d = new Dog();
    
    a->speak(); // prints "I am an animal"
    d->speak(); // prints "I am a dog"
    
    return 0;
}
```

- In this example, the `Animal` class has a virtual function `speak()`, which is overridden by the `Dog` class. When the `speak()` function is called on the `Animal` and `Dog` objects, the correct function is called based on the actual type of the object at runtime, thanks to the virtual table.
- ==Lesson learned: Never use malloc in C++==

### 3.3 Override keyword

**The** **override** **keyword ensures that the function is virtual and is** **overriding** **a virtual function from a base class**

- It **forces** the compiler to check the base class to see if there is a virtual function with this exact signature 
- override implies virtual ( **virtual should be omitted（省略）**)

![图片6](.\c++学习笔记src\图片6.png)

### 3.4 **final Keyword**

**The** **final** **keyword prevents inheriting from classes or overriding methods in derived classes**

![图片7](.\c++学习笔记src\图片7.png)

- All classes with **at least one virtual method** should declare a virtual destructor

- ```c++
  class Animal {
  public:
      virtual void speak() {
          cout << "I am an animal" << endl;
      }
      virtual ~Animal() {
          cout << "Animal destructor called" << endl;
      }
  };
  
  class Dog : public Animal {
  public:
      void speak() {
          cout << "I am a dog" << endl;
      }
      ~Dog() {
          cout << "Dog destructor called" << endl;
      }
  };
  
  int main() {
      Animal* a = new Animal();
      Animal* d = new Dog();
      
      a->speak(); // prints "I am an animal"
      d->speak(); // prints "I am a dog"
      
      delete a; // prints "Animal destructor called"
      delete d; // prints "Dog destructor called" followed by "Animal destructor called"
      
      return 0;
  }
  ```

In this example, both the `Animal` and `Dog` classes have virtual destructors. When the `delete` operator is called on the `Animal` and `Dog` objects, the correct destructor is called for the actual type of the object at runtime, thanks to the virtual destructor. This allows the `Dog` class to properly clean up any resources it has allocated, in addition to the resources allocated by the `Animal` class.

- **Do not use default parameters in virtual methods**
- **Default parameters are not inherited**

### 3.5 **Pure Virtual Method** 

- **A** **pure virtual method** **is a function that** **must** **be implemented in derived classes (concrete implementation)**

- Pure virtual functions can have or not have a body

```c++
class Animal {
public:
    virtual void speak() = 0; // pure virtual function
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() {
        cout << "Woof!" << endl;
    }
};

int main() {
    Animal* a = new Dog();
    a->speak(); // prints "Woof!"
    delete a;
    
    return 0;
}
```

- In this example, the `Animal` class contains a pure virtual function `speak()`. This means that any class derived from `Animal` must provide an implementation for the `speak()` function. The `Dog` class provides an implementation for the `speak()` function, so it can be instantiated and used like any other class.
- A class that contains at least one pure virtual function is called an abstract class, and cannot be instantiated directly. Instead, abstract classes are typically used as base classes for other classes that provide concrete implementations of the pure virtual functions.
- One benefit of using pure virtual functions is that they allow for a clean separation of interface and implementation. ==By defining a set of pure virtual functions in the base class, we can define a clear interface that any derived class must implement.== This can make it easier to reason about the behavior of the class hierarchy, and can make it easier to swap out different implementations of the same interface.

## 4. Operator Overloading

**Operator overloading** **is a special case of polymorphism in which some** **operators** **are treated as polymorphic functions and have different behaviors depending on the type of its arguments**

==**Categories not in bold are rarely used in practice**（非黑体字的类别实践之中很少用）==

![图片8](.\c++学习笔记src\图片8.png)

### 4.1 Subscript Operator operator[]

The **array subscript** operator[] allows accessing to an object in an array-like fashion

The operator accepts **everything** as parameter, not just integers.

```c++
#include <bits/stdc++.h>
struct A
{
	char permutation[6]{'c', 'b', 'd', 'a', 'h', 'y'};
	char& operator[](char c) { return permutation[c - 'a']; }
	char operator[](char c) const { return permutation[c - 'a']; }
};
int main()
{
	A a;
	std::cout << a['d'] << std::endl; //output 'a'
}
```

### 4.2 Comparison Operator operator<

**Relational** and c**omparison** operators operator<, <=, ==, >= > are used for

comparing two objects

In particular, the operator< is used to **determine the ordering** of a set of objects

```c++
#include <iostream>

class MyClass {
public:
    int value;
    //overload comparison operator
    bool operator<(const MyClass& other) const {
        return value < other.value;
    }
};
int main() {
    MyClass a, b;
    a.value = 1;
    b.value = 2;
    std::cout << std::boolalpha << (a < b) << std::endl;  //output true
    std::cout << std::boolalpha << (b < a) << std::endl;  //output false
    return 0;
}
```

### 4.3 Spaceship Operator operator<=>

==C++20== allows overloading the **spaceship operator** **<=>** for replacing all comparison operators operator<, <=, ==, >= >

```c++
struct A
{
	bool operator==(const A&) const;
	bool operator!=(const A&) const;
	bool operator<(const A&) const;
	bool operator>(const A&) const;
	bool operator<=(const A&) const;
	bool operator>=(const A&) const;
};
//replace by
struct B
{
	int operator<=>(const B&) const;
};
```

==Usage==

```c++
#include <compare>
#include <iostream>
class MyClass {
 public:
	int value;
	// 重载 <=> 运算符
	auto operator<=>(const MyClass& other) const {
		return value <=> other.value;
	}
};
int main() {
	MyClass a, b;
	a.value = 3;
	b.value = 2;
	std::cout << std::boolalpha << (a < b) << std::endl;  // 输出 true
	std::cout << std::boolalpha << (b < a) << std::endl;  // 输出 false
	auto cmp = a <=> b;
	if (cmp == std::strong_ordering::less) {
		std::cout << "a < b" << std::endl;
	} else if (cmp == std::strong_ordering::equal) {
		std::cout << "a == b" << std::endl;
	} else if (cmp == std::strong_ordering::greater) {
		std::cout << "a > b" << std::endl;
	}
	if (a<=>b < nullptr)
		std::cout << "a < b" << std::endl;
	else if (a<=>b == nullptr)
		std::cout << "a == b" << std::endl;
	else if (a<=>b > nullptr)
		std::cout << "a > b" << std::endl;
	return 0;
}
```

The compiler can also generate the code for the *spaceship operator* = default , even for multiple fields and arrays, by using the default comparison **semantic** （语义）of its members

![图片9](.\c++学习笔记src\图片9.png)

The *spaceship operator* can use one of the following ordering:

**strong ordering** • if a is equivalent to b , f(a) is also equivalent to f(b)

​             • exactly one of < , == , or > must be true

​             ○ integral types, e.g. int , char

**weak ordering**  • if a is equivalent to b , f(a) may not be equivalent to f(b)

​             • exactly one of < , == , or > must be true

​             ○ rectangles, e.g. R{2, 5} == R{5, 2}

**partial ordering** • if a is equivalent to b , f(a) may not be equivalent to f(b)

​             • < , == , or > may all be false

​             ○ floating-point float , e.g. NaN

>1. 强序关系（strong ordering）：如果 `a` 和 `b` 相等，那么 `f(a)` 和 `f(b)` 也必须相等，而且只有 `<`、`==` 和 `>` 中的一种可以为真。这种比较方式适用于整型类型，如 `int`、`char` 等。
>2. 弱序关系（weak ordering）：如果 `a` 和 `b` 相等，那么 `f(a)` 和 `f(b)` 不一定相等，而且只有 `<`、`==` 和 `>` 中的一种可以为真。这种比较方式适用于一些矩形类型，例如 `R{2, 5} == R{5, 2}`。
>3. 偏序关系（partial ordering）：如果 `a` 和 `b` 相等，那么 `f(a)` 和 `f(b)` 不一定相等，而且 `<`、`==` 和 `>` 中的任意一种都可能为假。这种比较方式适用于浮点型类型，例如 `float`，其中 NaN（Not a Number）的比较结果是偏序的。

```c++
#include <bits/stdc++.h>
using namespace std;
void test_strong_ordering()
{
	int a = 5, b = 5;
	auto result = a <=> b;

	if (result == std::strong_ordering::less) {
		std::cout << "a < b" << std::endl;
	} else if (result == std::strong_ordering::equal) {
		std::cout << "a == b" << std::endl;
	} else {
		std::cout << "a > b" << std::endl;
	}
}
void test_weak_ordering()
{
	struct Point {
		int x, y;

		auto operator<=>(const Point& other) const {
			if (x == other.x && y == other.y) {
				return std::weak_ordering::equivalent;
			} else if (x < other.x || (x == other.x && y < other.y)) {
				return std::weak_ordering::less;
			} else {
				return std::weak_ordering::greater;
			}
		}
	};
	Point p1{ 1, 2 };
	Point p2{ 1, 3 };
	auto cmp = p1 <=> p2;
	if (cmp == std::weak_ordering::less) {
		std::cout << "p1 < p2" << std::endl;
	} else if (cmp == std::weak_ordering::equivalent) {
		std::cout << "p1 == p2" << std::endl;
	} else {
		std::cout << "p1 > p2" << std::endl;
	}
}
void test_partial_ordering()
{
	struct FloatingPoint {
		double value;
		auto operator<=>(const FloatingPoint& other) const {
			if (std::isnan(value) || std::isnan(other.value)) {
				return std::partial_ordering::unordered;
			} else if (value < other.value) {
				return std::partial_ordering::less;
			} else if (value > other.value) {
				return std::partial_ordering::greater;
			} else {
				return std::partial_ordering::equivalent;
			}
		}
	};
	FloatingPoint a{ nan("") };
	FloatingPoint b{ 2.0 };
	auto cmp = a <=> b;
	if (cmp == std::partial_ordering::less) {
		std::cout << "a < b" << std::endl;
	} else if (cmp == std::partial_ordering::equivalent) {
		std::cout << "a == b" << std::endl;
	} else if (cmp == std::partial_ordering::greater) {
		std::cout << "a > b" << std::endl;
	} else if(cmp == std::partial_ordering::unordered) {
		std::cout << "a and b are unordered" << std::endl;
	}

}
int main()
{
	test_strong_ordering();
	test_weak_ordering();
	test_partial_ordering();
	return 0;
}
```

### 4.4 Function Call Operator operator()

The **function call operator** operator() is generally overloaded to create objects which behave like functions, or for classes that have a primary operation 

```c++
#include <bits/stdc++.h>
#include <numeric>
using namespace std;
struct Multiply
{
	int operator()(int a, int b) const
	{
		return a * b;
	}
};

void test_accumulate()
{
	int array[] = {2, 3, 4};
	int factorial = accumulate(array, array + 3, 1, Multiply());//累乘操作
	cout << factorial << endl;
}
int main()
{
	test_accumulate();
	return 0;
}
```

### 4.5 **Conversion Operator operator T()** 

The **conversion operator** operator T() allows objects to be either implicitly or explicitly (casting) converted to another type

C++11 **Conversion operators** can be marked explicit to prevent implicit conversions. It is a good practice as for class constructors

![图片10](.\c++学习笔记src\图片10.png)

```c++
struct x{
		operator int() {return 0;}
		operator float() {return 3.0f;}
	};
	auto f = []() -> auto {return x();};
	int x = f();
	float y = f();
	cout << x << ' ' << y << endl; // output: x = 0, y = 3.0
```



### 4.6 Increment and Decrement Operators operator++/--

The increment and decrement operators operator++, operator-- are used to **update** the value of a variable by one unit

```c++
struct A
{
	int* ptr;
	int pos;
	A(int* ptr, int pos) : ptr(ptr), pos(pos) {}
	A& operator++()    //return by reference
	{
		++ptr;
		++pos;
		return *this;
	}
	A operator++(int)  //return by value
	{
		A tmp = *this;
		++ptr;
		++pos;
		return tmp;
	}
};
```

### 4.7 **Assignment Operator operator=** 

The **assignment operator** operator= is used to copy values from one object to another *already existing* object

```c++
struct Array
{
	char* array;
	int size;
	Array (int Size, char value) : size(Size)
	{
		array = new char[size];
		fill(array, array + size, value);
	}
	~Array() { delete [] array; }
	Array& operator = (const Array& other); //How to implement?
	
	friend std::ostream& operator<<(std::ostream& os, const Array& a)
	{
		for (int i = 0; i < a.size; i++)
		{
			os << a.array[i] << " ";
		}
		return os;
	}
};
```

==First option==

```c++
Array& operator = (const Array& other)
{
    if(this == &other)
        return *this;
    delete [] array;
    size = other.size;
    array = new char[size];
    copy(other.array, other.array + size, array);
}
```

==Second option(less intuitive)==

```c++
Array& operator= (Array other)
{
    swap(this, &other);
    return *this;
}
friend void swap(Array* first, Array* second)
{
    using std::swap;
    swap(first->size, second->size);
    swap(first->array, second->array);
}
```

• **why using** std::swap ? if swap(x, y) finds a better match, it will use that instead of std::swap

• **why** friend ? it allows the function to be used from outside the structure/class scope

### 4.8 **Stream Operator operator<<**

The **stream operation** operator<< can be overloaded to perform input and output for user-defined types

**The example above**

```c++
friend std::ostream& operator<<(std::ostream& os, const Array& a)
{
    for (int i = 0; i < a.size; i++)
    {
        os << a.array[i] << " ";
    }
    return os;
}
```

### 4.9 **Operators Precedence**

```c++
struct Myint
{
	int x;
	int operator^(int exp)
	{
		int result = 1;
		for (int i = 0; i < exp; i++)
		{
			result *= x;
		}
		return result;
	}
};
void test()
{
	Myint a{3};
	std::cout << (a ^ 2) + 2 << std::endl; //output 11
	int z = a ^ 2 + 2;
	std::cout << z << std::endl;  //output 81
}
```


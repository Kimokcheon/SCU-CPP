# Lecture 3
## Scope
#### 1. What is the scopes of a, b, c and d?
```cpp
int a;
int f ()
{
	static int c;
	int b;
	{int d; }
}
int main ()
{
	f ();
}
```

- a是全局变量，作用域是所有编译单元（包括定义它的文件和所有声明了它的文件）；
- b是函数中的栈变量，作用域只限于函数内部，在函数定义的反括号之后结束作用；
- c是static静态变量，在静态内存区分配内存，在函数内部声明定义,只初始化一次，作用域在函数内，但生命周期直到程序结束；
- d的作用域比函数作用域更小，是只限于函数内部的括号里。

#### 2. What are the scopes of objects of O?

```cpp
struct O
{
	int i;
};
O f(O o)
{
	return o;
}
const O& g(O o)
{
	return std::move(o);
}
O h(const O& o)
{
	return o;
}
```

- `O` as `f` parameter: in function `f`.
- `O` as `f` return value: in the expression including `f`.
- `O` as `g` parameter and `g` return value: in the expression including `g`.
- `O` as `h` parameter and `h` return value: in the expression including `h`.

##	Constructor and destructor
#### 3. Is it necessary to declare destructors（析构函数） as public members? What about constructors（构造函数）?

- 析构函数: 不是. 构造函数: 不是.
- 原因：
  - 如果你不想让外面的用户直接构造一个类（假设这个类的名字为`A`）的对象，而希望用户只能构造这个类`A`的子类，那你就可以将类`A`的构造函数/析构函数声明为`protected`/`private`。
  - 如果将构造函数/析构函数声明为`private`，则类的使用者无法构造和这个类的对象，单件设计模式由此而来：

  ```cpp
  #include <iostream>
  using namespace std;
  
  class A
  {
  private:
      A(): data(10) { cout << "A" << endl; }
      ~A() { cout << "~A" << endl; }
  public:
      static A& Instance()
      {
          static A a;
          return a;
      }
      void Print()
      {
          cout << data << endl;
      }
  private:
      int data;
  };
  int main(int argc, char** argv)
  {
      A& ra = A::Instance();
      ra.Print();
  }
  ```

#### 4. When does copy constructors and move constructors get called?

- Copy constructor is usually called when:
  - New objects are being defined by an existing object of the same class
  - Function parameter or function return value is an object passed by value

- Move constructor is usually called when:
  - New objects are being defined by an rvalue reference(an object that is about to be destroyed)
  - Function parameter or function return value is an rvalue reference(an object that is about to be destroyed)

#### 5. What are the benefits of constructors and destructors? Try to declare a class with constructor and destructor.

- 构造函数和析构函数，一方面是可以为`private`的部分提供初始值，以免无法访问造成不便；另一方面是保证安全性，通过构造函数来强制或者叫做提示使用者该类的初始化数据类型，而不会造成错误的初始化赋值，同时析构函数也可以很好的防止出现memory leak，下面是一个例子：

```cpp
class A
{
	int* x;
	A()
	{
		x = new int;
		*x = 0;
	}
	~A()
	{
		if (x != nullptr) delete x;
	}
}
```

#### 6. Is it possible to call constructor and destructor explicitly? It is necessary?

- It is possible to call constructor and destructor explicitly. For An instance `a1` of a class `A`, we can use `a1.A::A()` to call constructor explicitly, and we can use `a1.A::~A()` to call destructor explicitly.
- It is not necessary to call constructor explicitly. If space is dynamically allocated in the constructor, it is shown that calling constructor explicitly will cause a memory leak.
- It is not necessary to call destructor explicitly. If we call destructor explicitly, it may cause the same memory to be released many times which has potential to cause errors.

#### 7. Specify which constructor will get called for each statement.

- `constructor ();`
- `constructor (int);`

```cpp
constructor a;
constructor b(5);
constructor *c = new constructor;
constructor *d = new constructor (5);
constructor e[5] = {};
constructor f[5] = {(1), (2)};
```

because numbers are default int type:  
a)	`constructor ();`  
b)	`constructor (int);`  
c)	`constructor ();`  
d)	`constructor (int);`  
e)	`constructor ();`  
f)	`constructor (int);` for the first two and `constructor();` for the last three.

#### 8. How to define an object on stack（栈）? What about heap? What will happen if you define oversize object exceed your system's limit?

- To define an object on stack, directly use its type name to define it.
- To define an object on heap, use a pointer and `new` to define it.
- It will cause a stackoverflow error.

Generally, when an object is initialized without the use of `new`/`delete` (like `myObj object(15, “hello”, 5);`), the object is placed on the stack and will be destroyed when its scope ends. If we use `new`/`delete`, (like `myObj* object = new myObj(15, “hello”, 5);`), the object will usually be stored on the heap while the pointer is most likely stored on stack. The user needs to manually free the memory, or it will cause a memory leak.
However, this is dependent on a couple of things, for example whether the `new()` operator for `myObj` is overridden or not. If we exceed the system's limits we might experience stack overflow which can cause the program to crash.

#### 9. What is the difference between the stack and the heap(堆)?

- Stack:
  - Limited size of several kilobytes to megabytes depending on the system and compiler settings.
  - Store local variables in functions.
  - Stack overflow may occur for large array varibles and deep recursive functions.
- Heap:
  - The size of heap is much larger than stack.
  - Heap is used for dynamic memory allocations.

#### 10. Do we need to free memory of stack or heap? How to verify that?

- We do not need to free memory of stack, which will be freed automatically when the end of the object's life scope is met.
- We need to free memory of heap, otherwise the memory of heap will be leaked, increasing the memory burden.
- In C++ language, memory allocated by pointers and the keyword new is memory of heap, otherwise it is memory of stack.

#### 11. Is it necessary to implement the destructor? Explain the reason.

- Not always, because some objects without using heap memories will be automatically freed by the compiler.

#### 12. Does the following code work fine? Explain the reason. How to fix the problem?

```cpp
struct O
{
	int i;
	O (int i) {}
};
int main ()
{
	O* o = new O[5];
}
```

No. It doesn’t define the default constructor. 

To fix this problem, we can:
1. give the constructor a default Argument: `O (int i=0) {};`
2. Or just overload a constructor: `O (){};`

#### 13. How to use constructor initializer list? 

- Have a look at this example below:

```cpp
class A
{
	int num1,num2;
	A(int _num1,int _num2) : num1(_num1), num2(_num2) {}
};
```

#### 14. When do we have to use constructor initializer list?

- For const varibles.
- For reference varibles.
- For class varibles that don't have a default constructor. See below:

  ```cpp
	struct Base
	{
		int num;
		Base(int _num) : num(_num) {}
	};

	class A
	{
		int num;
		Base b;
		A(int k) : num(k), b(k) {}
	};
  ```

##	Explicit
#### 15. Can keyword *explicit* forbid implicit type conversion for multi-parameter constuctor?

  ```cpp
	class Tree
	{
		int height_{0}, weight_{0};
	public:
		explicit Tree(int h, int w) : height_{h}, weight_{w} {}
	};
	void foo(Tree t) {}
	int main() {
		foo({1, 2});
	}
  ```
	
- In C++03, it compiles successfully, without forbidding implicit type conversion for multi-parameter constuctor.
- In C++11 and later version, it cannot compile, showing "error: converting to 'Tree' from initializer list would use explicit constructor 'Tree::Tree(int, int)', which implies keyword *explicit* works.

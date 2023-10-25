# Lecture 5 
##	Inline function(内联函数)
#### 1.	Why do we need C++ grammars such as function-like macros and inline functions? Try to describe a typical situation where the two grammars are used.

- 使用函数型宏和内联函数，一方面是为了节省运行时的时间开销，另一方面是为了能够增加代码的可读性，让许多小的函数能够在声明的地方就完成定义，而不要去其他编译单元中寻找。。

- 简单的加法函数可以写成function like macro，而类中的简单的返回某个值，输出某个值等等这样的函数就可以直接定义为内联。

#### 2. What is problem with the following code?

```cpp
#define IS_UPPER(C) ( (C) >= 'A' && (C) <= 'Z')
while ( IS_UPPER ( s=getchar() ) )
```

- The macro is expanded to `while ((s = getchar()) >= ‘a’ && (s = getchar()) <= ‘Z’))`, which is probably unintended because `getchar()` is called twice.

#### 3. Please give an example showing why brackets “()” are important in avoiding errors in function-like macros（宏函数）.

- if a macro is like `#define f(a) a+a`, when it is called in `a = 2*f(a);`, it would be like `a = 2*a+a`, which is not right.    
  when it is `#define f(a) (a+a)`, it would be `a = 2*(a+a)`, as we would like.

#### 4. Please explain the main advantages of inline functions over function-like macros.

- If macros get function calling as its parameter, the function may be called more than one time.
The inline function is like macro, but it will not cause the above problem.  
inline functions advantages: more efficiency; less error-prone; Support type checking, Support debugging (with symbol table).  
Besides, A macro has no concept of scoping (作用域) required by member functions.  
Inline functions are treated by the compiler almost like preprocessor macros are treated by the preprocessor in that the compiler inputs the function directly to the code before compiling, instead of making a function call which will generate some overhead resource consumption. For small functions, because this overhead can be significant compared to the time the function itself requires to run, inline functions makes the program run faster. The advantage of inline functions over preprocessor macros is that macro functions don’t always work the intended way. An example is the macro function `#define DIVIDEBY10(X) (float)(X/10)`. If we call `DIVIDEBY10(5 + 5)` the macro function will give us `(float)(5 + 5/10)` which is 5.5 instead of the correct answer 1. An inline functions works just like a regular function, so a similar `inline float divideByTen(int number) { return (float)(number/10);}` would still return 1 if the input is 5+5.  
The inline function could eliminated the the problem that macros could access to private class members. Moreover, an inline function is expanded in place like a preprocessor macro so it could maintain the efficiency of program.

#### 5. Is the keyword inline below necessary? Please explain this grammar.

```cpp
class A {
	int x_;
public:
	inline int setX(int x) { x_ = x; }
	inline int getX() { return x_; }
};
```

- 不需要，因为类中直接定义的成员函数会被编译器自动化为内联函数

#### 6. Where is keyword inline supposed to be placed? on declarations or definitions? Please try to explain why.

- The keyword `inline` should be placed on definitions.
- Reason:  
  Inline functions is similar to macros, and the compiler will replace inline functions in the preprocessing procedure. Using `inline` on definitions can make it possible that the compiler directly complete the replacement, while if it is placed on declarations, the compiler does not know what to replace the function.
  
#### 7. Can we add the keyword inline for every function? Please state the rule for setting inline functions (e.g., from google coding style).

- Obviously, we cannot add `inline` for every function, because if the function is too complicated, it would greatly reduce efficiency. The inline functions are actually put inside code when compiling, so overusing inline could make the executable really large. According to google code style, inline functions can be used when:  
  a)	when functions are 10 lines or smaller.  
  b)	without loops and switch statements.  
  c)	note: recursive and virtual functions are normally not inlined.
- In fact, the compiler will sometimes determine by its own whether a function is inlined or not even if you explicitly inline it.

#### 8. Find the relation or similarity between inline and the C++ class grammar?

- Inline function should be defined in everywhere the function is called.  
  Class should be declared everywhere it is used.  
  Inline function as a member of a class can be defined in the class body.

##	Namespace
#### 9. Explain why we need namespace and try to describe some situations where namespaces are needed.

- 名空间用于规定作用域，防止变量重名导致的错误。如全局变量的定义应被放入名空间中，防止污染作用域。

#### 10. Please enumerate all the ways of creating a namespace and referring to the names in the namespace using some examples.

- Creating:
  - `namespace Name {...}`
  - `namespace {...}`
- Using:
  - `using namepace spacename;`
  - `using spacename::membername;`

#### 11. What is the scope (作用域) of “using namespace”? Is it legal to include “using namespace” in header files? Please explain the reason.

- Using namespace's scope is from the '`using`' command to the end of the code block that contains the '`using`' command.
- “`using namespace`” should never appear in header files, because every `.cpp` file including that header file would use the namespace and this raises the chance of name collision greatly.

##	Static
#### 12. Please state in detail the lifetime (生命期) of static variables. How is static related to C++ class?

- lifetime (生命期) of static variables :
  - Allocated once at a fixed address in a special static data area; lives throughout lifetime of the program. static variables/objects and static general functions are local to its translation unit. Can be defined either in header or source files.

- Static members belong to the class:
  - They are shared by all objects of the same class.
  - Can be accessed using either class name or objects.
- Static member functions:
  - Cannot access non-static member variables
  - Cannot call non-static member functions
- Static member variables:
  - Provides a way to create constant member variables for defining static arrays.

#### 13.	Where are static variables stored in the memory?

- 全局变量和静态变量的存储是放在一块的，都放在全局区（静态区），初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。程序结束后由系统释放空间。

#### 14.	Can we access to a static variable (静态变量) defined in another source file directly and how? Please give an example. 

- In principle, no. However, access can be done if the external file contains a global pointer to the static variable.  
	```cpp
	//File a
	static int a;
	```
	```cpp
	//File b
	extern int a;
	```

#### 15.	Please state the concept of internal linkage (内部链接), and list all the different types of variables with the internal linkage.

- Linkage describes how names can or can not refer to the same entity throughout the whole program or one single translation unit. Were the name given internal linkage, such a declaration would denote a distinct entity, although using the same name, but its entity could be referred to by distinct declarations within the same translation unit.
- Static, const, and inline functions are with the internal linkage.

#### 16.	Can we define two static variables with the same name in two different source files?

- YES, static variables/objects and static general functions are local to its translation unit, so that there won’t be name conflict.

#### 17.	What are the differences between static and non-static member functions?

- 出现在类体外的函数定义不能指定关键字`static`；
- 静态成员之间可以相互访问，包括静态成员函数访问静态数据成员和访问静态成员函数；
- 非静态成员函数可以任意地访问静态成员函数和静态数据成员；
- 静态成员函数不能访问非静态成员函数和非静态数据成员；
- 由于没有`this`指针的额外开销，因此静态成员函数与类的全局函数相比速度上会有少许的增长；
- 调用静态成员函数，可以用成员访问操作符(`.`)和(`->`)为一个类的对象或指向类对象的指针调用静态成员函数，当同一类的所有对象使用一个量时，对于这个共用的量，可以用静态数据成员变量，这个变量对于同一类的所有的对象都取相同的值。静态成员变量只能被静态成员函数调用。静态成员函数也是由同一类中的所有对象共用。只能调用静态成员变量和静态成员函数。

#### 18.	Please list all the approaches to access the static member functions (静态成员函数) and static member variables（静态成员变量）, and give examples.

```cpp
class C{ static int a; static int f(); };
```  

They can be accessed either by `C::a` `C::f()` or by `c.a`, `c.f()` or by `c -> a`, `c -> f()`, given that `c` is (//or pointer to) an instance of type `C`.


#### 19.	Please give an example of object counting (对象计数). Please state the necessity of object counting and try to describe a typical situation of using object counting.

```cpp
class Example {
	static int count;
public:
	Example() { count++; }
	~Example() { count--; }

	int getCount() const { return count; }
};
int Example::count = 0;
```

- Typical situation: In a multi-thread program, you may want to limit the total amount of threads. Object counting can help the program check it. And for an instance class, object count is important.

##	Singleton
#### 20. Please give a complete example of the singleton design pattern.

```cpp
	class Singleton{
	private:
		static Singleton *instance;
		Singleton(){}
		Singleton(Singleton &&) = delete;
		Singleton(const Singleton &) = delete;
		Singleton & operator=(Singleton &&) = delete;
		Singleton & operator=(const Singleton &) = delete;
		~Singleton(){}
	public:
		Singleton *getInstance(){
			if(instance == nullptr)
				instance = new Singleton;
			return instance;
		}
	};
```

上面是 Lazy Singleton 的基础实现，但存在如下问题：

- 使用了`new`但没有相应的`delete`，存在内存泄露的问题。要解决这一问题，可以通过嵌套类的方式，在嵌套类内部的析构函数中`delete instance;`。
- 多线程环境下不是线程安全的。要解决这一问题，可以使用双检测锁模式（DCL）

但实际上，`c++11`以后，这两个问题可以通过一种更为优雅的方式解决。这一方法在 *Effective C++* 中被给出：

```cpp
class Singleton {
private:
    Singleton() {}
    ~Singleton() {}
public:
    Singleton(Singleton&&) = delete;
    Singleton(const Singleton&) = delete;
    Singleton &operator=(Singleton&&) = delete;
    Singleton &operator=(const Singleton&) = delete;
    Singleton *getInstance() {
        static Singleton instance;
	return instance;
    }
};
```

说明：由于`static Singleton instance;`只在第一次执行时（第一次调用`getInstance()`）初始化，因此实现了单件，同时保证了内存安全和线程安全。

#### 21. Please explain the necessity of singleton and try to describe some typical situations of using singletons.

- Singleton: 确保一个类只会有一个实例.
- 对于一些占内存比较大的对象常常采用singleton如Windows任务管理器，回收站


# Lecture 4

## Function Overloading(函数重载)

#### 1.	It is necessary to overload functions? Please explain why it is necessary and specify the situation that need to overload functions. What kinds of functions can be overloaded?

- 有必要。
- 在要实现功能相似参数不同的函数时，程序员就不需要选择不同的函数名，这也增强程序的可读性。
- 普通函数和类的成员函数都可以被重载。

#### 2. How the compilers distinguish two functions with the same name?  

- They should either be in different namespaces, or differ in the parameter types so that the compilers give different names to them according to different parameters while compiling.

##	Default Argument
#### 3. Where to put the default arguments （默认参数）on? declarations or definitions?

- Default arguments should be put in function declarations. There’s no need to put default arguments again on definitions, or else the compiler will generate compiling errors.

#### 4. Which arguments of a function can be defaulted with default values? Explain the reason.

- The parameters in the last of parameter list.
- To avoid confusion.

#### 5. Try to add an argument to an existing function with modifying the code as less as possible

添加前：
```cpp
int add(int x,int y)
{
	return  x + y;
}
```
添加后：
```cpp
int add(int x, int y, int z = 0)
{
	return  x + y + z;
}
```


#### 6. Does the following code work fine?

```cpp
struct O
{
	int i;
	O (int i = 0) {}
	O (int i, int j = 0) {}
};
int main ()
{
	O o(6);
}
```

No.  
When `O(6)` is called, there are two options:    
1. `O(int)` is called and the parameter is `6`.  
2. `O(int,int)` is called, the first parameter is `6` and the second is the default value `0`.

Therefore, these codes have two different meanings, so it cannot pass the compilation.  

##	Macro（宏）
#### 7. Give the details of header guarding method and explain why it is necessary.

- The header guarding method:
  - Define the macro when a header is included for the first time, and when it is about to be included for more times, the macro is checked such that all definitions won’t be included twice.

- Why do we need it:  
  - When the header file is included twice, all definitions inside will be defined multiple times, which is unacceptable.

#### 8. Explain why we should avoid using macros to define numbers? Please give the alternative grammars to replace using macros.

- Reasons why we should avoid using macros to define numbers:
  - The types, scopes and accessibilities of macros cannot be controlled.
- We can use `static const` or `enum` instead:
	```cpp
	//Example:
	class abcd
	{
	static const int MAX_NUM = 100;
	//enum{MAX_NUM = 100};
	}
	```

#### 9. In the following example, explain the reason to remove commented line for avoiding compile error and write down the output of the code below.

```cpp
enum smallenum: std::int16_t    {A,  B,  C };
enum color {red,  yellow,   green = 20,    blue};
enum class altitude: char{  high='h',low='l',}; 
enum {d,e,f = e + 2};
int f1 (int a)   {}
int f2 (char a)  {}
int main ()
{
	std::cout << sizeof(smallenum) << " " << A << " " << C << std::endl;
	std::cout << sizeof(red) << std::endl;
	std::cout << sizeof(d) << " " << d << std::endl;
	f1 (d);
	f1 (color::red);
	//f2 (altitude::high);
	f1 (A);
}
```

- c++11 defines a new concept, which makes enumerations both strongly typed and strongly scoped. So `altitude::high` won’t be transferred to “`'h'`”, and thus will cause compile error. A correct statement is like `altitude h = altitude::high`.
- Output: 
  ```plain
  2 0 2
  4
  4 0
  ```  


##	Constants
#### 10. Please explain why we can define a constant variable in the header file without causing compiling errors? What should be done for you to use a constant variable defined in another source file?

- C++中const变量默认为内部链接，即仅在被定义的文件中可见，在每个包含它的编译单元内单独分配内存地址，由于地址不同，链接时也不会发生重定义的错误，通常而言编译器甚至都不会为const变量创建存储空间，而是进行常量折叠，直接将其保存在符号表内，对其进行值替换，而没有存储空间自然也不会发生重定义。
- 在预编译的时候如果在头文件定义了`const`变量，每一个包含该头文件的c文件都会将其展开，而在编译的时候不会报错，因为这符合语法规则，每一个包含这个头文件的`*.c`文件都会编译一次这个变量，分配一个新的地址，然后在链接的时候也不会报错，因为每个同名变量都有自己的地址空间，虽然程序运行不会带来问题，但是如果变量多了，会造成rom的大量浪费。
- To use variables in another source file, we need to use the keyword `extern` as in the following code
	```cpp
	// some function
	extern int c;
	cout << c << endl;
	```

#### 11.	Please explain the difference between the following statements.

```cpp
const int* a = s;
int const* b = s;
int* const c = s;	
```

- 	the address `a` points to could be modified, but the value of the address `a` points to cannot be modified.
- 	same as `a`: `b` can be modified, but `*b` cannot.
- 	the address `c` points to cannot be modified.

#### 12. How to initialize a constant member variable(常量成员变量)?

- Using keyword `static` or constructor initializer list.
	```cpp
	//Example:
	class abcd
	{
	//static const int MAX_NUM = 100; //using keyword static
	const int MAX_NUM;
	abcd(int max_num):MAX_NUM(max_num) {}
	//using initialization list
	}
	```


#### 13. How to convert a constant variable into a non-constant one?

原则上我们可以使用`const_cast`，例如：
```cpp
const int a = 1;  
int &b = const_cast<int&> (a);  
b = 2;
```  
这段代码可以通过编译，但是很有可能运行错误，或者得到无法预计的结果(例如，在上述代码之后再开一个以a为长度的数组试试？除此之外，如果此时打印一下a、b的地址和值，你会发现它们拥有完全相同的地址，然而`a=1,b=2`。）。C++标准规定：Modifying a const object through a non-const access path and referring to a volatile object through a non-volatile glvalue results in undefined behavior。
在设计良好的程序中，通常不应该使用const_cast。

C++标准规定：
> Modifying a const object through a non-const access path and referring to a volatile object through a non-volatile glvalue results in undefined behavior。

在设计良好的程序中，通常不应该使用`const_cast`。

#### 14. Where should the keyword “const” be placed to declare or define a constant member function(常量成员函数)? Please give an example.

- The keyword const should be placed at the end of the declaration.
	```cpp
	//For example:
	void F(int) const;
	void Class::F(int) const {}
	```

#### 15. Please state the restrictions of constant member functions. Can we have any other alternative (i.e., access the members in other ways)?

- Constant member functions cannot modify any variable of the class. Notice that variables of a constant object can only be used by constant functions.

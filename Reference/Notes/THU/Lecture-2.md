# Lecture 2

## Abstraction

#### 1.	Generally speaking, what are the two major parts of a class? Please define a class that describes a computer, and then give an example of how to instantiate an object and access its members.

- The two major parts of a class: member variables (成员变量) and member functions (成员函数). The class Computer is defined and used as follows:
	```cpp
	class Computer
	{
	  public:
		std::string type_;  //member variables
		Computer(const std::string& type) : type_(type) {}    //member functions
	};

	int main()
	{
		Computer A("lenovo");
		string B = A.type_;
		return 0;
	}
	```

#### 2.	Where should we place the class definition (i.e., in the header file or the source file)? Please try to explain why header files are necessary.

- We should place the class definition (`class Foo {};`) in the header file. Here are the reasons:
  - **Class definition** is different from **object definition**. Even if different source files include the same header file with the same class definition, there are no linking errors of multiple class definitions.
  - The definitions of member functions can be included in a source file, which helps hide the implementations details. In this way, we may only provide the header file and the library (compiled from the source files) to the users, without exposing the implementation details.
  - To avoid multiple inclusion of the same header in a source file, we should place an include guard. i.e.
  	```cpp
	#ifndef XXX
	#define XXX
	...
	#endif
	```
    or we can directly use
    ```cpp
    #pragma once
    ...
    ```

#### 3.	Please try to explain why the designers want to organize data and functions into classes? What are the advantages and disadvantages?

- Data and functions are organized into classes because they are easier to deal with as a whole – an object.
- Objects in real world have attributes and behaviors. To model them we need to encapsulate attributes (data) and behaviors (functions).
- Advantages:
  - Easy for dividing the whole program into separate functioning modules.
  - Easy for cooperation of a team and also easy for debugging.
  -	Easy for code reuse. Little modifications are needed for reusing old code. Composition and inheritance are good ways for reuse.
  - Safe for code reuse. When only headers (including class definition with inline member functions) and libraries (including definitions of non-inline member functions) are provided, the client user cannot change the implementations made by the providers.
  -	Safe for memory control, with well-defined constructors and destructors.
- Disadvantages:
  -	Polymorphism (多态) takes more runtime and memory, due to the virtual pointer (vptr) and virtual table (vtable).


## Access control
#### 4.	Please try to use access control （访问控制）to enable information hiding of your class definition of a computer in Problem No.1.

```cpp
class Computer {
public:
	Computer(const std::string& type) : type_(type) {}
	std::string get_type() const { return type_; };
private:
	std::string type_;
};
```

#### 5.	Please try to explain the benefits of access control.

- By access control, the class designer can set the class interfaces as "`public`", and set the implementations as "`private`". The separation between interfaces and implementations makes the class easier to use. On the one hand, the client user does not need to worry about the implementation details. On the other hand, the class designer can easily modify the implentation details without affecting the user program (as the interfaces do not change).

#### 6.	Please tell the differences between keywords public, private and protected. We know that access control works for objects of the class. Does access control work in member functions of this class? I.e., is it possible that one member function cannot access another member?

- Differences：
  - `public`: public members can be accessed anywhere.
  - `private`: private members can only be accessed by members of this class.
  - `protected`: protected members can be accessed by members of this class and its derived class.

- Access control does not work in member functions of this class. No matter what access control the member has, it can always be accessed by the member functions of the same class.

#### 7.	Please try to explain why it is suggested to define a member function（成员函数） outside class definition (i.e., outside the "class XXX {};" block).

- When definitions of member functions are outside the class definitions, especially when they are defined in a separate `.cpp` file instead of the `.h` file, we can compile the implementation in `.cpp` into an object file (`.o`) and then wrap it into a library (`.a` on Linux). In this way, the client users cannot access or modify the implementation.
- If the member function is defined inside class definition, every `.cpp` file that include the header file with the class definition will copy the long definition of functions, which leads to code expansion.
- Besides, member functions defined inside the class definition are regarded as inline functions automatically. It is not be appropriate to inline every member function.

#### 8.	Please explain the differences between keyword struct and class.

- Members of a struct are public by default; members of a class are private by default. When inheriting, struct defaults to public inheritance and class defaults to private inheritance. 
- Class is a new feature in C++. It is recommended to use struct for C-style "plain-old-data" structures (e.g. without any methods), but they do achieve the same functions.

##	Friend
#### 9.	What should you do to permit a non-member function to access private or protected members? What about permitting another class to access them? Please give an example.

- The keyword **`friend`** is required to allow a non-member function to access private member of a class. It is similar if we want to allow another class to access private members of a class.
- For example:
	```cpp
	class B;
	class A
	{
		friend int f(A*);
		friend class B;
	private:
		int x;
	};
	int f(A* p)
	{
		return p->x;
	}
	class B
	{
	public:
		int g(A* p) { return p->x; }
	}
	```

##	Inline
#### 10.	Please define an inline function in Problems No. 1 with keyword **inline**. It is suggested to add a header file.

```cpp
//In header file:
class Computer {
	int computer_size_;
public:
	void set_size(int);
};
```
```cpp
//In source file:
inline void Computer::set_size(int _size) {
	computer_size_ = _size;
}
```

#### 11.	What is the real meaning of inline functions? When and where should we use keyword inline?

- The keyword **`inline`** is an optimizing indicator for the compiler, which indicates that the compiler may optimize the function as an inline function. However, the `inline` indicator is not compulsive (强制的). The compiler may optimize any function without the inline indicator as an inline function, and may treat any inline function as an ordinary function with function call overhead. When a function is treated as inline by the compiler, the function calls will be replaced by the function body of the inline function, so that the function call overhead will be eliminated.
- As a side effect, the inline keyword avoids the ODR (one definition rule). An inline function can be defined in different source files without causing the redefinition error. So the definition of an inline function can be put in the header file. Similarly, **`static`** also avoids the ODR.

- Advantages:
  - Inline functions are better than function-like macros. After compilation, there are no function all overhead for inline functions. Therefore, calls to inline functions are faster than that for ordinary functions.
  - Inline functions support type checking and debugging.
  - Both ordinary and member functions can be set as inline.
- When to use:
  - Simple functions which are used many times.
  - Better without any looping.
  - The address of the function is not used.
  - Because inline funtions simply replace the function call by code, so it is OK if we use inline on some "small" functions in order to accelerate the program. However, abused keyword inline will make the code long and thus make compilation longer. This may also reduce running speed.

#### 12. Please try to explain the implementation of inline functions (内联函数的实现) in compiler, and explain the reason for runtime reduction of inline functions.

- The compiler will copy the code of inline function to where the function is called.

- Reason:
  
  - No function call overhead, and with better safety than function-like macros. Inline functions save runtime because inline can generate less code without the function call, which needs to store local parameters before function call and restore the parameters after return.
  
- However, the [documents of GCC](https://gcc.gnu.org/onlinedocs/gcc/Inline.html) compilers tell that:

  - > You can also direct GCC to try to integrate all “simple enough” functions into their callers with the option `-finline-functions`.
  - > As required by ISO C++, GCC considers member functions defined within the body of a class to be marked inline even if they are not explicitly declared with the `inline` keyword. You can override this with `-fno-default-inline`;
  - > When a function is (1) both inline and static, if (2)all calls to the function are integrated into the caller, and (3)the function’s address is never used, then (==>) the function’s own assembler code is never referenced. 
    >
    > In this case, GCC does not actually output assembler code for the function, unless you specify the option `-fkeep-inline-functions`.
  - > Note that certain usages in a function definition can make it unsuitable for inline substitution. Among these usages are: (1)variadic functions(变参数的函数), use of `alloca`, (2)use of computed `goto`, (3) use of nonlocal `goto`, (4) use of nested functions, (5) use of `setjmp`, (6) use of `__builtin_longjmp` and (7)use of `__builtin_return` or `__builtin_apply_args`. 
    >
    > Using `-Winline` warns when a function marked inline could not be substituted, and gives the reason for the failure.
  
	- > GCC does not inline any functions when **not optimizing** unless you specify the ‘always_inline’ attribute for the function, like this:
    >
    > ```cpp
    > /* Prototype.  */
    > inline void foo (const char) __attribute__((always_inline));
    > ```
  

##	Header guarding
#### 13.	Please give an example of header guarding using preprocessor directives (预编译命令) "#ifndef XXX #define XXX ... #endif", and try to explain the possible compiling errors without them.

```cpp
	/* computer.h */
	#ifndef COMPUTER_H
	#define COMPUTER_H
	class computer {
	private:
	  DeviceManager dm;
	public:
	  inline void boot() { dm.awake_all(); }
	  inline void reboot() { dm.sleep_all(); dm.awake_all(); }
	};
	#endif
```

Without the guard, there will be compiling errors in the following codes.

```cpp
/* main.cpp */
#include "Computer.h"
#include "Bus.h" /* in Bus.h, Computer.h is also included. */
//...
```

The error message should be `'Computer' : 'class' type redefinition`.

This occurs because the declaration of class `Computer` is included twice, and `g++` only allows for one declaration of each class in a source file.

##	This pointer
#### 14. What does **this** pointer mean? How to avoid the name conflicts (名字冲突) between member and non-member variables with this pointer? How to return the current object in member functions?

- "`this`" is a constant pointer that points to the address of the current object. It cannot be changed, and is typically used to identify member variables/functions when name conflicts occur.
- To avoid name conflicts: in a member function, `this -> x` refers to the member variable named `x`.
- To return the current object in a member function: `return * this;`

##	Memory allocation
#### 15.	What are the differences between new/delete and malloc/free?

- `malloc`/`free` are library functions. `new`/`delete` are C++ operators.
- To use `malloc`, we have to manually calculate the memory space needed. `new` automatically calculates the required space.
- `new`/`delete` automatically calls the constructor/destructor. But `malloc`/`free` can't.

#### 16.	Why does C++ bring in new/delete to replace malloc/free?

- Different from `malloc`/`free`, `new`/`delete` calls constructor and destructor automatically. This is an important feature in OOP design, which makes it much easier for memory allocatoin and cleanup.
- `new`/`delete` is smarter when allocating the memory, which automatically calculates the size of the memory. However, `malloc`/`free` has to manually calculate the size of memory, and the returned `void*` pointer needs to be explicitly converted to the required type.
- `new`/`delete` is safer when it calls constructor and destructor automatically. Moreover, `new` will throw an exception when there are not enough memory, which is helpful for enhancing the user experience.
- The **`new`** operator can be overloaded to implement a memory allocating strategy to meet certain requirements. In contrast, `malloc` cannot be overloaded.

##	Incomplete class
#### 17. Please list the situations where we need to use incomplete type, i.e., forward declaration (前向声明). Please give an example.

- When we want to declare a function with a incomplete type as its argument type or return value type.
- When we want to reduce `#include` to save the time of compilation.
- When class `A` have a `B*` pointer and class `B` have an `A*` pointer, we must use forward declaration to avoid the error of referencing header files in loop.
- Example:
    ```cpp
    class B;
    class A {
			B *pb_;
	  	public:
			B *getB() { return pb_; }
		};
		class B {
			A *pa_;
	  	public:
			A *getA() { return pa_; }
		};
    ```

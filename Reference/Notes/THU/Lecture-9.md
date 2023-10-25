# Lecture 9
##	Virtual function (虚函数)
#### 1.	Please give an example to explain polymorphism (多态性).
<code>

	#include <iostream>
	using namespace std;

	enum note { middleC, Csharp, Eflat };
	/**
	 * The base class.
	 * It declared a virtual function.
	 */
	class Instrument {
	public:
	  virtual void play(note) const{ cout<< "Instrument::play" <<endl; }
	};

	/**
	 * The derived class.
	 * It overloaded the virtual function in the base class, so it has polymorphic behaviour.
	 */
	class Wind : public Instrument {
	public:
	  void play(note) const{ cout<< "Wind::play" <<endl; }
	};

	/**
	 * Use reference to display polymorphism.
	 */
	void tune(Instrument &i) {
	  i.play(middleC);
	}

	int main() {
	  Wind flute;
	  tune(flute); // Upcasting
	}
</code>
The output is "Wind::play".

#### 2. Is it necessary to redefine a virtual function in derived class (派生类)? And is the keyword virtual necessary in redefining the virtual function in derived class?

- No. If the base class is virtual, the derived class will automatically becomes virtual, whether it is needed to place the virtual keyword is case-dependent.
- The keyword virtual is not necessary. When one wants the virtual function to be further "modified", he or she should keep the keyword. While on the other hand, if the virtual function is not intended to be extensible, he or she should remove that keyword.

#### 3. What is the meaning of keyword final? What problem will be caused without it? Please give an example showing a typical situation that keyword final is necessary.

- the derived class can't overload the virtual function, and it can avoid a class to be inherited.
- Problem will occur when user overload a function improperly. When we don't want a class or virtual function be inherited or overloaded, we should use final.
- Example: class B inherits from class A, and class C inherits from B. function F() is a virtual function in A and is overridden in B, while it is not expected to be overridden in B's child classes. Then we should use final for function F() in B for better safety.
<code>

	class A {
	public:
	  virtual void F() { cout << "A::F()" << endl; }
	};

	class B : public A {
	public:
	  virtual void F() final { cout << "B::F()" << endl; }
	};

	class C : public B {
	public:
	  //void F() { cout << "C::F()" << endl; }
	  //Cause compile error.
	  //[Error] overriding final function 'virtual void B::F()'
	};
</code>

#### 4. What is the meaning of keyword override? What problem will be caused without it? Please give an example of a typical situation that keyword override is necessary.

- Keyword overide asks the compiler to check whether the function is correctly overided.(which means hide the original function in the base class)
- When we require polymorphism, override is necessary to tell others that we have overridden the virtual function in the base class.
<code>

	class Man {
	public:
	  virtual void speak() { cout << "I am a man." << endl; }
	}

	class Genius {
	public:
	  void speak() override { cout << "I am a genius." << endl; }
	}

	void foo(Man& m) {
	  m.speak();
	}
</code>

##	Late binding (后期绑定)
#### 5. Please explain the difference between early binding and late binding.

- Early binding: binding is performed during compilation before the program runs. General functions use early binging.
- Late binding: binding occurs during runtime, according to the original type of the object. Late binding is enabled by virtual function, by declaring functions as virtual in base class. VPTR makes late binding possible (which is also the reason why a polymorphic class uses more storage than class with same member variables but no virtual funtion).

#### 6. What kind of functions are bond with early binding? And what functions are bond with late binding?

- Non-virtual functions are bond with early binding.
- virtual functions (including normal member functions and destructors) are late bond because of the need of run-time polymorphism. (the behaviour of the class can only be determined during runtime)

#### 7. Does late binding work for objects? How about pointers and references?

- It doesn't work for objects, because one kind of objects have the same VPTR. But it work for pointers and references.

##	VTABLE (虚函数表) and VPTR (虚函数指针)
#### 8. What are VTABLE and VPTR? Where are they stored in?

- VTABLE: a table for each class to store the addresses of virtual functions.
- VPTR: each class with virtual functions and each object of the class contain a pointer pointing to VTABLE.
- VTABLE is usually stored in the memory like global variables, and VPTRs are stored in each object.

#### 9. How do VTABLE and VPTR enable polymorphism?

- For virtual function call (虚函数调用) by base-class pointer, the compiler inserts code to get VPTR and find the function address in VTABLE.
- During compilation (编译期间): the compiler determines the contents of the VTABLE.
- During runtime (运行期间): VTABLE is built in the memory, and VPTR is stored in each object

##	Pure virtual function (纯虚函数) and abstract class (抽象类)
#### 10. Why pure virtual functions (纯虚函数) are necessary in some cases? Please give an example of pure virtual function.

- Some classes serve as APIs and are not implemented (and hence should not be constructed directly). So it is good to declare these classes' member functions "pure" to make the compiler recognize that the class is abstract.
- Here's an example:
<code>

	class FileHandle {
	public:
	  void set_name();
	  virtual void get_data() = 0;	//pure virtual function
	};
</code>

#### 11. What is an abstract class?

- A class with at least one pure virtual function. It can provide a kind of common solutions (interfaces) to some classes. It can make interfaces cleaner and "ask" its derived classes to define these pure virtual functions.

#### 12. Please explain the purpose and advantages of abstract class.

- Purpose:
  - Only provide interfaces for derived classes, prepared for upcasting, program to the interface.
- Advantages:
  - Avoid object slicing: ensure that only pointers and references can be upcasted; provide interfaces for derived classes, prepared for upcasting, program to the interface.
  - Easy for code reuse.Easy for incremental development.


#### 13. Can pure virtual function have function body? What is the purpose to provide a function body for a pure virtual function?

- Yes, it can.
- Providing a function body for pure virtual function can reuse these code, which is good for programming.
- The most common use of pure virtual function body is the pure virtual destructor. By declaring destructor as pure virtual, we can create an abstract class while define most of its behaviour. But at the same time, destructor must have a function body (C++ standard requires). This provide a way to create an abstract class at a relatively low cost.

#### 14. Please give an example where a derived class of an abstract class is still an abstract class.
<code>

	//Example:
	class FileHandle {
	public:
	   void set_name();
	   virtual void get_data() =0;
	   virtual void process() = 0;
	};

	class RemoteFileHandle: public FileHandle {
	public:
	   void get_data();
	   //The derived class didn't overide all the pure virtual functions in the base class.
	   //Thus it is still an abstract class.
	}
</code>

#### 15. Why are virtual functions necessary when using dynamic_cast?

- dynamic_cast needs runtime type checking, and the information needed is stored in the virtual table. Compilers create virtual pointers and virtual tables only for those classes that have virtual functions.

#### 16. Why destructors have to be virtual for Base classes?

- The compiler may mot call the base class destructor if it is not declared virtual. This might cause memory leak.


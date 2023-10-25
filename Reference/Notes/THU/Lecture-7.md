# Lecture 7
##	Composition (组合)
#### 1.	Please explain the concept of composition and try to describe a car using composition with examples. The example is required to include the declaration and definition of constructors and destructor.

- composition就是指将另一个类的实例作为数据成员，组合进该类的内部，分别有公有组合和私有组合两种形式，公有组合可以沿用该实例的接口，而私有组合必须写一些新的接口。

```cpp
/* wheel.h */
class Wheel
{
private:
	int m_radius;
public:
	Wheel(int radius): m_radius(radius) { }
	~Wheel(){};  
};
```
```cpp
/* door.h */
class Door
{
private:
	int m_width, m_height;
public:
	Door(int width, int height) : m_width(width), m_height(height) { }
	~Door(){};  
};
```
```cpp	
/* car.h */
class Car
{
private:
	Wheel wheel;
	Door door;
public:
	Car() : wheel(0), door(0, 0) { }
	~Car(){};  
};
```

#### 2. Please list the different ways (i.e., public, protected, private) of composition and discuss their safety.

- `public`：不安全，能够被所有成员访问
- `protected`：较安全，能够被派生类的成员访问，不能够被其它成员访问
- `private`：安全，只能被class内部的成员访问
- `friend`：有风险，将class内部的私有成员暴露给该函数


#### 3. Please explain the differences between aggregation (聚集) and borrow (借用) in composition with examples.

- 在aggregation中，类的成员类是以实例的情况出现的。这个类拥有这些实例。
- 在borrow中，一个类的成员类只是存储的指针或者引用。这个类不拥有这些实例。

#### 4. Please explain the basic concept and usage of aggregate initialization.

- concept: subobjects are building blocks of the whole object.
- usage: initialized in the constructor initializer list. For instance, `NewClass(...) : Obj(...), ... {}`



#### 5. Please state the order of constructing and destructing member objects.

- In a class composed of more than one member objects.
Member objects are constructed in the same order as how the member objects are declared in the class.
It is NOT affected by the order of member objects in the constructor initializer list.
Member objects are destructed in reverse order of their construction.

#### 6. Please show the usage of constructor initializer list (构造函数初始化列表) in composition with examples.

- In the list, the member variables of the class are initialized. For classes, call its constructors, for common variables, give a value.

```cpp
//Example:
class Class1{
public:
	int x;
	Class1(int _x):x(_x){} //common variable
};
class Class2{
public:
	Class2():c(1){}      //composition
private:
	Class1 c;
};
```

#### 7. We recommend that class members should be initialized by the constructor initializer list (构造函数初始化列表) in the same order as their declaration in the class? Why? And in which order are the members actually initialize (constructors initializer list or their declaration)?

- Because their layout in the memory is the same as the order they are declared.And the member objects are actually initialized in the order as their declaration in the class. Therefore, it will improve the program readability if the constructor initializer list is written in the same order.

##	Inheritance (继承)
#### 8. Please explain the concept of inheritance with examples. It is required that the example include the declaration and definition of constructors and destructor.

- Inheritance is a method for code reuse in C++. Inheritance allows us to make connections between the classes doing similar jobs. Also, inheritances make it more convenient to update a new version.

```cpp
class Base {
	int i;
public:
	Base(int ii) : i(ii) { cout << “constructor Base”; }
	~Base() { cout << “destructor Base”; }
};

class Derived extends Base {
	int i ;
public:
	Derived(int ii) : i(ii), Base(ii) {}
	~Derived() { cout << “destructor Derived”; }
};
```

#### 9. Please explain the differences between public, protected and private inheritance for different access control (public, protected and private) in base class, preferably with a form (表格).

- In the cell of <span style="background-color:#cfc;">light green</span>, OK and NO means whether derived class can access the member in the base class.
- In the cell of <span style="background-color:#3a3;">dark green</span>, it means the access control to the inherited members of base class.
  
<table>
   <tr>
      <td rowspan="2" colspan="2">Inheritance table</td>
      <td colspan="6">Inheritance method</td>
   </tr>
   <tr>
      <td colspan="2">public</td>
      <td colspan="2">private</td>
      <td colspan="2">protected</td>
   </tr>
   <tr>
      <td rowspan="3">Access control in base class</td>
      <td>public</td>
      <td style="background-color:#cfc;">OK</td>
      <td style="background-color:#3a3;">pub</td>
      <td style="background-color:#cfc;">OK</td>
      <td style="background-color:#3a3;">prv</td>
      <td style="background-color:#cfc;">OK</td>
      <td style="background-color:#3a3;">pro</td>
   </tr>
   <tr>
      <td>private</td>
      <td style="background-color:#cfc;">NO</td>
      <td style="background-color:#3a3;">prv</td>
      <td style="background-color:#cfc;">NO</td>
      <td style="background-color:#3a3;">prv</td>
      <td style="background-color:#cfc;">NO</td>
      <td style="background-color:#3a3;">prv</td>
   </tr>
   <tr>
      <td>protected</td>
      <td style="background-color:#cfc;">OK</td>
      <td style="background-color:#3a3;">pro</td>
      <td style="background-color:#cfc;">OK</td>
      <td style="background-color:#3a3;">prv</td>
      <td style="background-color:#cfc;">OK</td>
      <td style="background-color:#3a3;">pro</td>
   </tr>
</table>

#### 10. Please state the order of constructing and destructing the base parts and derived parts for a derived object.

- Constructing: Base parts first, and derived parts next. If a class derived from multiple base classes, follow the order of inheritance.
- Destructing: Derived parts first, and base parts next.

#### 11. When constructing a derived class B from a base class A, which constructor(s) will be called?

- If B has no constructors, the nonparamatric constructor `A()` will be called.
- If B has a constructor, but doesn't call any constructors of A, then the nonparamatric constructor `A()` will be called first, then the constructor of B.
- If B has a constructor and calls a normal (paramatric) constructor `A(...)`, it must be put in the constructor initializer list. This time `A(...)` will be called first, then the constructor of B.

#### 12. Which functions cannot be inherited from the base class (基类)? And please try to explain the reason.

- There are three types of functions that cannot be inherited from the base class, i.e., constructor, destructor, and assignment operator. 
- Because these functions are related to the derived class itself, rather than its features. For example, it is not appropriate to let a derived object assign to its base type by default. These functions are automatically generated by the compiler if they are not defined in the class. 


#### 13. Please explain the differences between public inheritance and private inheritance. What are the typical examples using the different inheritance methods? 


- In public inheritance, the access control of Base class doesn’t change in the Derived class.
- In private inheritance, all members of Base class become privete.
- Public inheritance is used for subtyping. Private inheritance is used for hiding/exposing some interfaces of base class and removing is-a relationship.

```cpp
///Public inheritance: subtyping
class FName2 : public ifstream {
	string fileName;
	bool named;
public:
	FName2() : named(false) {}
	FName2(const string& fname)
		: ifstream(fname.c_str()), fileName(fname) {
		named = true;
}

///Private inheritance: Expose / hide interfaces
class Pet {
public:
	char eat() const { return 'a'; }
	int speak() const { return 2; }
	float sleep() const { return 3.0; }
	float sleep(int) const { return 4.0; }
};
class Goldfish : Pet { // Default private inheritance
public:
	using Pet::eat;   　　// Name publicizes member
	using Pet::sleep; 　  // Exposed both the two members
};
int main() {
	Goldfish bob;
	bob.eat();
	bob.sleep();
	bob.sleep(1);
//! bob.speak();    // Error: private member function
}
```	

#### 14. Please give an example showing how to re-declare a private member function inherited from base class to be public.

```cpp	
//Only if the member is public in the base class.

Class Pet
{
public:
	void eat() {
		cout << “Pet is eating” << endl;
	}
};

class Dog : private Pet
{
public:
	using Pet::eat;
};
```

#### 15. Please explain the basic concept of incremental development (增量式).

- Develop the basic part first, then add new parts to the basic part again and again until the whole program/class is developed, where existing code should be adaptive to future change and extension.

#### 16. Please explain the concept, usage and rules of multiple inheritance（多重继承）.

- concept: A derived class has a number of direct base classes. Used when a derived class has attributes of more than one base class.
- usage: class Derived: public Base1, public Base2 {…}; 
- rules:
  - Public inheritance preserves all the inherited members’ properties.
  - Private inheritance makes all the inherited members private.
  - Protected inheritance makes all the inherited members protected.

#### 17. What is "final" and "override" feature in c++11?

- "Final" can be used to disable inheritance of a class or a function.
- "Override" tells the compiler to check whether a member function in the derived class correctly overrides a virtual class in base class.
 
##	Code reuse
#### 18. Please list the common ways of code reuse, and try to compare between the different ways.

- Cut & Paste: It is common for developers to copy code with which they are familiar and change it to be something new. But it increases the complexcity of the code and is hard to extend.
- Composition: member variables of the new class are objects of existing classes.
- Inheritance: create a new class as a type of the existing class, typically with added members.
- Templates: patterns of classes and functions, with different parameter types.

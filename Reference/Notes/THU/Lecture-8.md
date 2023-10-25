# Lecture 8
##	Name hiding (名字隐藏)
#### 1.	Please give an example illustrating the effect of name hiding.

```cpp
class Base {
public:
	int f() const { cout << "Base::f()\n"; return 1; }
	int f(string) const { return 1; }
	void g() { }
};
class Derived1 : public Base {
public: 
	void g() const { } // hides g() in Base
};
class Derived2 : public Base {
public:
	// Redefinition:
	int f() const { cout << "Derived2::f()\n"; return 2; }
};
```

继承类1(`Derived1`)的`g`函数覆盖了基类(`Base`)的`g`函数，继承类1的对象调用`g`时会调用子类的`g`函数。  
继承类2(`Derived2`)的`f`函数会将基类(`Base`)的两个`f`函数（所有同名函数，不管参数个数和类型还是返回值类型）都覆盖掉，所以调用时如果传入字符串就会出现编译错误。

#### 2. How to overload the member functions of base class without name hiding? Give an example for each method.

- By using forward functions or the using keyword.

```cpp
//1. forward functions
class Base {
public:
    void f();
};
class Derived: public Base {
public:
    void f() { Base::f(); }
    void f() const {…}
};
//2.Using keyword
class Base {
public:
    void f();
};
class Derived: public Base {
public:
    void f() const { … }
    using Base::f;
};
```

#### 3. How to expose some specific member functions of base class? Give an example for each method.

- 使用`using`关键词 `using Base::function()`
- 自定义同名函数转发调用

```cpp
void function()	
{
    Base::function();
}
```

##	Composition vs. inheritance
#### 4. Please think of an example using public composition. Then please try to modify the example and use private composition instead. 

An example using public composition:

```cpp
class Wheel
{
public:
  void Run();
};
class Car
{
public:
  Wheel w[4];
  void Run() {for(int i=0;i<4;i++) w[i].Run();}
};
```

`Wheel::Run()` is accessible from external, so it’s bad code. Using private composition instead:

```cpp
class Wheel
{
public:
  void Run();
};
class Car
{
private:
  Wheel w[4];
public:
  void Run() {for(int i=0;i<4;i++) w[i].Run();}
};
```

#### 5. Please think of an example using public inheritance. Then please try to modify the example and use private inheritance instead. If private inheritance is not feasible for the example, please explain the reason. 

```cpp
Class fruit
{
Public:
  Double water_amount, price_per_kilo;
  Int color;	
}
Class apple: public fruit 
{
  Int type; // hongfushi or guoguang or huangyuanshuai
};
Void set_price(fruit p, double price)
{
  p.price_per_kilo = price;
}
Int main()
{
  Apple a;
a.water_amount = 90; a.color = red; a.type = hongfushi;
  set_price(a, 1.00);
}
```

- 如果改成私有继承的话就会让`water_amount`，`price_per_kilo`, `color`这些变量不可见，对象`a`就不能访问它们，而且`set_price`函数也不能实现`upcasting`.
- 公有继承的特点是基类的公有成员和保护成员作为派生类的成员时，它们都保持原有的状态，而基类的私有成员仍然是私有的，不能被这个派生类的子类所访问；私有继承的特点是基类的公有成员和保护成员都作为派生类的私有成员，并且不能被这个派生类的子类所访问。将公有继承转为私有继承将会带来很大的不便，因为本来公有继承后的派生类是要“面向大众”的，而现在变成私有，全部不能访问。

#### 6. Please explain the connotation of all kinds of composition and inheritance (public, protected, priviate).

- Composition:
  - Public: directly access objects of the inner class. (has-a relationship)
  - Protected/Private: need to define new interfaces to access the inner object. (has-a relationship)
- Inheritance:
  - Public: has all interfaces of the base class. (is-a relationship)
  - Protected: rarely used.
  - Private: almost the same with composition.

##	Upcasting (向上转型)
#### 7. What is the meaning of upcasting? Is it true that upcasting works fine in protected inheritance (保护继承) and private inheritance (私有继承)? Please try to explain why it works or not.

- Upcasting means converting a reference/pointer of the derived class object into a reference/pointer of the base class object. 
- It’s only effective in public inheritance. Because only public inheritance follows is-a relationship.

#### 8. Please explain the reason why it is necessary to define a copy-constructor by upcasting. Please give an example of the copy-constructor with upcasting.

- If not define the copy-constructor by upcasting, default constructor of parent may be called and the value won’t be pass and define in the parent class. That is not what we expect and may cause problem in the project, so that we should write an copy-constructor by upcasting.

```cpp	
class abcd
{
private:
  int x;
public:
  abcd(int _x):x(_x) {}
  abcd(const abcd &a):x(a.x) {}
  void Output() {cout<<x<<endl;}
};
class abcd2: public abcd
{
public:
  abcd2(int _x):abcd(_x) {}
  abcd2(const abcd2 &a):abcd(a) {}
};
int main()
{
  abcd2 a=233;
  abcd b=a;
  b.Output();
}
```

#### 9. What is the meaning of object slicing (对象切割)? Do you think object slicing is good? Why?

- When derived object(not pointer or reference) is casted to base object, the derived object is sliced to subobject corresponding to base class.
- Object slicing is not good. Because some data are lost and there will be data loss which is not safe. So we use upcasting to avoid it.

#### 10. What are the differences between object slicing and upcasting?

- Object slicing is used in real objects, while upcasting is used in pointers or references.
- Object slicing will lose some data, while upcasting only operates on the pointers and will not lose data.
- Object slicing is possibly dangerous (generate incomplete objects), while upcasting is always safe.
- Object slices occurs when compilers do copy constructing (hence slicing the object, only keeping the base members), and upcast occurs when pointers are assigned (and the object is unchanged, the thing that changed is how the compiler sees the block of memory the object is occupying).

# Assignment7

## 1.Question answer

1.why do you think the the constructor and the variables are defined as `protected` and not `private`?

==ans1== ：在面向对象编程中，`public`、`private`和`protected`是用于控制类中成员访问权限的关键字。`private`成员只能在类内部访问，`public`成员可以被任何地方访问，而`protected`成员只能在类内部以及该类的子类中访问。

通常情况下，成员变量应该被定义为`private`，以确保数据的封装性和安全性。但是，本任务我们需要在子类中访问父类的成员变量，这时候就需要将成员变量定义为`protected`。同样，构造函数也应该被定义为`protected`，以确保只有该类的子类可以访问它。这种情况下，子类可以使用父类的构造函数来初始化继承的成员变量。

2.what happens if you define the destructor i.e. `~EspressoBased()` in the protected section?

==ans2==：析构函数应该被定义为`public`，以确保任何对象都可以调用它来销毁该类的对象。如果基类的析构函数被定义为`protected`，派生类拥有的基类析构函数调用权限是`private`，可能会导致内存无法完全释放

## 2.Result

![googletest](.\resource\googletest.png)
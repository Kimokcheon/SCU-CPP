# Assignment 7

高锦梁 2022141450043

## 实践思路

首先按部就班地按照README.md中的内容对于整个assignment做了基本的书写。其中学习到了很多东西：比如书写基类可以直接用.文件写、虚函数需要用虚析构函数析构等等。在实现了一系列内容之后进入到Test部分，该部分主要反馈出三个问题需要我去解决：第一个是为了保证原有class结构的情况下对于内部的函数进行优化和补全，第二个主要是运算符的重载，第三个是将原有的浅拷贝换成深拷贝（为了防止出现两次delete到同一地址）。在这里补充一些，复制构造，拷贝构造的概念（提醒一下我自己）：

1.复制构造函数：用于创建一个新对象，该对象与另一个已经存在的对象具有相同的值。

```C++
class MyClass {
public:
    int x;
    MyClass(int a) { x = a; }
    MyClass(const MyClass& other) { x = other.x; } 
    // 复制构造函数
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = obj1; // 使用复制构造函数创建一个新对象
    cout << obj2.x; // 输出 10
    return 0;
}
```

2.浅拷贝构造函数：是一种创建新对象的方法，其中新对象与原始对象共享相同的数据。这意味着如果更改一个对象的数据，另一个对象的数据也会发生更改。

```c++
class MyClass {
public:
    int* x;
    MyClass(int a) { x = new int(a); }
    MyClass(const MyClass& other) { x = other.x; } 
    // 浅拷贝构造函数
    ~MyClass() { delete x; }
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = obj1; // 使用浅拷贝构造函数创建一个新对象
    *(obj2.x) = 20;
    cout << *(obj1.x); // 输出 20
    return 0;
}
```

3.深拷贝构造函数：是一种创建新对象的方法，其中新对象与原始对象具有相同的数据，但是它们在内存中具有不同的地址。这意味着如果更改一个对象的数据，另一个对象的数据不会发生更改。(特别地，我在作业中是使用一个clone函数来辅助实现深拷贝)

```C++
class MyClass {
public:
    int* x;
    MyClass(int a) { x = new int(a); }
    MyClass(const MyClass& other) { x = new int(*(other.x)); } 
    // 深拷贝构造函数
    ~MyClass() { delete x; }
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = obj1; // 使用深拷贝构造函数创建一个新对象
    *(obj2.x) = 20;
    cout << *(obj1.x); // 输出 10
    return 0;
}
```

## 测试样例成功截图

![Test](.\images\Test.png)

## 两个问题

###### Question 1 : Why do you think the the constructor and the variables are defined as `protected` and not `private`? answer the question in your report after you completed your code.

构造函数和变量被定义为`protected`而不是`private`，是因为`protected`允许派生类访问它们，而`private`则不允许。所以将它们定义为`protected`可以更方便地实现这一点。同时，这也确保了封装性，因为它们仍然无法被类外的代码访问。

###### Question 2 : What happens if you define the destructor i.e. `~EspressoBased()` in the protected section? explain your answer in your report.

如果将析构函数`~EspressoBased()`定义为`protected`，那么这个析构函数将只能被派生类和基类内部的代码调用，而无法在类外部直接访问。因为`protected`成员只能在该类及其派生类内部访问，而不能在类外部访问。如此一来，析构函数的作用是在对象被销毁时释放资源。如果析构函数被定义为`protected`，那么只有该类及其派生类才能释放资源，而外部代码无法释放资源。可能会导致资源泄漏和内存泄漏等问题。所以，在该assignment中析构函数应该被定义为`public`，以便在对象被销毁时能够正确地释放资源。
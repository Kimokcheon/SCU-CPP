#### Submission 3

##### Lecture 10/Adapter/6

The original example codes are as follows.

```
class BST;
class PQ{
private:
    BST a;
public:
    void push(Object o) { a.insert(o); }
    void pop() { a.erase(o); }
    Object top() { return a.getMin(); }
};
```

However, this does not reflect the essence of Adapter, which is to fit the difference of two different classes without changing the original codes. To show the idea, I will give a new example.

```
//Suppose class A want to use the function func() of class B
class A;
class B
{
public:
	void func() {}
};
class Adapter: public A
{
public:
	void func()
	{
		b->func();
	}
private:
	B* b;
};
```

In this way, A.func() is callable.
<center>
<h1>
Assignment6
</h1>
<h3>
Deadline: Tuesday, 4.18
</center>

# Introduction
In this assignment you should implement linked-list data structure with c++.
![](./staff/linkedlist.png)

# LinkedList Class
This class represents each LinkedList. It has the following method and member variables.
```c++
class LinkedList {
public:
    class Node {
    public:
        Node();
        Node(double );
        Node *next;
        Node *previous;
        double getValue();
        void setValue(double);
    private:
        double value;
    };
    LinkedList();
    LinkedList(const LinkedList &);
    ~LinkedList();
    void push_back(double);
    void push_front(double);
    double pop_back();
    double pop_front();
    double back();
    double front();
    bool empty();
    void clear();
    void show();
    int getSize();
    void extend(const LinkedList &);
private:
    int N{0};
public:
    Node *head;
    Node *tail;
};
```
```LinkedList``` class is a nested class and it means that we define class inside another class. ```LinkedList``` class has ```Node``` class. As you can see,  definition of ```Node``` class is inside of ```LinkedList``` class.

DO NOT change main.cpp.


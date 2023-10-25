#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <initializer_list>

class LinkedList {
public:
    class Node {
    friend class LinkedList; // friend class
    public:
        Node();
        Node(double);
        Node *next;
        Node *previous;
        double getValue();
        void setValue(double);
        friend std::ostream& operator <<(std::ostream&, const Node&);
    private:
        double value;
    };
    LinkedList();
    LinkedList(const LinkedList&);
    LinkedList(std::initializer_list<double>);
    ~LinkedList();
    void push_back(double);
    void push_front(double);
    double pop_back();
    double pop_front();
    double back();
    double front();
    bool empty() const;
    void clear();
    void show();
    int getSize() const;
    void extend(const LinkedList&);
    double& operator[](const int&);
private:
    int N{0};
public:
    Node *head;
    Node *tail;
};

#endif
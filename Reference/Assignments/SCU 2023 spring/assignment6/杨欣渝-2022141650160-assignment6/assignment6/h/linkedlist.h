#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
class LinkedList {
public:
    double& operator[](int pos);
    class Node {
    public:
        Node();
        Node(double _value);
        Node *next;
        Node *previous;
        double getValue();
        void setValue(double _value);
        friend std::ostream &operator<<(std::ostream & out, const Node& x);
        friend double& LinkedList:: operator[](int pos);
    private:
        double value;
    };
    LinkedList();
    LinkedList(const LinkedList& Y);
    LinkedList(std::initializer_list<double> a);
    ~LinkedList();
    void push_back(double x);
    void push_front(double x);
    void pop_back();
    void pop_front();
    double back();
    double front();
    bool empty();
    void clear();
    void show();
    int getSize();
    void extend(const LinkedList& Y);
private:
    int N{0};
public:
    Node *head;
    Node *tail;
};
#endif
#pragma once 
#include <iostream>
#include <ostream>
#include <iomanip>
#include <list>
class LinkedList {
public:
    class Node {
    public:
        Node();
        Node(double x);
        Node *next;
        Node *previous;
        double& getValue();
        void setValue(double);
        friend std::ostream & operator <<(std::ostream & out,const Node &s);
    private:
        double value;
    };
    LinkedList();
    LinkedList(const LinkedList &T);
    LinkedList(std::initializer_list<double> values);
    ~LinkedList();
    double& operator[](int index);
    // double operator[](int index);
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
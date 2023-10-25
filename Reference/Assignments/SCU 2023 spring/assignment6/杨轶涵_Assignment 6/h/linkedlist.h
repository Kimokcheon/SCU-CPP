#pragma once
#include <initializer_list>
#include <iostream>

class LinkedList {
public:
    class Node {
    public:
        Node();
        Node(double );
        Node *next;
        Node *previous;
        double getValue() const ;
        double &getRef();
        void setValue(double);
        friend std::ostream& operator << ( std::ostream& o , const Node& );
    private:
        double value;
    };
    LinkedList();
    LinkedList(const LinkedList &);
    LinkedList( const std::initializer_list<double>& );
    ~LinkedList();
    void push_back(double);
    void push_front(double);
    double pop_back();
    double pop_front();
    double back() const;
    double front() const;
    bool empty();
    void clear();
    void show() const ;
    int getSize();
    void extend(const LinkedList &);
    double & operator [] ( int v );
    friend std::ostream& operator << ( std::ostream& o , const LinkedList& F );
private:
    int N{0};
public:
    Node *head;
    Node *tail;
};
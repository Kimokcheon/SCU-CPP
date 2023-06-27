#include<iostream>
#include <initializer_list>
class LinkedList {
public:
    class Node {
    friend class LinkedList;
    public:
        Node();
        Node(double );
        Node *next;
        Node *previous;
        double getValue();
        void setValue(double);
        friend std::ostream& operator<<(std::ostream& out,LinkedList::Node x);
    private:
        double value;
    };
    LinkedList();
    LinkedList(const LinkedList &);
    LinkedList(std::initializer_list<double>);
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
    double& operator[](int);
private:
    int N{0};
public:
    Node *head;
    Node *tail;
};
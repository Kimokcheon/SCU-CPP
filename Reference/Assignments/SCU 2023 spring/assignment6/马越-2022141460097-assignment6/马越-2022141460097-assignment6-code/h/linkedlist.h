#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

class LinkedList {
public:
    class Node {
        friend class LinkedList;
    public:
        Node();
        Node(double);

        Node *next;
        Node *previous;

        double getValue() const;
        void setValue(double);
        friend std::ostream &operator<<(std::ostream &, const Node &);

    private:
        double value;
    };

    LinkedList();
    LinkedList(const std::initializer_list<double>&);
    LinkedList(const LinkedList &);

    ~LinkedList();

    void push_back(double);
    void push_front(double);

    double pop_back();
    double pop_front();

    double back() const;
    double front() const;

    bool empty() const;

    void clear();

    void show() const;

    int getSize() const;

    void extend(const LinkedList &);

    double &operator[](size_t);
    const double &operator[](size_t) const;

private:
    int N{0};

public:
    Node *head;
    Node *tail;
};

#endif //LINKEDLIST_H
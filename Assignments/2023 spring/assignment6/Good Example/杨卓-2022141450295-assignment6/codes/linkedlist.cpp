#include "../h/linkedlist.h"
#include <iomanip>
#include <iostream>
#include <initializer_list>

// Node:
LinkedList::Node::Node() {
    value = 0;
    next = previous = nullptr;
}

LinkedList::Node::Node(double v) {
    this->value = v;
    next = previous = nullptr;
}

double LinkedList::Node::getValue() {
    return this->value;
}

void LinkedList::Node::setValue(double value) {
    this->value = value;
}

std::ostream &operator<<(std::ostream &out, const LinkedList::Node &node) {
    out << node.value;
    return out;
}

// LinkedList
// constructor
LinkedList::LinkedList() {
    N = 0;
    head = tail = new Node;
}

LinkedList::LinkedList(const LinkedList &list) {
    this->N = 0;
    this->head = this->tail = new Node;
    Node *p = list.head;
    while (p != list.tail) {
        this->push_back(p->getValue());
        p = p->next;
    }
}

LinkedList::LinkedList(std::initializer_list<double> list) {
    this->N = 0;
    this->head = this->tail = new Node;
    for (auto value : list) {
        this->push_back(value);
    }
}

// destructor
LinkedList::~LinkedList() {
    Node *p = head, *next;
    while (p != tail) {
        next = p->next;
        delete p;
        p = next;
    }
    delete tail;
}

// push
void LinkedList::push_back(double value) {
    if (this->empty()) {
        head = new Node(value);
        head->next = tail;
        tail->previous = head;
    } else {
        Node *newnode = new Node(value);
        newnode->previous = tail->previous;
        newnode->next = tail;
        tail->previous->next = newnode;
        tail->previous = newnode;
        tail->value = value;
    }
    ++N;
}

void LinkedList::push_front(double value) {
    Node *newnode = new Node(value);
    newnode->next = head;
    head->previous = newnode;
    head = newnode;
    tail->setValue(tail->previous->getValue());
    ++N;
}

// pop
double LinkedList::pop_back() {
    if (this->empty())
        throw std::logic_error("Empty List!");
    Node *back =  tail->previous;
    Node *previous = back->previous;
    double back_value = back->getValue();
    previous->next = tail;
    tail->previous = previous;
    delete back;
    --N;
    if (!this->empty())
        tail->setValue(tail->previous->getValue());
    return back_value;
}

double LinkedList::pop_front() {
    if (this->empty())
        throw std::logic_error("Empty List!");
    double front_value = head->getValue();
    Node *next = head->next;
    delete head;
    head = next;
    --N;
    if (!this->empty())
        tail->setValue(tail->previous->getValue());
    return front_value;
}

// back&front value
double LinkedList::back() {
    if (this->empty())
        throw std::logic_error("Empty List!");
    return tail->previous->getValue();
}

double LinkedList::front() {
    if (this->empty())
        throw std::logic_error("Empty List!");
    return head->getValue();
}

// other information
bool LinkedList::empty() const {
    return head == tail;
}

void LinkedList::clear() {
    if (this->empty()) return;
    Node *p = head, *next;
    while (p != tail) {
        next = p->next;
        delete p;
        p = next;
    }
    head = tail;
    N = 0;
}

void LinkedList::show() {
    Node *p = head;
    while (p != tail) {
        std::cout << p->getValue() << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

int LinkedList::getSize() const {
    return this->N;
}

void LinkedList::extend(const LinkedList &list) {
    if (this->empty()) {
        this->N = 0;
        this->head = this->tail = new Node;
    }
    Node *p = list.head;
    while (p != list.tail) {
        this->push_back(p->getValue());
        p = p->next;
    }
}

double& LinkedList::operator[](const int &idx) {
    if (this->empty())
        throw std::logic_error("Empty List!");
    if (idx < 0 || idx >= N)
        throw std::logic_error("Out of range!");
    int index = 0;
    Node *p = head;
    while (p != tail) {
        if (idx == index) return p->value;
        ++index;
        p = p->next;
    }
    throw std::logic_error("Out of range!");
}
#include "linkedlist.h"
#include <stdexcept>

LinkedList::Node::Node(): value(0), next(nullptr), previous(nullptr) { }

LinkedList::Node::Node(double val): value(val), next(nullptr), previous(nullptr) { }

double LinkedList::Node::getValue() const {
    return value;
}

void LinkedList::Node::setValue(double val) {
    value = val;
}

std::ostream &operator<<(std::ostream &os, const LinkedList::Node &node) {
    os << node.value;
    return os;
}

LinkedList::LinkedList(): head(nullptr), tail(nullptr), N(0) { }

LinkedList::LinkedList(const std::initializer_list<double> &list): head(nullptr), tail(nullptr), N(0) {
    for (auto &val: list)
        push_back(val);
}

LinkedList::LinkedList(const LinkedList &list): head(nullptr), tail(nullptr), N(0) {
    Node *cur = list.head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::push_back(double val) {
    Node *newNode = new Node(val);
    if (N == 0) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    N++;
}

void LinkedList::push_front(double val) {
    Node *newNode = new Node(val);
    if (N == 0) {
        head = newNode;
        tail = newNode;
    } else {
        head->previous = newNode;
        newNode->next = head;
        head = newNode;
    }
    N++;
}

double LinkedList::pop_back() {
    if (N == 0) {
        throw std::logic_error("pop_back(): empty list");
    }
    double val = tail->value;
    Node *newTail = tail->previous;
    delete tail;
    tail = newTail;
    if (tail == nullptr) {
        head = nullptr;
    } else {
        tail->next = nullptr;
    }
    N--;
    return val;
}

double LinkedList::pop_front() {
    if (N == 0) {
        throw std::logic_error("pop_front(): empty list");
    }
    double val = head->value;
    Node *newHead = head->next;
    delete head;
    head = newHead;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->previous = nullptr;
    }
    N--;
    return val;
}

double LinkedList::back() const {
    if (N == 0) {
        throw std::logic_error("back(): empty list");
    }
    return tail->value;
}

double LinkedList::front() const {
    if (N == 0) {
        throw std::logic_error("front(): empty list");
    }
    return head->value;
}

bool LinkedList::empty() const {
    return N == 0;
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node *next = head->next;
        delete head;
        head = next;
    }
    head = tail = nullptr;
    N = 0;
}

void LinkedList::show() const {
    Node *cur = head;
    while (cur != nullptr) {
        std::cout << cur->value << ", ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

int LinkedList::getSize() const {
    return N;
}

void LinkedList::extend(const LinkedList &list) {
    Node *cur = list.head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
}

double &LinkedList::operator[](size_t n) {
    if (n >= N) {
        throw std::logic_error("index out of range");
    }
    Node *cur = head;
    for (int i = 0; i < n; i++) {
        cur = cur->next;
    }
    return cur->value;
}

const double &LinkedList::operator[](size_t n) const {
    if (n >= N) {
        throw std::logic_error("index out of range");
    }
    Node *cur = head;
    for (int i = 0; i < n; i++) {
        cur = cur->next;
    }
    return cur->value;
}


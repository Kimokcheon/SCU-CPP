#include "../h/linkedlist.h"

double& LinkedList::Node::getValue(){
    return this->value;
}

void LinkedList::Node::setValue(double a){
    this->value = a;
}

LinkedList::LinkedList(const LinkedList &preList) {
    Node *a = preList.head;
    if (a == nullptr) {
        head = nullptr;
        tail = nullptr;
        N = 0;
        return;
    }
    head = new Node(a->getValue());
    N++;
    a = a->next;
    Node *n = head;
    while (a != nullptr) {
        N++;
        Node *m = new Node(a->getValue());
        n->next = m;
        m->previous = n;
        n = m;
        a = a->next;
    }
    tail = n;
    tail->next = nullptr;
    N++;
}


LinkedList::~LinkedList() {
    Node *n = this->head;
    Node *last = nullptr;
    while (n != nullptr) {
        last = n;
        n = n->next;
        delete last;
    }
    delete n;
}

void LinkedList::push_back(double x) {
    Node *n = new Node(x);
    if (tail == nullptr) {
        head = n;
        tail = n;
    } else {
        tail->next = n;
        n->previous = tail;
        tail = n;
    }
    N++;
}

void LinkedList::push_front(double x) {
    Node *n = new Node(x);
    if (head == nullptr) {
        head = n;
        tail = n;
    } else {
        n->next = head;
        head->previous = n;
        head = n;
    }
    N++;
}


void LinkedList::pop_back() {
    if(this->empty()){
        throw std::logic_error("");
    }
    if (head == tail) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else {
        Node *n = head;
        while (n->next != tail) {
            n = n->next;
        }
        delete tail;
        tail = n;
        tail->next = nullptr;
    }
    N--;
}


void LinkedList::pop_front() {
    if(this->empty()){
        throw std::logic_error("");
    }
    if (head == tail) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else {
        Node *n = tail;
        while (n->previous != head) {
            n = n->previous;
        }
        delete head;
        head = n;
        head->previous = nullptr;
    }
    N--;
}

double LinkedList::back() const {
    if(this->empty()){
        throw std::logic_error("");
    }
    return tail->getValue();
}

double LinkedList::front() const {
    if(this->empty()){
        throw std::logic_error("");
    }
    return head->getValue();
}

bool LinkedList::empty() const {
    return N == 0;
}

void LinkedList::clear() {
    Node *n = this->head;
    Node *last = nullptr;
    while (n != nullptr) {
        last = n;
        n = n->next;
        delete last;
    }
    head = nullptr;
    tail = nullptr;
    N = 0;
}



void LinkedList::show() const {
    if(this->empty()){
        std::cout << "";
        return;
    }
    Node *n = head;
    while(n != nullptr){
        std::cout << n->getValue() << " ";
        n = n->next;
    }
    delete n;
}

int LinkedList::getSize() const {
    return N;
}

void LinkedList::extend(LinkedList preList) {
    if (preList.empty()) {
        return;
    }
    if (this->empty()) {
        *this = preList;
    } else {
        tail->next = preList.head;
        preList.head->previous = tail;
        tail = preList.tail;
    }
    N += preList.getSize();
    preList.head = nullptr;
    preList.tail = nullptr;
}


double& LinkedList::operator[](int x) const{
    if(x < 0 || x >= this->getSize()){
        throw std::logic_error("");
    }
    Node *n = this->head;
    int i = 0;
    while(i < x){
        n = n->next;
        i++;
    }
    return n->getValue();
}

double LinkedList::operator<<(Node *n){
    return n->getValue();
}








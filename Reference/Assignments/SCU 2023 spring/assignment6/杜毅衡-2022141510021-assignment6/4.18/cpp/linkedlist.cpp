#include <iostream>
#include <list>
#include "../h/linkedlist.h"


//init Node

LinkedList::Node::Node() : next(nullptr), previous(nullptr),value(0) {}
LinkedList::Node::Node(double x) :  next(nullptr), previous(nullptr),value(x) {}

double& LinkedList::Node::getValue(){
    return value;
}
void LinkedList::Node::setValue(double x){
    value=x;
    return ;
}

//output
std::ostream& operator<<(std::ostream& out, const LinkedList::Node& s) {
    out << s.value;
    return out;
}

//init LinkedList 
LinkedList::LinkedList():N(0),head(nullptr),tail(nullptr){}
//the init of LinkedList{x,x,x}
LinkedList::LinkedList(std::initializer_list<double> values) {
    head = tail = nullptr;
    for (auto val : values) {
        push_back(val);
    }
}
//copy
LinkedList::LinkedList(const LinkedList &T){
    if(T.N!=0){
        N=1;
        head = tail = new Node((T.head)->getValue());
        Node* cur = T.head->next;
        while (cur != nullptr) {
            push_back(cur->getValue());
            cur = cur->next;
        }
    }
}
//destructor
LinkedList::~LinkedList(){
    Node* cur = head;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    N = 0;
}
//LinkedList[i],return lvalue
double& LinkedList::operator[](int index) {
    if (index < 0 || index >= N) {
        throw std::logic_error("0");
    }
    Node* cur = head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->getValue();
}

void LinkedList::push_back(double x){
    Node* jt=new Node(x);
    if(empty()){
        ++N;
        head=tail=jt;
        return ;
    }
    else if(N==1){
        ++N;
        tail=jt;
        tail->previous=head;
        head->next=tail;
    }
    else{
        ++N;
        tail->next = jt;
        jt->previous = tail;
        jt->next=nullptr;
        tail = jt;
        return ;
    }
}
void LinkedList::push_front(double x){
    Node* jt=new Node(x);
    if(empty()){
        ++N;
        head=tail=jt;
        return ;
    }
    else if(N==1){
        head=jt;
        head->next=tail;
        tail->previous=head;
    }
    else{
        ++N;
        head->previous = jt;
        jt->next = head;
        jt->previous = nullptr;
        head = jt;
        return ;
    }
}

double LinkedList::pop_back(){
    if(empty()) {   
        throw std::logic_error("0");
        return 0;
    }
    double res=0;
    if(getSize()==1){
        --N;
        res=tail->getValue();
        head=tail=nullptr;
    }
    else{
        --N;
        res=tail->getValue();
        tail=tail->previous;
        tail->next=nullptr;
    }
    return res;
}
double LinkedList::pop_front(){
    if(empty()) {
        throw std::logic_error("0");
        return 0;
    }

    double res=0;
    if(getSize()==1){
        --N;
        res=head->getValue();
        head=tail=nullptr;
    }
    else{
        --N;
        res=head->getValue();
        head=head->next;
        head->previous=nullptr;
    }
    return res;
}

double LinkedList::back() {
    if(empty()) {
        throw std::logic_error("0");
        return 0;
    }
    Node* it;
    it=tail;
    return (*it).getValue();    
}
double LinkedList::front() {
    if(empty()) {
        throw std::logic_error("0");
        return 0;
    }
    Node* it;
    it=head;
    return (*it).getValue();    
}
bool LinkedList::empty() {
    return N==0;
}
void LinkedList::clear(){
    N=0;
    head=tail=nullptr;
    return ;
}
void LinkedList::show(){
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->getValue() << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
    return ;
}
int LinkedList::getSize(){
    return N;
}
void LinkedList::extend(const LinkedList & T){
    if(T.N==0) return ;
    Node* cur=T.head;
    while (cur != nullptr){
        push_back(cur->getValue());
        cur=cur->next;
    }
    return ;
}
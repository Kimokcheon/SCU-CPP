#include "../h/linkedlist.h"
#include <iostream>
#include <iomanip>

LinkedList::Node::Node():next(nullptr),previous(nullptr),value(0){}

void LinkedList::Node::setValue(double val){
    value=val;
}

double LinkedList::Node::getValue(){
    return value;
}

LinkedList::Node::Node(double val){
    next=new Node();
    previous=new Node();
    setValue(val);
}

void LinkedList::push_back(double val){
    Node *now=new Node(val);
    if(head==tail){
        head->value=val;
    }
    now->next=tail->next;
    now->previous=tail;
    tail->next=now;
    tail=now;
    ++N;
}

void LinkedList::push_front(double val){
    Node *now=new Node(val);
    Node *tmp=head->next;
    head->value=val;
    if(tmp==nullptr){
        now->previous=head;
        head->next=now;
        tmp=tail=now;
        ++N;
        return;
    }
    now->previous=tmp->previous;
    now->next=tmp;
    tmp->previous=now;
    ++N;
}

double LinkedList::back(){
    if(tail==head){
        throw std::logic_error("");
    }
    return tail->getValue();
}

double LinkedList::front(){
    if(tail==head){
        throw std::logic_error("");
    }
    return head->next->getValue();
}

double LinkedList::pop_back(){
    double ret=back();
    auto tail_=tail;
    auto now=tail->previous;
    if(now!=nullptr){
        now->next=nullptr;
        tail=now;
    }
    delete tail_;
    --N;
    return ret;
}

double LinkedList::pop_front(){
    double ret=front();
    auto head_=head->next;
    if(head_!=nullptr){
        if(head_->next==nullptr){
            tail=head;
            delete head_;
            return ret;
        }
        head_->next->previous=head;
        head->next=head_->next;
        head->value=head->next->value;
    }
    delete head_;
    --N;
    return ret;
}

bool LinkedList::empty(){
    return !N;
}

void LinkedList::clear(){
    Node *tmp=nullptr;
    for(Node *now=head->next;now!=tail->next;now=now->next){
        if(tmp!=nullptr)
        delete tmp;
        tmp=now;
    }
    delete tmp;
    N=0;
    tail=head;
}

void LinkedList::show(){
    std::cout<<'[';
    for(Node *now=head->next;now!=tail;now=now->next){
        if(now==nullptr){
            std::cout<<" ]"<<std::endl;
            return;
        }
        std::cout<<now->getValue()<<", ";
    }
    std::cout<<tail->getValue()<<']'<<std::endl;
}

int LinkedList::getSize(){
    return N;
}

void LinkedList::extend(const LinkedList & add){
    LinkedList tmp(add);
    if(tmp.head==tmp.tail){
        return;
    }
    tail->next=tmp.head->next;
    tmp.head->next->previous=tail;
    tail=tmp.tail;
    delete tmp.head;
    N+=tmp.N;
}

LinkedList::LinkedList(){
    head=new Node();
    tail=head;
}

LinkedList::LinkedList(const LinkedList & tmp){
    N=tmp.N;
    head=new Node();
    tail=head;
    for(Node *now=tmp.head->next;now!=tail->next;now=now->next){
        push_back(now->getValue());
    }
}

LinkedList::LinkedList(std::initializer_list<double> tmp){
    N=0;
    head=new Node();
    tail=head;
    for(auto it:tmp){
        push_back(it);
    }
}

LinkedList::~LinkedList(){
    clear();
}

double& LinkedList::operator[](int x){
    int cnt=0;
    for(Node* now=head->next;now!=tail->next;now=now->next,++cnt){
        if(cnt==x){
            return now->value;
        }
    }
    throw std::logic_error("Out of range");
}

std::ostream& operator<<(std::ostream& out,LinkedList::Node x){
    out<<x.getValue();
    return out;
}
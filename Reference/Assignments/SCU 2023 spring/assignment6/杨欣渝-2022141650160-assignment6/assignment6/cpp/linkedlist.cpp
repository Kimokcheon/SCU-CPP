#include <bits/stdc++.h>
#include "linkedlist.h"

LinkedList:: Node:: Node():value(0),next(nullptr),previous(nullptr){}
LinkedList:: Node:: Node(double _value):value(_value),next(nullptr),previous(nullptr){} 
//初始化要注意初始化指针
double LinkedList:: Node:: getValue(){ return value; }
void LinkedList:: Node:: setValue(double _value){ value=_value; }
std::ostream &operator<<(std::ostream & out, const LinkedList::Node& x){
    out<<x.value<<' ';
    return out;
}
//重载Node的输出

LinkedList:: LinkedList():head(nullptr),tail(nullptr){}
//同样的，head和tail都要初始化（不然会给你随一个地址 就会有问题）
LinkedList:: LinkedList(std::initializer_list<double> a){
    head=tail=nullptr;
    for(auto x : a) push_back(x);
}
//用initializer_list初始化，和vector差不多，但是不能改变里面的值
LinkedList:: LinkedList(const LinkedList & Y){ 
    head=tail=nullptr;
    auto now=Y.head;
    while(now!=nullptr){
        push_back(now->getValue());
        now=now->next;
    }
}
//复制另一个链表，不能直接等于！
LinkedList:: ~LinkedList(){
    while(head!=nullptr){
        auto nxt=head->next;
        delete head;
        head=nxt;
    }
}
//析构函数需要把自己new出来的空间delete掉

void LinkedList:: push_back(double x){
    if(head==nullptr){
        head=tail=new Node(x);
        N++;
        return;
    }
    tail->next=new Node(x);//new一个节点出来，加入链表最后
    tail->next->previous=tail;
    tail=tail->next;
    N++;
}
void LinkedList:: push_front(double x){
    if(head==nullptr){
        head=tail=new Node(x);
        N++;
        return;
    }
    head->previous=new Node(x);//new一个节点出来，加入链表最前面
    head->previous->next=head;
    head=head->previous;
    N++;
}
void LinkedList:: pop_back(){
    if(tail==nullptr){ throw std::logic_error(""); return; }
    auto now=tail->previous;
    delete tail;//delete 最后的Node
    tail=now;
    if(tail!=nullptr) tail->next=nullptr;
    else head=tail=nullptr;
    N--;
}
void LinkedList:: pop_front(){
    if(head==nullptr){ throw std::logic_error(""); return; }
    auto now=head->next;//delete 最前面的Node
    delete head;
    head=now;
    if(head!=nullptr) head->previous=nullptr;
    else head=tail=nullptr;
    N--;
}
double LinkedList:: back(){
    if(tail==nullptr){ throw std::logic_error(""); return 0; }//记得throw error
    return tail->getValue();
}
double LinkedList:: front(){
    if(head==nullptr){ throw std::logic_error(""); return 0; }
    return head->getValue();
}
bool LinkedList:: empty(){
    if(head==nullptr) return 1;
    return 0;
}
void LinkedList:: clear(){
    while(head!=nullptr){
        auto nxt=head->next;
        delete head;
        head=nxt;
    }
    head=tail=nullptr;
    N=0;
}
void LinkedList:: show(){
    auto now=head;
    while(now!=nullptr){
        std::cout<<now->getValue()<<' ';
        now=now->next;
    }
    std::cout<<std::endl;
}
int LinkedList:: getSize(){
    return N;
}
void LinkedList:: extend(const LinkedList& Y){
    auto now=Y.head;
    if(tail==nullptr&&now!=nullptr){
        head=tail=new Node(now->getValue());
        now=now->next;
    }
    while(now!=nullptr){
        tail->next=new Node(now->getValue());
        tail->next->previous=tail;
        tail=tail->next;
        now=now->next;
    }
}
double& LinkedList:: operator[](int pos){
    auto now=head;
    if(pos>=0){//顺序
        while(pos--){
            if(now==nullptr){ throw std::logic_error(""); }
            now=now->next;
        }
    }
    else{//逆序
        now=tail;
        while((++pos)!=0){
            if(now==nullptr){ throw std::logic_error(""); }
            now=now->previous;
        }
    }
    if(now==nullptr) throw std::logic_error("");
    return (double&)(now->value);//返回一个引用
}

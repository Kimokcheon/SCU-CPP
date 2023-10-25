#include"linkedlist.h"
#include<iostream>
using namespace std;

LinkedList::Node::Node(){value=0;next=previous=nullptr;}

LinkedList::Node::Node(double v){this->value=v;next=previous=nullptr;}

double LinkedList::Node::getValue(){return this->value;}

void LinkedList::Node::setValue(double v){this->value=v;}

LinkedList::LinkedList(){N=0;tail=head=nullptr;}

LinkedList::LinkedList(const LinkedList & A)
{
    this->N=0;this->head=this->tail=nullptr;
    if(A.N)
    {
        Node *p=A.head;
        while(p!=A.tail)
        {
            this->push_back(p->getValue());
            p=p->next;
        }
        this->push_back(A.tail->getValue());
    }
}

LinkedList::LinkedList(std::initializer_list<double> A)
{
    this->N=0;this->head=this->tail=nullptr;
    for(auto X: A) this->push_back(X);
}

LinkedList::~LinkedList()
{
    if(this->head!=nullptr)
    {
        Node *p=this->head;
        while(p!=nullptr&&p!=tail)
        {
            Node *next=p->next;
            if(p!=nullptr)delete p;
            p=next;
        }
        if(tail!=nullptr) delete tail;
    }
}

void LinkedList::push_back(double v)
{
    if(this->empty())
    {
        head=tail=new Node(v);
    }
    else
    {
        Node *X=new Node(v);
        X->previous=tail;X->next=nullptr;
        tail->next=X;
        tail=X;
    }
    N++;
}

void LinkedList::push_front(double v)
{
    if(this->empty())
    {
        head=tail=new Node(v);
    }
    else
    {
        Node *X=new Node(v);
        X->next=head;X->previous=nullptr;
        head->previous=X;
        head=X;
    }
    N++;
}

double LinkedList::pop_back()
{
    if(this->empty())throw std::logic_error("Empty List!");
    double v=this->back();
    tail=tail->previous;
    if(N>1) delete(tail->next),tail->next=nullptr;
    else head=nullptr;
    N--;
    return v;
}

double LinkedList::pop_front()
{
    if(this->empty())throw std::logic_error("Empty List!");
    double v=this->front();
    head=head->next;
    if(N>1) delete(head->previous),head->previous=nullptr;
    else tail=nullptr;
    N--;
    return v;
}

double LinkedList::back()
{
    if(this->empty())throw std::logic_error("Empty List!");
    return tail->getValue();
}

double LinkedList::front()
{
    if(this->empty())throw std::logic_error("Empty List!");
    return head->getValue();
}

bool LinkedList::empty() const{return (!N);}

void LinkedList::clear()
{
    Node *p=this->head;
    while(p!=tail)
    {
        Node *next=p->next;
        delete p;
        p=next;
    }
    delete tail;
    head=tail=nullptr;N=0;
}

void LinkedList::show()
{
    if(this->empty()){cout<<endl;return ;}
    Node *p=this->head;
    while(p!=tail)
    {
        cout<<p->getValue()<<" ";
        p=p->next;
    }
    cout<<tail->getValue()<<endl;
}

int LinkedList::getSize(){return this->N;}

void LinkedList::extend(const LinkedList &A)
{
    if(this->empty())
    {
        this->N=0;
        this->head=this->tail=nullptr;
    }
    if(A.empty()) return ;
    Node *p=A.head;
    while(p!=A.tail)
    {
        Node *next=p->next;
        this->push_back(p->getValue());
        p=next;
    }
    this->push_back(A.tail->getValue());
}

double& LinkedList::operator[](const int &x)
{
    if(this->empty()) throw std::logic_error("Empty List!");
    if(x<0||x>=N) throw std::logic_error("Out of range!");
    int now=0;
    Node *p=head;
    while(p!=tail)
    {
        if(x==now) return p->value;
        ++now;
        p=p->next;
    }
    if(x==now) return p->value;
    throw std::logic_error("Out of range!");
}

ostream &operator<<(ostream &out, const LinkedList::Node &node)
{
    out<<node.value;
    return out;
}
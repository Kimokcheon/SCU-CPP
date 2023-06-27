#include "../h/linkedlist.h"
#include <stdexcept>
#include <iostream>

LinkedList::LinkedList( ) {
    tail = head = new Node();
}

LinkedList::LinkedList( const LinkedList& t ) {
    Node *ahead = t.head;
    head = tail = new Node();
    while( ahead != t.tail ) {
        push_back( ahead -> getValue() );
        ahead = ahead -> next;
    }
    N = t.N;
}

LinkedList::LinkedList( const std::initializer_list<double>& t ) {
    head = tail = new Node();
    for( const auto& v : t ) 
        push_back( v );// , std::cout << v << ' ';
    // std::cout << std::endl;
    N = t.size();
    // std::cout << this -> operator[]( 1 ) << ' ' << this -> head -> getRef() << std::endl;
}

LinkedList::~LinkedList( ) {
    while( head != tail ) {
        head = head -> next;
        delete head -> previous;
    }
    delete head;
}

void LinkedList::push_back( double val ) {
    if( head == tail ) {
        head = new Node();
        head -> setValue( val );
        head -> next = tail , tail -> previous = head;
        return;
    }
    Node *pretail = tail -> previous;
    Node *newnode = new Node( val );
    pretail -> next = newnode;
    tail -> previous = newnode;
    newnode -> previous = pretail;
    newnode -> next = tail;
    ++ N;
}

void LinkedList::push_front( double val ) {
    if( head == tail ) {
        head = new Node();
        head -> setValue( val );
        head -> next = tail , tail -> previous = head;
        return;
    }
    Node *newnode = new Node( val );
    newnode -> next = head;
    head -> previous = newnode;
    head = newnode;
    ++ N;
}

double LinkedList::pop_back( ) {
    if( head == tail ) {
        throw std::logic_error("Pop back on an empty list.");
    }
    double val = tail -> previous -> getValue();
    Node * pretail = tail -> previous;
    if( pretail -> previous != nullptr ) {
        pretail -> previous -> next = tail;
    }
    tail -> previous = pretail -> previous;
    delete pretail;
    -- N;
    return val;
}

double LinkedList::pop_front( ) {
    if( head == tail ) {
        throw std::logic_error("Pop front on an empty list.");
    }
    double val = head -> getValue();
    Node * ahead = head;
    head = head -> next;
    delete ahead;
    -- N;
    return val;
}

double LinkedList::back( ) const {
    if( head == tail ){
        throw std::logic_error("Try to get value in an empty list.");
    }
    return tail -> previous -> getValue();
}

double LinkedList::front( ) const {
    if( head == tail ) {
        throw std::logic_error("Try to get value in an empty list.");
    }
    return head -> getValue();
}

bool LinkedList::empty( ) {
    return head == tail;
}

void LinkedList::clear( ) {
    while( head != tail ) {
        Node *ptr = head;
        head = head -> next;
        delete ptr;
    }
    tail -> previous = nullptr;
    N = 0;
}

void LinkedList::show( ) const {
    for( Node *ptr = head ; ptr != tail ; ptr = ptr -> next ) {
        std::cout << ptr -> getValue() << ' ';
    }
    std::cout << std::endl;
}

int LinkedList::getSize() {
    return N;
}

void LinkedList::extend( const LinkedList& t ) {
    for( Node *ptr = t.head ; ptr != t.head ; ptr = ptr -> next ) {
        push_back( ptr -> getValue() );
    }
    N += t.N;
}

LinkedList::Node::Node( ) : value( 0 ) , next( nullptr ) , previous( nullptr ) {}
LinkedList::Node::Node( double v ) : value( v ) , next( nullptr ) , previous( nullptr ) {}

double LinkedList::Node::getValue( ) const {
    if( this -> next == nullptr ) {
        if( this -> previous == nullptr ) return value;
        return this -> previous -> getValue();
    }
    return value;
}

double &LinkedList::Node::getRef( ) {
    return value;
}

void LinkedList::Node::setValue( double v ) {
    value = v;
}

std::ostream& operator << ( std::ostream& o , const LinkedList& F ) {
    for( LinkedList::Node *ptr = F.head ; ptr != F.tail ; ++ ptr ) {
        o << ptr -> getValue() << ' ';
    }
    o << std::endl;
    return o;
}

std::ostream& operator << ( std::ostream& o , const LinkedList::Node& F ) {
    o << F.getValue() << std::endl;
    return o;
}

double &LinkedList::operator[] ( int v ) {
    if( v < 0 || v >= N ) {
        throw std::logic_error( "Out of range." );
    }
    Node *ahead = head;
    while( v-- ) {
        ahead = ahead -> next;
    }
    return ahead -> getRef();
}
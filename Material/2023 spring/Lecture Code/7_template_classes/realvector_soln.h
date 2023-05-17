#ifndef RealVector_H
#define RealVector_H

#include <string>
#include <algorithm>

template<class valueType> class RealVector {
public:
    //type aliases: this is how the iterator type works! This defines RealVector::iterator
    using iterator = valueType*;
    using const_iterator = const valueType*;

    //initial size for our underlying array
    const size_t kInitialSize = 2;
    //constructors
    RealVector();
    RealVector(size_t n, const valueType& val);
    //destructor
    ~RealVector();

    //interface
    size_t size() const;
    bool empty() const;

    valueType& at(size_t indx);

    void insert(size_t pos, const valueType& elem);
    void push_back(const valueType& elem);

    //don't forget about accessing iterators!
    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    //EXERCISE: add remove!

private:
    void grow();
    //array where we store our elements
    valueType* elems;
    //number of elements in our vector
    size_t logical_size;
    //total capacity of underlying array
    size_t array_size;
};


#include "realvector.cpp"
// #include "realvector.h"

#endif // RealVector_H



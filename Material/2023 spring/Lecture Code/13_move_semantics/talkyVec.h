#ifndef TALKYVEC_H
#define TALKYVEC_H
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#include <string>
#include <algorithm>
#include <iostream>


template <class ValueType>
class TalkyVec {

public:
    using iterator = ValueType*;
    using const_iterator = const ValueType*;
    using size_type = size_t;

    // Default constructor
    TalkyVec();
    // Rule of three:
    //      copy constructor, copy assignment, and destructor
    TalkyVec(const TalkyVec& rhs);
    TalkyVec& operator=(const TalkyVec& rhs);
    ~TalkyVec();

    size_type size() const;
    bool empty() const;

    ValueType& operator[](size_type indx);
    const ValueType& operator[](size_type indx) const ;

    ValueType& at(size_type indx);
    const ValueType& at(size_type indx) const;

    iterator insert(iterator pos, const ValueType& elem);
    void push_back(const ValueType& elem);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    void grow();
    ValueType* elems;
    size_type logicalSize;
    size_type allocatedSize;
    const size_type kInitialSize = 10;
};


template <class ValueType>
TalkyVec<ValueType>::TalkyVec()
{
    std::cout << "DEFAULT CONSTRUCTOR\n" << std::endl;
    allocatedSize = kInitialSize;
    logicalSize = 0;
    elems = new ValueType[allocatedSize];
    std::cout << RED << "Allocated size" << allocatedSize << " array\n" << RESET << std::endl;
}

template <class ValueType>
TalkyVec<ValueType>::TalkyVec(const TalkyVec& rhs) :
    logicalSize(rhs.logicalSize), allocatedSize(rhs.allocatedSize)
{
    std::cout << "COPY CONSTRUCTOR" << std::endl;
    elems = new ValueType[allocatedSize];
    std::cout << RED << "Allocated size" << allocatedSize << " array" << RESET << std::endl;
    std::copy(rhs.begin(), rhs.end(), begin());
    std::cout << BLUE << "Copied size" << allocatedSize << " array.\n" << RESET << std::endl;
}


/*
 * Can't use initialiser list here because this is not
 * a constructor. It also wouldn't make sense since
 * the members in this object should already be initialised
 * if the copy assignment operator is being used.
 */
template <class ValueType>
TalkyVec<ValueType>& TalkyVec<ValueType>::operator=(const TalkyVec& rhs) {
    // Make sure we don't self assign
    std::cout << "COPY ASSIGNMENT" << std::endl;
    if(this != &rhs) {
        std::cout << MAGENTA << "Deallocating size" << allocatedSize << " array." << RESET << std::endl;
        delete[] elems;
        logicalSize = rhs.logicalSize;
        allocatedSize = rhs.allocatedSize;
        std::cout << RED << "Allocated size" << allocatedSize << " array" << RESET << std::endl;
        elems = new ValueType[allocatedSize];
        std::copy(rhs.begin(), rhs.end(), begin());
        std::cout << BLUE << "Copied size" << allocatedSize << " array\n" << RESET << std::endl;
    }
    return *this;
}


template <class ValueType>
TalkyVec<ValueType>::~TalkyVec() {
    std::cout << "DESTRUCTOR" << std::endl;
    std::cout << MAGENTA << "Deallocating size" << allocatedSize << " array\n" << RESET << std::endl;
    delete[] elems;
}

template <class ValueType>
typename TalkyVec<ValueType>::iterator TalkyVec<ValueType>::begin() {
    return elems;
}

template <class ValueType>
typename TalkyVec<ValueType>::const_iterator TalkyVec<ValueType>::begin() const {
    return elems;
}

template <class ValueType>
typename TalkyVec<ValueType>::iterator TalkyVec<ValueType>::end() {
    return elems + size();
}

template <class ValueType>
typename TalkyVec<ValueType>::const_iterator TalkyVec<ValueType>::end() const {
    return elems + size();
}

template <class ValueType>
typename TalkyVec<ValueType>::size_type TalkyVec<ValueType>::size() const {
    return logicalSize;
}

template <class ValueType>
bool TalkyVec<ValueType>::empty() const {
    return size() == 0;
}

template <class ValueType>
ValueType& TalkyVec<ValueType>::at(size_type index) {
    if(index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}

template <class ValueType>
const ValueType& TalkyVec<ValueType>::at(size_type index) const{
    if(index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}


template <class ValueType>
ValueType& TalkyVec<ValueType>::operator[](size_type index) {
    return *(begin() + index);
}

template <class ValueType>
const ValueType& TalkyVec<ValueType>::operator[](size_type index) const {
    return *(begin() + index);
}

template <class ValueType>
void TalkyVec<ValueType>::grow() {
    std::cout << "GROW" << std::endl;
    iterator new_elems = new ValueType[2*allocatedSize];
    std::cout << "Allocating size " <<  2*allocatedSize << " vector." << std::endl;
    std::copy(begin(), end(), new_elems);
    std::cout << "Copying size " << allocatedSize << " vector." << std::endl;
    delete[] elems;
    std::cout << "Deallocating size " <<  allocatedSize << " vector.\n" << std::endl;
    allocatedSize *= 2;
    elems = new_elems;
}

template <class ValueType>
typename TalkyVec<ValueType>::iterator TalkyVec<ValueType>::insert(iterator pos, const ValueType &elem) {
    size_type indx = pos - begin();
    std::cout << "INSERT" << std::endl;
    if(size() == allocatedSize) {
        grow();
    }
    /*
     * If we grew, we need pos to point to the new array
     * since the previous address of pos would be invalid
     */
    pos = begin() + indx;
    std::cout << "Copying size " << allocatedSize << " array.\n" << std::endl;
    std::copy_backward(pos, end(), end() + 1);
    *pos = elem;
    ++logicalSize;
    return pos;
}

template <class ValueType>
void TalkyVec<ValueType>::push_back(const ValueType &elem) {
    std::cout << "PUSH BACK" << std::endl;
    if(logicalSize == allocatedSize){
        grow();
    }
    elems[logicalSize++] = elem;
}



#endif // TALKYVEC_H


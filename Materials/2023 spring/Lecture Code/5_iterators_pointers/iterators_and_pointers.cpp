// system and timing
#include <iostream>
#include <chrono>

// data structure imports
#include <deque>
#include <vector>
#include <iterator>
#include <utility> // pair

using std::cout;    using std::endl;
using std::to_string;

int main() {

    // Pointer initialization and dereferencing
    int x = 5;
    int* pointerToX = &x; // initialized as the address of x.
    cout << "Raw value of pointerToX: " << (void*)pointerToX << endl;
    cout << "Value of x: " << x << ", value of integer pointed to by pointerToX: " << *pointerToX << endl << endl << endl;


    std::vector<int> vec = {1, 2, 3, 6, 11, 23};
    cout << "Values in vector: ";
    // a pre-built, c++ function that can be applied to print out a vector. come to the functions+algo lecture to learn more!
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
    cout << endl;

    // Addresses are numbers! Therefore, for containers that have elements in consecutive addresses,
    // the "++" operator will be equivalent for pointers and iterators.
    int* pointerToVec = &vec[0];
    std::vector<int>::iterator vectorIterator = vec.begin();
    cout << "Raw value of pointerToVec: \t\t\t" << (void *)pointerToVec << endl; 
    cout << "Value of pointerToVec: " << *pointerToVec << ", value of vectorIterator: " << *vectorIterator << endl << endl;
    
    // increment pointer and iterator to next element with ++;
    pointerToVec++;       // adding 1 to the address of vec[0] to get the address of vec[1]
    vectorIterator++;     // idk
    cout << "After increment: Raw value of pointerToVec: \t" << (void *)pointerToVec << endl;
    cout << "After increment: Value of pointerToVec: " << *pointerToVec << ", value of vectorIterator: " << *vectorIterator << endl;
    
 
    // Pointer to element of deque
    std::deque<int> deq;
    for (int i = 0; i < 1000; ++i) {
        deq.push_back(i);
    }
    int* pointerToDeq = &deq[0];
    std::deque<int>::iterator dequeIterator = deq.begin();
    cout << "Raw value of pointerToDeq: \t\t\t" << (void *)pointerToDeq << endl; 
    cout << "Value of pointerToDeq: " << *pointerToDeq << ", value of dequeIterator: " << *dequeIterator << endl << endl;    

    // increment pointer and iterator to next element with ++;
    for (int i = 1; i < 1000; ++i) {
        pointerToDeq++;       // adding 1 to the address of vec[0] to get the address of vec[1]
        dequeIterator++;     // idk
        cout << "After increment: Value of dequeIterator: " << *dequeIterator << ", value of pointerToDeq: " << *pointerToDeq << endl;
    }

    return 0;
}


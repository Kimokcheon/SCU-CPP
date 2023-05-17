// system and timing
#include <iostream>
#include <chrono>

// data structure imports
#include <vector>
#include <deque>
#include <list>

const int NUM_ELEMS = 1000;
using std::cout;    using std::endl;
using std::to_string;

// these are the functions we'll be defining in this file!
// utilities to help us time operations
using timer = std::chrono::high_resolution_clock::time_point;
timer startTimer();
int getElapsedTime(timer start);

// insert to front of sequence container
void timeVectorFrontInsert(std::vector<std::string>& vec);
void timeDequeFrontInsert(std::deque<std::string>& deq);
void timeListFrontInsert(std::list<std::string>& lst);

// insert to back of sequence container
void timeVectorBackInsert(std::vector<std::string>& vec);
void timeDequeBackInsert(std::deque<std::string>& deq);
void timeListBackInsert(std::list<std::string>& lst);

// insert to middle of sequence container
void timeVectorMiddleInsert(std::vector<std::string>& vec);
void timeDequeMiddleInsert(std::deque<std::string>& deq);
void timeListMiddleInsert(std::list<std::string>& lst);

// indexed accessing sequence container
void timeVectorAccess(std::vector<std::string>& vec);
void timeDequeAccess(std::deque<std::string>& vec);

int main() {
    // initialize data structures
    std::vector<std::string> vec;
    std::deque<std::string> deq;
    std::list<std::string> lst;

    /* 
     * Adding elements to front of datastructures
     */ 
    timeVectorFrontInsert(vec);
    timeDequeFrontInsert(deq);
    timeListFrontInsert(lst);

    /* 
     * Adding elements to end of datastructures
     */ 
    timeVectorBackInsert(vec);
    timeDequeBackInsert(deq);
    timeListBackInsert(lst);

    /* 
     * Adding elements to middle of datastructures
     */ 
    timeVectorMiddleInsert(vec);
    timeDequeMiddleInsert(deq);
    timeListMiddleInsert(lst);

    /* 
     * Accessing elements by index in datastructures
     */ 
    timeVectorAccess(vec);
    timeDequeAccess(deq); 
    cout << "Impossible to access lists' elements by index" << endl;

    return 0;
}

// functions used above
// timer utilities
timer startTimer() {
    timer start = std::chrono::high_resolution_clock::now();
    return start;
}

int getElapsedTime(timer start) {
    timer end = std::chrono::high_resolution_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration;
}

// insert to front of sequence containers
void timeVectorFrontInsert(std::vector<std::string>& vec) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        vec.insert(vec.begin(), "element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to front of vector! Time measured: ";
    cout << "\t" << duration << " microseconds" << endl;
}

void timeDequeFrontInsert(std::deque<std::string>& deq) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        deq.push_front("element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to front of deque! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl;
}

void timeListFrontInsert(std::list<std::string>& lst) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        lst.push_front("element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to front of list! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl << endl;
}

// insert to back of sequence containers
void timeVectorBackInsert(std::vector<std::string>& vec) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        vec.push_back("element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to back of vector! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl;
}

void timeDequeBackInsert(std::deque<std::string>& deq) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        deq.push_back("element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to back of deque! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl;
}

void timeListBackInsert(std::list<std::string>& lst) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        lst.push_back("element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to back of list! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl << endl;
}

// insert to middle of sequence containers
void timeVectorMiddleInsert(std::vector<std::string>& vec) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        vec.insert(vec.begin() + NUM_ELEMS, "element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to middle of vector! Time measured: ";
    cout << "\t" << duration << " microseconds" << endl;
}

void timeDequeMiddleInsert(std::deque<std::string>& deq) {
    timer start = startTimer();
    for (int i = 0; i < NUM_ELEMS; ++i) {
        deq.insert(deq.begin() + NUM_ELEMS, "element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to middle of deque! Time measured: ";
    cout << "\t" << duration << " microseconds" << endl;
}

void timeListMiddleInsert(std::list<std::string>& lst) {
    timer start = startTimer();
    // we can't just do lst.begin() + NUM_ELEMS because we can't access list elements by index,
    // so we have to use "std::advance". 
    auto it = lst.begin();
    advance(it, NUM_ELEMS);
    for (int i = 0; i < NUM_ELEMS; ++i) {
        lst.insert(it, "element #" + to_string(i));
    }
    int duration = getElapsedTime(start);
    cout << "Adding " << NUM_ELEMS << " elements to middle of list! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl << endl;
}

// sequentially access elements
void timeVectorAccess(std::vector<std::string>& vec) {
    timer start = startTimer();
    for (std::size_t i = 0; i < vec.size(); ++i) {
        (void)vec[i];
    }
    int duration = getElapsedTime(start);
    cout << "Iterating through " << vec.size() << " elements of vector! Time measured: ";
    cout << "\t" << duration << " microseconds" << endl;
}

void timeDequeAccess(std::deque<std::string>& deq) {
    timer start = startTimer();
    for (std::size_t i = 0; i < deq.size(); ++i) {
        (void)deq[i];
    }
    int duration = getElapsedTime(start);
    cout << "Iterating through " << deq.size() << " elements of deq! Time measured: ";
    cout << "\t\t" << duration << " microseconds" << endl;
}

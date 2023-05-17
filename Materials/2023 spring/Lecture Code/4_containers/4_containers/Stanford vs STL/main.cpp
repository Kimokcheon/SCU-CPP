/*
 * COUT AND STANFORD LIBRARY IMPORTS
 */
#include <iostream>
#include "console.h"
#include "vector.h"
#include "set.h"
#include "map.h"
#include "strlib.h"

/*
 * STL IMPORTS
 */
#include <vector>
#include <sstream>
using std::string;      using std::cout;
using std::endl;        using std::cin;
using std::to_string;

void vectorComparison();
void setComparison();
void mapComparison();

int main() {
    cout << "Which container would you like to compare?" << endl;
    string inp;
    cin >> inp;
    if (inp == "set") {
        setComparison();
    }
    else if (inp == "map") {
        mapComparison();
    }
    else {
        vectorComparison();
    }
    return 0;
}

// you'll learn what this "template" business is and how it allows us to use this function with both
// vectors and sets soon!
template <class stanfordContainer, class stlContainer>
void printContainers(stanfordContainer stanford, stlContainer stl) {
    std::stringstream stanfordSS, stlSS;
    // assuming containers of ints
    std::copy(stanford.begin(), stanford.end(), std::ostream_iterator<int>(stanfordSS, " "));
    std::copy(stl.begin(), stl.end(), std::ostream_iterator<int>(stlSS, " "));
    cout << "Stanford Container's Elements: " << stanfordSS.str() << ", STL container's Elements: " << stlSS.str() << endl;
}

void vectorComparison() {
    ///////////////////////////////////////////////////////////////////
    cout << "1. Create a new, empty vector: " << endl;
    ///////////////////////////////////////////////////////////////////
    Vector<int> stanfordEmpty;
    std::vector<int> stlEmpty;
    printContainers(stanfordEmpty, stlEmpty);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "2. Create a vector with n copies of 0: " << endl;
    ///////////////////////////////////////////////////////////////////
    int n = 5;
    Vector<int> stanfordN(n);
    std::vector<int> stlN(n);
    printContainers(stanfordN, stlN);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "3. Create a vector with n copies of a value k: " << endl;
    ///////////////////////////////////////////////////////////////////
    int k = 10;
    Vector<int> stanford(n, k);
    std::vector<int> stl(n, k);
    printContainers(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "4. Add a value k to the end of a vector: " << endl;
    ///////////////////////////////////////////////////////////////////
    stanford.add(k);
    stl.push_back(k);
    printContainers(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "5. Get the element at index i: " << endl;
    ///////////////////////////////////////////////////////////////////
    int i = 1;
    cout << "Stanford Vector element at index " << to_string(i) << ": " << stanford[i] << endl;

    cout << "STL Vector element at index " << to_string(i) << ": " << stl[i] << endl;

    ///////////////////////////////////////////////////////////////////
    cout << endl << "6. Replace the element at index i: " << endl;
    ///////////////////////////////////////////////////////////////////
    stanford[i] = 11;
    stl[i] = 11;
    printContainers(stanford, stl);


    ///////////////////////////////////////////////////////////////////
    cout << endl << "7. Remove all elements of a vector: " << endl;
    ///////////////////////////////////////////////////////////////////
    stanford.clear();
    stl.clear();
    printContainers(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "8. Check vector's size and if it is empty: " << endl;
    ///////////////////////////////////////////////////////////////////
    cout << "Stanford vector size: " << stanford.size() << "." << endl;
    cout << "STL vector size: " << stl.size() << "." << endl;

    cout << "Stanford vector is empty? " << stanford.isEmpty() << endl;
    cout << "STL vector is empty? " << to_string(stl.empty()) << endl;
}

void setComparison() {
    ///////////////////////////////////////////////////////////////////
    cout << "1. Create a new, empty set: " << endl;
    ///////////////////////////////////////////////////////////////////
    Set<int> stanford;
    std::set<int> stl;
    printContainers(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "2. Add a value k to the set: " << endl;
    ///////////////////////////////////////////////////////////////////
    int k = 12;
    stanford.add(k);
    stl.insert(k);
    printContainers(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "3. Remove the value k from the set: " << endl;
    ///////////////////////////////////////////////////////////////////
    stanford.remove(k);
    stl.erase(k);
    printContainers(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "4. Check if a value k is in the set: " << endl;
    ///////////////////////////////////////////////////////////////////
    cout << "Is " << k << " in the Stanford set? " << stanford.contains(k) << endl;
    cout << "Is " << k << " in the STL set? " << to_string(stl.count(k)) << endl;

    ///////////////////////////////////////////////////////////////////
    cout << endl << "5. Check set's size and if it is empty: " << endl;
    ///////////////////////////////////////////////////////////////////
    cout << "Stanford set size: " << stanford.size() << "." << endl;
    cout << "STL set size: " << stl.size() << "." << endl;

    cout << "Stanford set is empty? " << stanford.isEmpty() << endl;
    cout << "STL set is empty? " << to_string(stl.empty()) << endl;
}

// we can't use the usual printContainers since maps don't just contain integers.
// they contain key-value pairs in a fundamentally different way than vectors/sets of just ints.
void printMaps(Map<char, int> stanford, std::map<char, int> stl) {
    string stanfordS = "";
    for (const char& k: stanford) {
        stanfordS += to_string(k) + ": " + to_string(stanford[k]) + ", ";
    }

    string stlS = "";
    for (const auto &[k, v] : stl) {
        stlS += to_string(k) + ": " + to_string(v) + ", ";
    }

    cout << "Stanford Container's Elements: " << stanfordS << "STL container's Elements: " << stlS << endl;
}

void mapComparison() {
    ///////////////////////////////////////////////////////////////////
    cout << "1. Create a new, empty map: " << endl;
    ///////////////////////////////////////////////////////////////////
    Map<char, int> stanford;
    std::map<char, int> stl;
    printMaps(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "2. Add a keys k with values v to the map: " << endl;
    ///////////////////////////////////////////////////////////////////
    char k1 = 'k', k2 = 'l';
    int v1 = 13, v2 = 14;
    stanford.put(k1, v1);
    stanford[k2] = v2;

    stl.insert({k1, v1});
    stl[k2] = v2;
    printMaps(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "3. Remove key k1 from the map" << endl;
    ///////////////////////////////////////////////////////////////////
    stanford.remove(k1);
    stl.erase(k1);
    printMaps(stanford, stl);

    ///////////////////////////////////////////////////////////////////
    cout << endl << "4. Check if a key k is in the map: " << endl;
    ///////////////////////////////////////////////////////////////////
    cout << "Is " << k1 << " in the Stanford map? " << stanford.containsKey(k1) << endl;
    cout << "Is " << k1 << " in the STL map? " << to_string(stl.count(k1)) << endl;

    ///////////////////////////////////////////////////////////////////
    cout << endl << "5. Check map's size and if it is empty: " << endl;
    ///////////////////////////////////////////////////////////////////
    cout << "Stanford map size: " << stanford.size() << "." << endl;
    cout << "STL map size: " << stl.size() << "." << endl;

    cout << "Stanford map is empty? " << stanford.isEmpty() << endl;
    cout << "STL map is empty? " << to_string(stl.empty()) << endl;
}

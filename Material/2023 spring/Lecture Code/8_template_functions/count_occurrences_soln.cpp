// system and timing
#include <iostream>
#include <chrono>

// data structure imports
#include <deque>
#include <vector>
#include <iterator>
#include <utility> // pair

using std::cout;    using std::endl;

// count_occurrences
template <typename InputIt, typename DataType>
int count_occurrences(InputIt begin, InputIt end, DataType target){
    int count = 0;
    for (auto iter = begin; iter != end; ++iter){
        if (*iter == target) count++;
    }
    return count;
}

int main() {

    // vector of strings
    std::vector<std::string> lands = {"Xadia", "Drakewood", "Innean"};
    cout << count_occurrences(lands.begin(), lands.end(), "Xadia") << endl;
    
    // string itself (array of chars)
    std::string str = "Xadia";
    cout << count_occurrences(str.begin(), str.end(), 'a') << endl;

    return 0;
}


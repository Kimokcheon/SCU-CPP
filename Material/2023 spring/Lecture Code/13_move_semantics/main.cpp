#include "talkyVec.h"
using std::cout; using std::cin;
using std::string; using std::endl;

TalkyVec<int> makeMeAVec(int num){
    TalkyVec<int> res;
    while (num != 0) {
        res.push_back(num%10);
        num /= 10;
    }
    return res;
}

int main(){
    TalkyVec<int> vec;
    vec = makeMeAVec(123);
    cout << "ENDING MAIN\n" << endl;
}
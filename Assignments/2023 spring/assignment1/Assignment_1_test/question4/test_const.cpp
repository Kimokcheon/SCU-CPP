#include <iostream>

using namespace std;
struct A {
#define p "hello"
};

class C {
public:

    static const int NUM = 3; 
    enum con {
        NUM1 = 3
    };
};

#define MAX(a,b) ((a) > (b) ? (a) : (b))
template<typename T>
inline int Max(const T& a, const T& b){
    return (a>b ? a:b);
}
const int C::NUM;   
int main() {
    cout << p << endl; 
    C c;
    cout << &c.NUM << endl;     

    cout << C::NUM1 << endl;

    int a=5, b=0;
    cout<<MAX(++a, b)<<endl;             
    cout<<MAX(++a, b+10)<<endl;           
    a=5,b=0;
    cout<<Max(++a,b)<<endl;
}
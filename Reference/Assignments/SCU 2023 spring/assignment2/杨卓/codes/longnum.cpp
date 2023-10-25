#include "longnum.h"
#include <cstring>
#include <iostream>


namespace Longnum {

Longint::Longint() {
    memset(num, 0, sizeof(num));
    length = 1;
    sign = 1;
}
Longint::Longint(const long long &x) {
    length = 0;
    memset(num, 0, sizeof(num));
    if (x == 0) {
        length = 1;
        sign = 1;
    } else {
        long long t = x;
        if (t < 0) {
            sign = -1;
            t = -t;
        }
        while (t != 0) {
            num[++length] = t%10;
            t /= 10;
        }
    }
}
Longint::Longint(const std::string &s) {
    length = s.length();
    int pos = 0;
    if (s[0] == '-') {
        sign = -1;
        pos = 1;
    }
    for (int i = 0; i < length-pos; ++i) {
        num[i] = s[length-i-1]-'0';
    }
}
int &Longint::operator[](const int &index) {
    return this->num[index];
}
std::ostream &operator<<(std::ostream &os, const Longint &A) {
    for (int i = A.length; i >= 1; --i) {
        os << A.num[i];
    }
    return os;
}
std::istream &operator>>(std::istream &is, Longint &A) {
    std::string s;
    is >> s;
    A = s;
    return is;
}
Longint operator+(const Longint &A, const Longint &B) {

}
Longint operator-(const Longint &A, const Longint &B) {
    
}
Longint operator*(const Longint &A, const Longint &B) {
    
}
std::pair<Longint, long long> operator/(const Longint &A, const long long &B) {
    
}


}
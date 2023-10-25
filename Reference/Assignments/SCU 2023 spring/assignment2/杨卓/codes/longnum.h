#ifndef LONGNUM
#define LONGNUM

#include <cstring>
#include <iostream>

namespace Longnum {


const int MaxN = 1000005;
class Longint {
  private:
    int num[MaxN];
    int length, sign;
  public:
    Longint();
    Longint(const long long &x);
    Longint(const std::string &s);
    int &operator[](const int &index);
    friend std::ostream & operator<<(std::ostream &os, const Longint &A);
    friend std::istream & operator>>(std::istream &is, Longint &A);
    friend Longint operator+(const Longint &A, const Longint &B);
    friend Longint operator-(const Longint &A, const Longint &B);
    friend Longint operator*(const Longint &A, const Longint &B);
    friend std::pair<Longint, long long> operator/(const Longint &A, const Longint &B);

};


}



#endif
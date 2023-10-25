#ifndef CALCULATOR_PROJECT_CALCULATOR
#define CALCULATOR_PROJECT_CALCULATOR

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double ips=1e-9;
const int maxn=1e5;
struct cp{
    double x,y;
    cp(double X,double Y);
};
class number{
    public:
    static int rev[4000006],limit_now;
    explicit number(char s[]="");
    ~number() = default;
    number(const number &A) = default;
    // number(number &&A);
    number &operator=(const number &A) = default;

    void print(ostream& out = cout) const;
    friend ostream &operator<<(ostream &out, const number &A);
    void init(int& L);
    void carry();
    vector<cp> fft(int inv,int L);
    number operator +(const number& y);
    number operator *(const number& y);
    void add(cp c);
    int n,m,flag;
    vector<cp> B;
    private:
};

#endif // CALCULATOR_PROJECT_CALCULATOR
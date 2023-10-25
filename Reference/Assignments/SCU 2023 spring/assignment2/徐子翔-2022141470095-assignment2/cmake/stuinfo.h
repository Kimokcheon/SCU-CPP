#include <bits/stdc++.h>
using namespace std;
struct stuinfo
{
    string name;
    double score[3];
    double ave;
    bool operator < (const stuinfo &others)const {
        return ave>others.ave;
    }
};
void inputstu(stuinfo stu[] , int &n);
void showstu(stuinfo stu[] , int n);
void sortstu(stuinfo stu[] , int n);
bool findstu(stuinfo stu[] , int n, string ch);


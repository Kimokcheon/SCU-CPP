#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<set>
#include<vector>
using namespace std;
vector<int> s;
int main()
{
    for(int i=1;i<=5;i++)
    {
        int x;cin>>x;
        s.push_back(x);
    }
    vector<int>::iterator it=s.begin();
    reverse_iterator it2=s.rbegin();
    for(;it!=s.end();it++) cout<<(*it)<<" ";cout<<endl;
    for(;it2!=s.rend();it2++) cout<<(*it2)<<" ";cout<<endl;
}
    
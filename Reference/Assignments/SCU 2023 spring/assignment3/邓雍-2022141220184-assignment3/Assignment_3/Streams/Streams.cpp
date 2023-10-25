#include<iostream>

using namespace std;
struct
{
    string name;
    int score;
}a[100005];
int main()
{
    freopen("stu.dat","r",stdin);
//    freopen("stu.dat","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) cin>>a[i].name>>a[i].score;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) cout<<a[i].name<<" "<<a[i].score<<endl;
}
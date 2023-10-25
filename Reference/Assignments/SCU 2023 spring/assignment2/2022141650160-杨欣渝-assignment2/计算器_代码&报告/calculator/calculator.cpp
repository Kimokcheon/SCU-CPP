#include "calculator.h"
#include <bits/stdc++.h>
#define pi (3.1415926535)
using namespace std;
char o[10];
int number:: rev[4000006] = {0, };
int number:: limit_now=0;
cp::cp(double X=0,double Y=0){ x=X,y=Y; }
cp operator *(const cp& a,const cp& b){return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
cp operator +(const cp& a,const cp& b){return cp(a.x+b.x,a.y+b.y);}
cp operator -(const cp& a,const cp& b){return cp(a.x-b.x,a.y-b.y);}

number:: number(char s[]):m(0), flag(1), n(0){
    n=strlen(s),m=0;
    int nn=n; n=0;
    if(nn&&s[0]=='-') flag=-1;
    if(flag==-1) while(m<maxn) B.push_back({9,0}),m++,n++;
    bool tag=0; int mm=0;
    for(int i=nn-1;i>=0;i--){
        if(s[i]=='.') tag=1; mm+=(!tag);
        if(s[i]!='.'&&s[i]!='-'){ if(flag==1) B.push_back({s[i]-'0',0}); else B.push_back({'9'-s[i],0}); n++; }
    }
    if(tag) m+=mm;
    if(n&&flag==-1){
        while(n-m<maxn) B.push_back({9,0}),n++;
        int now=1;
        for(int i=0;i<n;i++) now+=B[i].x,B[i].x=now%10,now/=10;
        while(now) B.push_back({now%10,0}),now/=10,n++;
    }
}
void number:: print(ostream &out) const {
    vector<cp> ans=B;
    if(n>maxn)
        if(abs(ans[maxn+maxn-1].x-9)<ips){ out<<'-'; for(int i=0;i<n;i++) ans[i].x=9-ans[i].x; int now=1;
			for(int i=0;i<n;i++) now+=ans[i].x,ans[i].x=now%10,now/=10; while(now) ans.push_back({now%10,0}),now/=10;
        }
    int l=0; while(l<m&&ans[l].x==(double)0) l++;
    int r=min(n-1,maxn+maxn-10); while(r>m&&abs(ans[r].x-0)<ips) r--;
    while(r>=m) out<<(int)(ans[r--].x);
    if(l!=m) out<<'.'; while(r>=l) out<<(int)(ans[r--].x);
}

void number::init(int &L){
    int limit=1;
	while(limit<L) limit<<=1; L=limit;
    if(limit==limit_now) return; limit_now=limit;
	int bit=0; while((1<<bit)<limit) bit++;
	for(int i=0;i<limit;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
}
void number:: add(cp c){ if(B.size()>n) B[++n]=c; else B.push_back(c),n++; }
void number:: carry(){
    long long now=0;
    for(int i=0;i<n;i++){ now+=B[i].x; B[i]={(double)(now%10),0}; now/=10; }
    while(now){ add({(double)(now%10),0}); now/=10; }
}
number number:: operator +(const number& y){
    number ans; ans.m=max(y.m,m);
    int lx=0,ly=0;
    if(y.m>m) while(ly<y.m-m) ans.add(y.B[ly]),ly++;
    if(y.m<m) while(lx<m-y.m) ans.add(B[lx]),lx++;
    while(lx<n&&ly<y.n) ans.add(B[lx]+y.B[ly]),lx++,ly++; while(lx<n) ans.add(B[lx]),lx++; while(ly<y.n) ans.add(y.B[ly]),ly++;
    ans.carry();
    return ans;
}
vector<cp> number:: fft(int inv,int L){
    init(L); vector<cp> a=B;
    while(a.size()<L) a.push_back({0,0});
    for(int i=0;i<L;i++) if(rev[i]>i) swap(a[i],a[rev[i]]);
    for(int mid=1;mid<L;mid<<=1){
		cp tmp(cos(pi/mid),inv*sin(pi/mid));
		for(int i=0;i<L;i+=mid*2){
			cp now(1,0);
			for(int j=0;j<mid;j++,now=now*tmp){ cp x=a[i+j],y=now*a[i+j+mid]; a[i+j]=x+y,a[i+j+mid]=x-y; }
		}
	}
	if(inv==-1) for(int i=0;i<L;i++) a[i].x/=L;
    return a;
}
number number:: operator *(const number& y){
    number ans=*this,b=y; ans.n=n+y.n-1,ans.m=m+y.m; ans.B=ans.fft(1,n+y.n); b.B=b.fft(1,n+y.n);
    for(int i=0;i<limit_now;i++) ans.B[i]=ans.B[i]*b.B[i]; ans.B=ans.fft(-1,limit_now);
    for(int i=0;i<n+y.n;i++) ans.B[i]={(int)(ans.B[i].x+0.5),0}; ans.carry();
    return ans;
}
ostream &operator<<(ostream &out, const number &A){ A.print(out); return out; }

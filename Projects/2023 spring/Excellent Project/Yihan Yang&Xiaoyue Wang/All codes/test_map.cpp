#include "map.h"
#include <iostream>
#include <functional>
using namespace std;

namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
inline int rd() {
  int x = 0, f = 1;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = gc();
  }
  while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
  return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char &c) {
  if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  *pp++ = c;
}
inline void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) push(sta[--top] + '0');
  push( 10 );
}
}

Project::map<pair<int,int>,int> S;

const int inf = 1e8;

int main() {
	freopen("P6136_10.in","r",stdin);
    // freopen( "test.in" , "r" , stdin );
	using namespace IO;
	int n , m;
	n = rd() , m = rd();
	for( int i = 1 ; i <= n ; ++ i ) {
		int x = rd();
        auto it = S.lower_bound( make_pair( x , -inf ) );
        if( it == S.end() || ( it -> first ).first != x )
            S[make_pair( x , 0 )] = 1;
        else 
            S[make_pair( x , it -> first . second - 1 )] = 1;
	}
	int last = 0 , res = 0;
	for( int i = 1 ; i <= m ; ++ i ) {
		static int op , x;
		op = rd() , x = rd();
        // for( auto it : S ) std::cout << ( it.first ).first << ' ';
        // puts("");
		x ^= last;
        if( op == 1 ) {
	        auto it = S.lower_bound( make_pair( x , -inf ) );
	        if( it == S.end() || ( it -> first ).first != x )
	            S.insert( make_pair( make_pair( x , 0 ) , 1 ) );
	        else 
	            S.insert( make_pair( make_pair( x , it -> first . second - 1 ) , 1 ) );
        } else if( op == 2 ) {
            auto it = S.lower_bound( make_pair( x , -inf ) );
            if( it != S.end() && ( it -> first ).first == x )
                S.erase( it );
        } else if( op == 3 ) {
            auto it = S.lower_bound( make_pair( x , -inf ) );
            last = it - S.begin() + 1;
        } else if( op == 4 ) {
            auto it = ( x - 1 ) + S.begin();
            last = ( it -> first ).first;
        } else if( op == 5 ) {
            auto it = S.lower_bound( make_pair( x , -inf ) );
            -- it;
            last = ( it -> first ).first;
        } else {
            auto it = S.upper_bound( make_pair( x , 0 ) );
            last = ( it -> first ).first;
        }
        // std::cout << last << std::endl;
        if( op > 2 ) res ^= last;
	}
	printf("%d\n",res);
}
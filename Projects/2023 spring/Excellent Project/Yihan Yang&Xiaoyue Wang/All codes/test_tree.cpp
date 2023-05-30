#include "_SB_tree.h"
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

_Sb_tree::_Sb_tree<std::pair<int,int>,std::pair<int,int>,std::_Identity<std::pair<int,int>>,std::less<pair<int,int>>> S;

const int inf = 1e8;

int main() {
	freopen("P6136_10.in","r",stdin);
	using namespace IO;
	int n , m;
	n = rd() , m = rd();
	for( int i = 1 ; i <= n ; ++ i ) {
		int x = rd();
        auto it = S.lower_bound( make_pair( x , -inf ) );
        if( it == S.end() || it -> first != x )
            S._M_insert_unique( make_pair( x , 0 ) );
        else 
            S._M_insert_unique( make_pair( x , it -> second - 1 ) );
	}
	int last = 0 , res = 0;
	for( int i = 1 ; i <= m ; ++ i ) {
		static int op , x;
		op = rd() , x = rd();
		x ^= last;
        if( op == 1 ) {
	        auto it = S.lower_bound( make_pair( x , -inf ) );
	        if( it == S.end() || it -> first != x )
	            S._M_insert_unique( make_pair( x , 0 ) );
	        else 
	            S._M_insert_unique( make_pair( x , it -> second - 1 ) );
        } else if( op == 2 ) {
            auto it = S.lower_bound( make_pair( x , -inf ) );
            if( it != S.end() && it -> first == x )
                S.erase( it );
        } else if( op == 3 ) {
            auto it = S.lower_bound( make_pair( x , -inf ) );
            last = S.get_pos( it ) + 1;
        } else if( op == 4 ) {
            auto it = ( x - 1 ) + S.begin();
            last = it -> first;
        } else if( op == 5 ) {
            auto it = S.lower_bound( make_pair( x , -inf ) );
            -- it;
            last = it -> first;
        } else {
            auto it = S.upper_bound( make_pair( x , 0 ) );
            last = it -> first;
        }
        if( op > 2 ) res ^= last;
	}
	printf("%d\n",res);
}
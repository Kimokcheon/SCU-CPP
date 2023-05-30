#include "map.h"
#include <iostream>
const int MAXN = 2e5 + 10;
typedef long long ll;
int n , c;
int A[MAXN];

// int main() {
    
//     // _Sb_tree::_Sb_tree<int,std::pair<int,int>,std::_Select1st<std::pair<int,int>>,std::less<int>> S;
//     // std::cin >> n >> c;
//     // for( int i = 1 ; i <= n ; ++ i ) {
//     //     scanf("%d",A + i);
//     //     if( S.count( A[i] ) ) {
//     //         auto it = S.find( A[i] );
//     //         int cn = it -> second;
//     //         S.erase( it );
//     //         S._M_insert_unique( std::make_pair( A[i] , cn + 1 ) );
//     //     }
//     //     else S._M_insert_unique( std::make_pair( A[i] , 1 ) );
//     //     A[i] -= c;
//     // }
//     // ll res = 0;
//     // for( int i = 1 ; i <= n ; ++ i ) {
//     //     auto it = S.find( A[i] );
//     //     if( it != S.end() ) 
//     //         res += it -> second;
//     // }
//     // std::cout << res << std::endl;
// }
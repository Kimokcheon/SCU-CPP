//RandomGenerator.cpp
#include <RandomGenerator.hpp>
#include <bits/stdc++.h>
using namespace std;
namespace random_generator{
    
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int* Generate(int n){
    int* A = new int[n];
    for(int i=0; i<n; i++) A[i] = rng() % n;
    return A;
}
void print(int* A, int n){
    if(A == nullptr) return;
    int maxn = A[0], minn = A[0];
    for(int i=1; i<n; i++)
        maxn = max(maxn, A[i]), minn = min(minn, A[i]); 
    cout<< minn << ' ' << maxn << endl;
}
void Del(int* A){
    delete []A;
}

}
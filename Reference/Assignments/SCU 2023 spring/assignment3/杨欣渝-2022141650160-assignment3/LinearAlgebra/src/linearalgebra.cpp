#include "linearalgebra.h"
#include<bits/stdc++.h>
using namespace std;
algebra::Matrix algebra::zeros(size_t n,size_t m){
    algebra::Matrix mat(n);
    for(int i=0;i<n;i++) mat[i]=vector<double>(m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=0;
    return mat;
}
algebra::Matrix algebra::ones(size_t n,size_t m){
    algebra::Matrix mat(n);
    for(int i=0;i<n;i++) mat[i]=vector<double>(m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=1;
    return mat;
}
algebra::Matrix algebra::random(size_t n,size_t m,double minn,double maxx){
    if(minn>maxx) throw logic_error("The function of random has error!");
    default_random_engine rg; rg.seed(random_device()()); uniform_real_distribution<double> dist(minn, maxx);
    algebra::Matrix mat(n);
    for(int i=0;i<n;i++) mat[i]=vector<double>(m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=dist(rg);
    return mat;
}
void algebra::show(const algebra:: Matrix& matrix){
    int n=matrix.size(),m=matrix[0].size();
    cout<<fixed<<setprecision(3);
    for(int i=0;i<n;i++){ for(int j=0;j<m;j++) cout<<matrix[i][j]<<' '; cout<<endl; }
}
algebra::Matrix algebra::multiply(const algebra::Matrix& matrix,double c) {
    if(matrix.size()==0) return matrix;
    int n=matrix.size(),m=matrix[0].size(); Matrix mat=zeros(n,m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=matrix[i][j]*c;
    return mat;
}
algebra::Matrix algebra::multiply(const algebra::Matrix& matrix1,const algebra::Matrix& matrix2) {
    if(matrix1.size()==0) return matrix1;
    if(matrix2.size()==0) return matrix2;
    int n=matrix1.size(),m=matrix2[0].size(),l=matrix1[0].size();
    if(matrix2.size()!=l) throw logic_error("The function of multipy has error!");
    Matrix mat=zeros(n,m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) for(int k=0;k<l;k++) mat[i][j]+=matrix1[i][k]*matrix2[k][j];
    return mat;
}
algebra::Matrix algebra::sum(const algebra::Matrix& matrix,double c) {
    if(matrix.size()==0) return matrix;
    int n=matrix.size(),m=matrix[0].size();
    algebra::Matrix mat=zeros(n,m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=matrix[i][j]+c;
    return mat;
}
algebra::Matrix algebra::sum(const algebra::Matrix& matrix1,const algebra::Matrix& matrix2){
    if(matrix1.size()==0&&matrix2.size()==0) return {};
    if(matrix1.size()!=matrix2.size()) throw logic_error("The function of sum has error!");
    if(matrix1[0].size()!=matrix2[0].size()) throw logic_error("The function of sum has error!");
    int n=matrix1.size(),m=matrix1[0].size();
    algebra::Matrix mat=zeros(n, m);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=matrix1[i][j]+matrix2[i][j];
    return mat;
}
algebra::Matrix algebra::transpose(const algebra::Matrix& matrix) {
    if(matrix.size()==0) return {};
    int n=matrix.size(),m=matrix[0].size();
    algebra::Matrix mat=zeros(m,n);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[j][i]=matrix[i][j];
    return mat;
}
algebra::Matrix algebra::minor(const algebra::Matrix& matrix,size_t n,size_t m){
    if(matrix.size()==0) return matrix;
    int nn=matrix.size(),mm=matrix[0].size();
    algebra::Matrix mat=zeros(nn-1,mm-1);
    for(int i=0;i<nn;i++) 
        for(int j=0;j<mm;j++){
            if(i==n||j==m) continue;
            mat[(i>n)?i-1:i][(j>m)?j-1:j]=matrix[i][j];
        }
    return mat;
}
double algebra::determinant(const algebra::Matrix& matrix){
    if (matrix.size()==0) return 1;
    int n=matrix.size(),m=matrix[0].size();
    if(n!=m) throw logic_error("The function of determinant has error!");
    if(n==1&&m==1) return matrix[0][0];
    double ans=0; double tag;
    for(int i=0;i<m;i++){
        tag=(i&1)?(-1):1;
        ans+=tag*matrix[0][i]*determinant(minor(matrix,0,i));
    }
    return ans;
}
algebra::Matrix algebra::inverse(const algebra::Matrix& matrix) {
    if (matrix.size() == 0) return {};
    double det;
    if (fabs(det=determinant(matrix)) < EPS) throw std::logic_error("The function of inverse has error!");
    int n=matrix.size(),m=matrix[0].size();
    algebra::Matrix mat=zeros(n,m);
    double tag;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            tag=((i+j)&1)?(-1):1;
            mat[i][j]=tag*determinant(minor(matrix,i,j))/det;
        }
    }
    return transpose(mat);
}
algebra::Matrix algebra::concatenate(const algebra::Matrix& matrix1,const Matrix& matrix2,int axis=0){
    if(matrix1.size()==0||matrix2.size()==0) return {};
    int n1=matrix1.size(),m1=matrix1[0].size(),n2=matrix2.size(),m2=matrix2[0].size();
    int N,M; Matrix mat;
    if(axis==0){
        if(m1!=m2) throw logic_error("The function of concatenate has error!");
        N=n1+n2, M=m1;
        mat=zeros(N,M);
        for(int i=0;i<n1;i++) for(int j=0;j<m1;j++) mat[i][j]=matrix1[i][j];
        for(int i=n1;i<N;i++) for(int j=0;j<m1;j++) mat[i][j]=matrix2[i-n1][j];
    }
    else{
        if(n1!=n2) throw logic_error("The function of concatenate has error!");
        N=n1, M=m1+m2;
        mat=zeros(N,M);
        for(int i=0;i<n1;i++) for(int j=0;j<m1;j++) mat[i][j]=matrix1[i][j];
        for(int i=0;i<n1;i++) for(int j=m1;j<M;j++) mat[i][j]=matrix2[i][j-m1];
    }
    return mat;
}
algebra::Matrix algebra::ero_swap(const algebra::Matrix& matrix,size_t r1,size_t r2) {
    if(matrix.size()==0) return {};
    int n=matrix.size(),m=matrix[0].size();
    if(r1>=n||r1<0||r2>=n||r2<0) throw logic_error("The function of ero_swap has error!");
    algebra::Matrix mat=matrix;
    for(int i=0;i<m;i++) swap(mat[r1][i],mat[r2][i]);
    return mat;
}
algebra::Matrix algebra::ero_multiply(const algebra::Matrix& matrix,size_t r,double c) {
    if(matrix.size()==0) return {};
    int n=matrix.size(),m=matrix[0].size();
    if(r<0||r>n) throw logic_error("The function of ero_multiply has error!");
    Matrix mat=matrix;
    for(int i=0;i<m;i++) mat[r][i]*=c;
    return mat;
}
algebra::Matrix algebra::ero_sum(const algebra::Matrix& matrix, size_t r1, double c, size_t r2) {
    if(matrix.size()==0) return {};
    int n=matrix.size(),m=matrix[0].size();
    algebra::Matrix mat=matrix;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j]=((i==r2)?(matrix[i][j]+matrix[r1][j]*c):(matrix[i][j]));
    return mat;
}
algebra::Matrix algebra::upper_triangular(const algebra::Matrix& matrix) {
    if(matrix.size()==0) return {};
    int n=matrix.size(),m=matrix[0].size();
    if(n!=m) throw logic_error("The function of upper_triangular has error!");
    algebra::Matrix mat=matrix;
    for(int i=0,j=0;i<n;i++,j++){
        int tag=i; while(tag<n&&fabs(mat[tag][j])<algebra::EPS) tag++;
        if(tag==n){ i--; continue; }
        if(i!=tag) mat=ero_swap(mat,i,tag);
        for(int k=i+1;k<n;k++) mat=ero_sum(mat,i,-mat[k][j]/mat[i][j],k);
    }
    return mat;
}

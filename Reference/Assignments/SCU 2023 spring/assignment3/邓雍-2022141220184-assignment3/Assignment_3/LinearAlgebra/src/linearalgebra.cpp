#include "linearalgebra.h"
#include<vector>
#include<utility>
#include<chrono>
#include<ctime>
#include<random>
#include<cstddef>
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;
using Matrix = std::vector<std::vector<double>>;
mt19937 mt_rand(chrono::system_clock::now().time_since_epoch().count());
const unsigned int inf=-1;
double rnd(double min,double max){return (1.0*mt_rand()/inf)*(max-min)+min;}

namespace algebra
{
    Matrix zeros(std::size_t n,std::size_t m)
    {
        Matrix x(n,vector<double>(m));
        return x;
    }
    Matrix ones(size_t n,size_t m)
    {
        Matrix x(n,vector<double>(m,1));
        return x;
    }
    Matrix Unit(size_t n)
    {
        Matrix x(n,vector<double>(n));
        for(int i=0;i<n;i++) x[i][i]=1;
        return x;
    }
    Matrix random(size_t n,size_t m,double min,double max)
    {
        if(max>min)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(min, max);
            Matrix random(n, std::vector<double>(m));
            for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) random[i][j]=dis(gen);
            return random;
        }
        else throw logic_error("min >= max");
    }
    void show(const Matrix& matrix)
    {
        for(int i=0;i<matrix.size();i++,puts(""))
        for(int j=0;j<matrix[i].size();j++) printf("%0.3lf ",matrix[i][j]);
    }
    Matrix multiply(const Matrix& matrix, double c)
    {
        Matrix x=matrix;
        for(int i=0;i<matrix.size();i++)
        for(int j=0;j<matrix[i].size();j++) x[i][j]*=c;
        return x;
    }
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
    {
        if(matrix1.empty()||matrix2.empty())
        {
            puts("Matrix is empty");
            return zeros(0,0);
        }
        int n1=matrix1.size(),m1=matrix1[0].size();
        int n2=matrix2.size(),m2=matrix2[0].size();
        if(m1!=n2) throw logic_error("Matrix type does not match, not multiplyable");
        Matrix x(matrix1.size(),vector<double>(matrix2[0].size()));
        for(int i=0;i<matrix1.size();i++)
        for(int j=0;j<matrix2[0].size();j++)
        for(int k=0;k<matrix1[i].size();k++) x[i][j]+=matrix1[i][k]*matrix2[k][j];
        return x;
    }
    Matrix sum(const Matrix& matrix, double c)
    {
        Matrix x=matrix;
        for(int i=0;i<matrix.size();i++)
        for(int j=0;j<matrix[i].size();j++) x[i][j]+=c;
        return x;
    }
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
    {
        if(matrix1.empty()&&matrix2.empty()) return zeros(0,0);
        else if(matrix1.empty()||matrix2.empty()) throw logic_error("Matrix type does not match");
        if(matrix1.size()!=matrix2.size()||matrix1[0].size()!=matrix2[0].size()) throw logic_error("Matrix type does not match");
        Matrix x(matrix1.size(),vector<double>(matrix1[0].size()));
        for(int i=0;i<matrix1.size();i++)
        for(int j=0;j<matrix1[0].size();j++) x[i][j]=matrix1[i][j]+matrix2[i][j];
        return x;
    }
    Matrix transpose(const Matrix& matrix)
    {
        if(matrix.empty()) return zeros(0,0);
        Matrix x(matrix[0].size(),vector<double>(matrix.size()));
        for(int i=0;i<matrix.size();i++)
        for(int j=0;j<matrix[0].size();j++) x[j][i]=matrix[i][j];
        return x;
    }
    Matrix minor(const Matrix& matrix,size_t n,size_t m)
    {
        if(n>=matrix.size()||m>=matrix[0].size()){puts("Out of range");return zeros(0,0);}
        Matrix x=matrix;x.erase(x.begin()+n);
        for(auto &i:x) i.erase(i.begin()+m);
        return x;
    }
    double determinant(const Matrix& matrix)
    {
        if(matrix.empty()||matrix[0].empty()) return 1;
        if(matrix.size()!=matrix[0].size()) throw logic_error("Matrix is not square");
        if(matrix.size()==1) return matrix[0][0];
        double det=0;
        for(int i=0;i<matrix.size();i++) det+=pow(-1,i)*matrix[i][0]*determinant(minor(matrix,i,0));
        return det;
    }
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2)
    {
        if(r1<0||r1>=matrix.size()||r2<0||r2>=matrix.size()) throw logic_error("Out of range");
        Matrix x=matrix;
        swap(x[r1],x[r2]);
        return x;
    }
    Matrix ero_multiply(const Matrix &matrix, size_t r, double c)
    {
        if(r<0||r>=matrix.size()) throw logic_error("Out of range");
        Matrix x=matrix;
        for(int i=0;i<matrix[r].size();i++) x[r][i]*=c;
        return x;
    }
    Matrix ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2)
    {
        if(r1<0||r1>=matrix.size()||r2<0||r2>=matrix.size()) throw logic_error("Out of range");
        Matrix x=matrix;
        for(int i=0;i<matrix[r2].size();i++) x[r2][i]+=c*x[r1][i];
        return x;
    }
    Matrix upper_triangular(const Matrix &matrix)
    {
        if(matrix.empty()) return zeros(0,0);
        if(matrix.size()!=matrix[0].size()) throw logic_error("Matrix is not square");
        Matrix x=matrix;
        for(int i=0;i<matrix[i].size()-1;i++)
        {
            if(!x[i][i])
            {
                for(int j=i+1;j<matrix[i].size();j++)
                {
                    if(!x[j][i])
                    {
                        x=ero_swap(x,i,j);
                        break;
                    }
                }
            }
            for(int j=i+1;j<matrix[i].size();j++) x=ero_sum(x,i,-x[j][i]/x[i][i],j);
        }
        return x;
    }
    Matrix inverse(const Matrix &matrix)
    {
        if(matrix.empty()||matrix[0].empty())
        {
            puts("Empty matrix");
            return zeros(0,0);
        }
        if(fabs(determinant(matrix))<=1e-7) throw logic_error("non_singular_matrix");
        if(matrix.size()!=matrix[0].size()) throw logic_error("non_singular_matrix");
        Matrix x=matrix,y=Unit(matrix.size());
        for(int i=0;i<matrix[i].size()-1;i++)
        {
            if(!x[i][i])
            {
                for(int j=i+1;j<matrix[i].size();j++)
                {
                    if(!x[j][i])
                    {
                        x=ero_swap(x,i,j);y=ero_swap(y,i,j);
                        break;
                    }
                }
            }
            for(int j=i+1;j<matrix[i].size();j++) x=ero_sum(x,i,-x[j][i]/x[i][i],j),y=ero_sum(y,i,-x[j][i]/x[i][i],j);
        }
        for(int i=matrix[i].size()-1;i>=0;i--)
        {
            double v=x[i][i];
            x=ero_multiply(x,i,1/v);y=ero_multiply(y,i,1/v);
            for(int j=i-1;j>=0;j--)
            {
                x=ero_sum(x,i,-x[j][i]/x[i][i],j);
                y=ero_sum(y,i,-x[j][i]/x[i][i],j);
            }
        }
        return y;
    }
    Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis)
    {
        if(!axis&&matrix1[0].size()==matrix2[0].size())
        {
            Matrix x(matrix1.size()+matrix2.size(),vector<double>(matrix2[0].size()));
            for (int i = 0;i<matrix1.size()+matrix2.size();i++)x[i]=i<matrix1.size()?matrix1[i]:matrix2[i-matrix1.size()];
            return x;
        }
        else if(!axis&&matrix1[0].size()!=matrix2[0].size()) throw logic_error("Matrix size not match");
        else if(axis&&matrix1.size()==matrix2.size())
        {
            Matrix x(matrix1.size(),vector<double>(matrix1[0].size()+matrix2[0].size()));
            for(int i=0;i<matrix1.size();i++)
            for(int j=0;j<matrix1[0].size()+matrix2[0].size();j++) x[i][j]=j<matrix1[0].size()?matrix1[i][j]:matrix2[i][j-matrix1[0].size()];
            return x;
        }
        else if(axis&&matrix1.size()!=matrix2.size()) throw logic_error("Matrix size not match");
        return zeros(0,0);
    }
}

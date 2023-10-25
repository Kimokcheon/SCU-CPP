#include "linearalgebra.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>

using std::size_t;

namespace algebra {

Matrix zeros(size_t n, size_t m) {
    Matrix mat(n);
    for (int i = 0; i < n; ++i) {
        mat[i] = std::vector<double>(m);
        for (int j = 0; j < m; ++j)
            mat[i][j] = 0;
    }
    return mat;
}

Matrix ones(size_t n, size_t m) {
    Matrix mat(n);
    for (int i = 0; i < n; ++i) {
        mat[i] = std::vector<double>(m);
        for (int j = 0; j < m; ++j)
            mat[i][j] = 1;
    }
    return mat;
}

Matrix random(size_t n, size_t m, double min, double max) {
    if (max < min) {
        throw std::logic_error("max is less then min!");
    }
    std::default_random_engine rg;
    rg.seed(std::random_device()());
    std::uniform_real_distribution<double> dist(min, max);
    Matrix mat(n);
    for (int i = 0; i < n; ++i) {
        mat[i] = std::vector<double>(m);
        for (int j = 0; j < m; ++j) {
            mat[i][j] = dist(rg);
        }
    }
    return mat;
}

// 3 decimal numbers
void show(const Matrix& matrix) {
    int n = matrix.size();
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < n; ++i) {
        int m = matrix[i].size();
        for (int j = 0; j < m ; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix multiply(const Matrix& matrix, double c) {
    if (matrix.size() == 0) return {};
    int n = matrix.size(), m = matrix[0].size();
    Matrix res = zeros(n ,m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            res[i][j] = matrix[i][j]*c;
    }
    return res;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.size() == 0 || matrix2.size() == 0) return {};
    int n, m, t;
    n = matrix1.size();
    m = matrix1[0].size();
    t = matrix2[0].size();
    if (m != matrix2.size()) {
        throw std::logic_error("These matrixes can't be multipled!");
    }
    Matrix res = zeros(n, t);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            for (int k = 0; k < m; ++k) {
                res[i][j] += matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    return res;
}

Matrix sum(const Matrix& matrix, double c) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix res = zeros(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res[i][j] = matrix[i][j] + c;
    return res;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.size() == 0 && matrix2.size() == 0) return {};
    int n, m;
    if (matrix1.size() != 0) {
        n = matrix1.size();
        m = matrix1[0].size();
        if (matrix2.size() != n || matrix2[0].size() != m) {
            throw std::logic_error("These matrixes can't add!");
        }
    } else if (matrix2.size() != 0) {
        n = matrix1.size();
        m = matrix1[0].size();
        if (matrix1.size() != n || matrix1[0].size() != m) {
            throw std::logic_error("These matrixes can't add!");
        }
    }
    Matrix res = zeros(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res[i][j] = matrix1[i][j] + matrix2[i][j];
    return res;
}

Matrix transpose(const Matrix& matrix) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix res = zeros(m, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res[j][i] = matrix[i][j];
    return res;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m) {
    if (matrix.size() == 0) return {};
    int N = matrix.size();
    int M = matrix[0].size();
    Matrix res = zeros(N-1, M-1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == n || j == m) continue;
            int tx = i, ty = j;
            if (i > n) --tx;
            if (j > m) --ty;
            res[tx][ty] = matrix[i][j];
        }
    }
    return res;
}

double determinant(const Matrix& matrix) {
    if (matrix.size() == 0) return 1;
    int n = matrix.size();
    int m = matrix[0].size();
    if (n != m) {
        throw std::logic_error("This matrix is not square!");
    }
    if (n == 1 && m == 1) {
        return matrix[0][0];
    }
    double res = 0;
    for (int i = 0; i < m; ++i) {
        int coe = 1;
        if (i%2 == 1) coe = -1;
        res += coe*matrix[0][i]*determinant(minor(matrix, 0, i));
    }
    return res;
}

Matrix inverse(const Matrix& matrix) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix res = zeros(n, m);
    double det = determinant(matrix);
    if (fabs(det) < EPS) {
        throw std::logic_error("inverse is not exsist!");
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int t = 1;
            if ((i+j)%2 == 1) t = -1;
            res[i][j] = t*determinant(minor(matrix, i, j))/det;
        }
    }
    res = transpose(res);
    return res;
}

Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis = 0) {
    if (matrix1.size() == 0 || matrix2.size() == 0) return {};
    int n1 = matrix1.size();
    int m1 = matrix1[0].size();
    int n2 = matrix2.size();
    int m2 = matrix2[0].size();
    int N, M;
    Matrix res;
    if (axis == 0 && m1 != m2) {
        throw std::logic_error("colomn is not same!");
    }
    if (axis == 1 && n1 != n2) {
        throw std::logic_error("row is not same!");
    }
    if (axis == 0) {
        N = n1+n2;
        M = m1;
        res = zeros(N, M);
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                res[i][j] = matrix1[i][j];
        for (int i = n1; i < N; ++i)
            for (int j = 0; j < m1; ++j)
                res[i][j] = matrix2[i-n1][j];
    } else {
        N = n1;
        M = m1+m2;
        res = zeros(N, M);
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                res[i][j] = matrix1[i][j];
        for (int i = 0; i < n1; ++i)
            for (int j = m1; j < M; ++j)
                res[i][j] = matrix2[i][j-m1];
    }
    return res;
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    if (r1 >= n || r1 < 0 || r2 >= n || r2 < 0) {
        throw std::logic_error("out of range!");
    }
    Matrix res = zeros(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == r1) res[i][j] = matrix[r2][j];
            else if (i == r2) res[i][j] = matrix[r1][j];
            else res[i][j] = matrix[i][j];
        }
    }
    return res;
}

Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    if (r < 0 || r >= n) {
        throw std::logic_error("out of range!");
    }
    Matrix res = zeros(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (i == r) res[i][j] = matrix[i][j] * c;
            else res[i][j] = matrix[i][j];
        }
    return res;
}

Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix res = zeros(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == r2) res[i][j] = matrix[i][j]+matrix[r1][j]*c;
            else res[i][j] = matrix[i][j];
        }
    }
    return res;
}

// Matrix upper_triangular(const Matrix& matrix) {
//     if (matrix.size() == 0) return {};
//     int n = matrix.size();
//     int m = matrix[0].size();
//     if (n != m) {
//         throw std::logic_error("non-square!");
//     }
//     Matrix res = matrix;
//     for (int i = 0, j = 0; i < n;) {
//         int ni = i;
//         while (ni < n && fabs(res[ni][j]) < EPS) ++ni;
//         if (ni == n) {
//             ni = 0;
//             ++j;
//             continue;
//         }
//         if (i != ni) res = ero_swap(res, i, ni);
//         for (int k = i+1; k < n; ++k) {
//             res = ero_sum(res, i, -res[k][j]/res[i][j], k);
//         }
//         ++i;
//         ++j;
//     }
//     return res;
// }
Matrix upper_triangular(const Matrix& matrix) {
    if (matrix.size() == 0) return {};
    int n = matrix.size();
    int m = matrix[0].size();
    if (n != m) {
        throw std::logic_error("non-square!");
    }
    Matrix res = matrix;
    for (int i = 0, j = 0; i < n;) {
        int k = i;
        while (k < n && fabs(res[k][j]) < EPS) ++k;
        if (k == n) {
            k = 0;
            ++j;
            continue;
        }
        if (i != k) res = ero_swap(res, i, k);
        for (int p = i+1; p < n; ++p) {
            res = ero_sum(res, i, -res[p][j]/res[i][j], p);
        }
        ++i;
        ++j;
    }
    return res;
}

}
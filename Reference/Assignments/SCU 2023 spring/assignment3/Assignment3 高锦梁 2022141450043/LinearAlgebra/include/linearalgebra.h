#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <random>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using Matrix = std::vector<std::vector<double>>;

namespace algebra {
    void show(const Matrix& matrix);
    Matrix primary_matrix(size_t n, int l1, int l2);
    Matrix primary_matrix(size_t n, int l, double c);
    Matrix primary_matrix(size_t n, int l1, int l2, double c);
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);
    Matrix set_E(size_t n);
    Matrix set_matrix(size_t n, size_t m);
    Matrix zeros(size_t n, size_t m);
    Matrix ones(size_t n, size_t m);
    Matrix random(size_t n, size_t m, double min, double max);
    Matrix multiply(const Matrix& matrix, double c);
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
    Matrix sum(const Matrix& matrix, double c);
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
    Matrix transpose(const Matrix& matrix);
    Matrix minor(const Matrix& matrix, size_t n, size_t m);
    double determinant(const Matrix& matrix);
    Matrix upper_triangular(const Matrix& matrix);
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);
    Matrix inverse(Matrix matrix);
}

#endif //LINEARALGEBRA_H

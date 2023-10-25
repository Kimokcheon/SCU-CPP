#include "linearalgebra.h"

namespace algebra {

    void show(const Matrix& matrix){
        for (const auto & i : matrix) {
            for (double j : i) {
                std::cout << std::fixed << std::setprecision(3) << j << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix primary_matrix(size_t n, int l1, int l2){
        Matrix matrix(set_E(n));
        std::swap(matrix[l1], matrix[l2]);
        return matrix;
    }

    Matrix primary_matrix(size_t n, int l, double c){
        Matrix matrix(set_E(n));
        for (double & i : matrix[l]) {
            i *= c;
        }
        return matrix;
    }

    Matrix primary_matrix(size_t n, int l1, int l2, double c){
        Matrix matrix(set_E(n));
        for (size_t i = 0; i < matrix[l1].size(); ++i) {
            matrix[l1][i] += matrix[l2][i] * c;
        }
        return matrix;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
        if(matrix.empty()) throw std::logic_error("Matrix is empty");
        if(r1 >= matrix.size() || r2 >= matrix.size()) throw std::logic_error("Row index is out of range");
        Matrix A = matrix;
        for(int i = 0; i < matrix[0].size(); ++i){
            double temp = A[r1][i];
            A[r1][i] = A[r2][i];
            A[r2][i] = temp;
        }
        return A;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
        if(matrix.empty()) throw std::logic_error("Matrix is empty");
        if(r >= matrix.size()) throw std::logic_error("Row index is out of range");
        Matrix A = matrix;
        for(int i = 0; i < matrix[0].size(); ++i){
            A[r][i] *= c;
        }
        return A;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
        if(matrix.empty()) throw std::logic_error("Matrix is empty");
        if(r1 >= matrix.size() || r2 >= matrix.size()) throw std::logic_error("Row index is out of range");
        Matrix A = matrix;
        for(int i = 0; i < matrix[0].size(); ++i){
            A[r2][i] += c * A[r1][i];
        }
        return A;
    }

    Matrix set_E(size_t n){
        Matrix matrix(n, std::vector<double>(n, 0));
        for (size_t i = 0; i < n; ++i) {
            matrix[i][i] = 1;
        }
        return matrix;
    }

    Matrix set_matrix(size_t n, size_t m){
        Matrix matrix(n, std::vector<double>(m, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        return matrix;
    }

    Matrix zeros(size_t n, size_t m){
        Matrix matrix(n, std::vector<double>(m, 0));
        return matrix;
    }

    Matrix ones(size_t n, size_t m){
        Matrix matrix(n, std::vector<double>(m, 1));
        return matrix;
    }

    Matrix random(size_t n, size_t m, double min, double max){
        if(min > max)throw std::logic_error("Invalid range");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(min, max);
        Matrix matrix(n, std::vector<double>(m, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                matrix[i][j] = dis(gen);
            }
        }
        return matrix;
    }

    Matrix multiply(const Matrix& matrix, double c){
        if(matrix.empty())throw std::logic_error("Invalid matrix");
        if(c == 0)return zeros(matrix.size(), matrix[0].size());
        Matrix result(matrix.size(), std::vector<double>(matrix[0].size(), 0));
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                result[i][j] = c * matrix[i][j];
            }
        }
        return result;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
        if(matrix1.empty() || matrix2.empty())return {};
        if(matrix1[0].size() != matrix2.size())throw std::logic_error("Invalid matrix");
        Matrix result(matrix1.size(), std::vector<double>(matrix2[0].size(), 0));
        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix2[0].size(); ++j) {
                for (size_t k = 0; k < matrix1[0].size(); ++k) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return result;
    }

    Matrix sum(const Matrix& matrix, double c){
        if(matrix.empty() || matrix[0].empty()) return {};
        Matrix result(matrix.size(), std::vector<double>(matrix[0].size(), 0));
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                result[i][j] = matrix[i][j] + c;
            }
        }
        return result;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
        if((matrix1.empty() && matrix2.empty()))return {};
        if((matrix1.empty() || matrix2.empty()))throw std::logic_error("Invalid matrix");
        if(matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())throw std::logic_error("Invalid matrix");
        Matrix result(matrix1.size(), std::vector<double>(matrix1[0].size(), 0));
        for (size_t i = 0; i < matrix1.size(); ++i) {
            for (size_t j = 0; j < matrix1[i].size(); ++j) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return result;
    }

    Matrix transpose(const Matrix& matrix){
        if(matrix.empty())return {};
        Matrix result(matrix[0].size(), std::vector<double>(matrix.size(), 0));
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                result[j][i] = matrix[i][j];
            }
        }
        return result;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m){
        if(matrix.empty())throw std::logic_error("Invalid matrix");
        Matrix result(matrix.size() - 1, std::vector<double>(matrix[0].size() - 1, 0));
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (i == n || j == m) continue;
                result[i < (n) ? i : i - 1][j < (m) ? j : j - 1] = matrix[i][j];
            }
        }
        return result;
    }

    double determinant(const Matrix& matrix){
        if(matrix.empty()) return 1;
        if(matrix.size() != matrix[0].size())throw std::logic_error("Invalid matrix");
        if (matrix.size() == 1) return matrix[0][0];
        double result = 0;
        for (size_t i = 0; i < matrix.size(); ++i) {
            result += matrix[0][i] * pow(-1, i) * determinant(minor(matrix, 0, i));
        }
        return result;
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if(matrix.empty())return {};
        if(matrix.size() != matrix[0].size())throw std::logic_error("Invalid matrix");
        Matrix A = matrix;
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            int pivot_row = i;
            if(A[i][i] == 0){
                for (int j = i + 1; j < n; ++j) {
                    if(A[j][i] != 0){
                        pivot_row = j;
                        break;
                    }
                }
                if(pivot_row == i)throw std::logic_error("Invalid matrix");
                std::swap(A[i], A[pivot_row]);
            }
            for (int j = i + 1; j < n; ++j) {
                double factor = A[j][i] / A[i][i];
                for (int k = i; k < n; ++k) {
                    A[j][k] -= factor * A[i][k];
                }
            }
        }
        return A;
    }

    Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis) {
        if (axis == 0) {
            if (matrix1[0].size() != matrix2[0].size()) throw std::invalid_argument("Matrices have different number of columns");
            Matrix result(matrix1.size() + matrix2.size(), std::vector<double>(matrix1[0].size(), 0));
            for (size_t i = 0; i < matrix1.size(); ++i) {
                for (size_t j = 0; j < matrix1[i].size(); ++j) {
                    result[i][j] = matrix1[i][j];
                }
            }
            for (size_t i = 0; i < matrix2.size(); ++i) {
                for (size_t j = 0; j < matrix2[i].size(); ++j) {
                    result[i + matrix1.size()][j] = matrix2[i][j];
                }
            }
            return result;
        } else if (axis == 1) {
            if (matrix1.size() != matrix2.size()) throw std::invalid_argument("Matrices have different number of rows");
            Matrix result(matrix1.size(), std::vector<double>(matrix1[0].size() + matrix2[0].size(), 0));
            for (size_t i = 0; i < matrix1.size(); ++i) {
                for (size_t j = 0; j < matrix1[i].size(); ++j) {
                    result[i][j] = matrix1[i][j];
                }
            }
            for (size_t i = 0; i < matrix2.size(); ++i) {
                for (size_t j = 0; j < matrix2[i].size(); ++j) {
                    result[i][j + matrix1[0].size()] = matrix2[i][j];
                }
            }
            return result;
        } else {
            throw std::invalid_argument("Axis must be 0 or 1");
        }
    }

    Matrix inverse(const Matrix matrix) {
        if (matrix.empty()) return {};
        if (determinant(matrix) == 0 || matrix.size() != matrix[0].size()) throw std::logic_error("Invalid matrix");
        Matrix A = matrix;
        Matrix E = set_E(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            if (A[i][i] == 0) {
                for (int j = i + 1; j < matrix.size(); j++) {
                    if (A[j][i] != 0) {
                        E = ero_swap(E, i, j);
                        A = ero_swap(A, i, j);
                        break;
                    }
                }
            }
            E = ero_multiply(E, i, 1 / A[i][i]);
            A = ero_multiply(A, i, 1 / A[i][i]);
            for (int j = 0; j < matrix.size(); j++) {
                if (j != i && A[j][i] != 0) {
                    E = ero_sum(E, i, -A[j][i], j);
                    A = ero_sum(A, i, -A[j][i], j);
                }
            }
        }
        return E;
    }
}
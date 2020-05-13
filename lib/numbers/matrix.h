#pragma once

#include "../general.h"

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T* data;

    void powerImpl(Matrix<T>& result, Matrix<T>& temp, ll exponent) const;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new T[rows * cols];
    }

    inline T* operator[](int row) {
        return data + (row * cols);
    }

    inline const T* operator[](int row) const {
        return data + (row * cols);
    }

    inline T& operator()(int row, int col) {
        return data[row * cols + col];
    }

    inline const T& operator()(int row, int col) const {
        return data[row * cols + col];
    }

    Matrix<T> power(ll exponent) const;

    template <typename U>
    friend void multiply(Matrix<U>& c, const Matrix<U>& a, const Matrix<U>& b);
};

template <typename T>
void multiply(Matrix<T>& c, const Matrix<T>& a, const Matrix<T>& b) {
    fill(c.data, c.data + c.rows * c.cols, 0);
    for (int i = 0; i < c.rows; i++) {
        for (int j = 0; j < b.rows; j++) {
            for (int k = 0; k < c.cols; k++) {
                c(i, k) += a(i, j) * b(j, k);
            }
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::power(ll exponent) const {
    Matrix<T> result(rows, cols);
    Matrix<T> temp(rows, cols);
    powerImpl(result, temp, exponent);
    return result;
}

template<typename T>
void Matrix<T>::powerImpl(Matrix<T> &result, Matrix<T> &temp, ll exponent) const {
    if (exponent == 0) {
        fill(result.data, result.data + rows * cols, 0);
        for (int i = 0; i < rows; i++) {
            result[i][i] = 1;
        }
    } else if ((exponent & 1) == 1) {
        powerImpl(temp, result, exponent - 1);
        multiply(result, temp, *this);
    } else {
        powerImpl(temp, result, exponent >> 1);
        multiply(result, temp, temp);
    }
}

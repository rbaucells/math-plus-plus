#pragma once
#include "matrix.h"

// m = m
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator=(const Matrix<ROWS, COLUMNS, T>& other) {
    if (this != &other) {
        memcpy(data, other.data, sizeof(T) * COLUMNS * ROWS);
    }

    return *this;
}

// m == m
template< int ROWS, int COLUMNS, scalar T>
bool Matrix<ROWS, COLUMNS, T>::equals(const Matrix<ROWS, COLUMNS, T>& other, const underlying_type_t<T> precision) const {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (!compare(data[c][r], other.data[c][r], precision))
                return false;
        }
    }

    return true;
}

template< int ROWS, int COLUMNS, scalar T>
bool Matrix<ROWS, COLUMNS, T>::operator==(const Matrix<ROWS, COLUMNS, T>& other) const {
    return equals(other);
}

// m + m
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::add(const Matrix<ROWS, COLUMNS, T>& other) const {
    Matrix<ROWS, COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] + other.data[c][r];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator+(const Matrix<ROWS, COLUMNS, T>& other) const {
    return add(other);
}

// m - m
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::subtract(const Matrix<ROWS, COLUMNS, T>& other) const {
    Matrix<ROWS, COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] - other.data[c][r];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator-(const Matrix<ROWS, COLUMNS, T>& other) const {
    return subtract(other);
}

// m * m
template< int ROWS, int COLUMNS, scalar T>
template<int OTHER_COLUMNS>
Matrix<ROWS, OTHER_COLUMNS, T> Matrix<ROWS, COLUMNS, T>::multiply(const Matrix<COLUMNS, OTHER_COLUMNS, T>& other) const {
    Matrix<ROWS, OTHER_COLUMNS, T> result;

    for (int c = 0; c < OTHER_COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            for (int x = 0; x < COLUMNS; x++) {
                result[c][r] += data[x][r] * other.data[c][x];
            }
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<int OTHER_COLUMNS>
Matrix<ROWS, OTHER_COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator*(const Matrix<COLUMNS, OTHER_COLUMNS, T>& other) const {
    return multiply(other);
}

// m * v
template< int ROWS, int COLUMNS, scalar T>
Vector<COLUMNS, T> Matrix<ROWS, COLUMNS, T>::multiply(const Vector<COLUMNS, T>& other) const {
    Vector<COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[r] += data[c][r] * other[c];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
Vector<COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator*(const Vector<COLUMNS, T>& other) const {
    return multiply(other);
}

// m * #
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::multiply(const T val) const {
    Matrix<ROWS, COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] * val;
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator*(const T val) const {
    return multiply(val);
}

// m / #
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::divide(const T scalar) const {
    Matrix<ROWS, COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] / scalar;
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator/(const T scalar) const {
    return divide(scalar);
}

// m += m
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::addEquals(const Matrix<ROWS, COLUMNS, T>& other) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] += other.data[c][r];
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator+=(const Matrix<ROWS, COLUMNS, T>& other) {
    return addEquals(other);
}

// m -= m
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::subtractEquals(const Matrix<ROWS, COLUMNS, T>& other) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] -= other.data[c][r];
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator-=(const Matrix<ROWS, COLUMNS, T>& other) {
    return subtractEquals(other);
}

// m *= #
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::multiplyEquals(const T val) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] *= val;
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator*=(const T val) {
    return multiplyEquals(val);
}

// m /= #
template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::divideEquals(const T scalar) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] /= scalar;
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator/=(const T scalar) {
    return divideEquals(scalar);
}

// Operators for different types

// m = m
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator=(const Matrix<ROWS, COLUMNS, OTHER_T>& other) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] = other.data[c][r];
        }
    }

    return *this;
}

// m == m
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::equality_comparable_with<OTHER_T, T>
bool Matrix<ROWS, COLUMNS, T>::equals(const Matrix<ROWS, COLUMNS, OTHER_T>& other, const std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHER_T>> precision) const {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (!compare(data[c][r], other.data[c][r], precision))
                return false;
        }
    }

    return true;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::equality_comparable_with<OTHER_T, T>
bool Matrix<ROWS, COLUMNS, T>::operator==(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const {
    return equals(other);
}

// m + m
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::add(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const {
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] + other.data[c][r];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::operator+(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const {
    return add(other);
}

// m - m
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::subtract(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const {
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] - other.data[c][r];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::operator-(const Matrix<ROWS, COLUMNS, OTHER_T>& other) const {
    return subtract(other);
}

// m * m
template< int ROWS, int COLUMNS, scalar T>
template<int OTHER_COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Matrix<ROWS, OTHER_COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::multiply(const Matrix<COLUMNS, OTHER_COLUMNS, OTHER_T>& other) const {
    Matrix<ROWS, OTHER_COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < OTHER_COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            for (int x = 0; x < COLUMNS; x++) {
                result[c][r] += data[x][r] * other.data[c][x];
            }
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<int OTHER_COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Matrix<ROWS, OTHER_COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::operator*(const Matrix<COLUMNS, OTHER_COLUMNS, OTHER_T>& other) const {
    return multiply(other);
}

// m * v
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Vector<COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::multiply(const Vector<COLUMNS, OTHER_T>& other) const {
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[r] += data[c][r] * other[c];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Vector<COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::operator*(const Vector<COLUMNS, OTHER_T>& other) const {
    return multiply(other);
}

// m * #
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::multiply(const OTHER_T val) const {
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] * val;
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::operator*(const OTHER_T val) const {
    return multiply(val);
}

// m / #
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::divide(const OTHER_T scalar) const {
    Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = data[c][r] / scalar;
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires HasCommonType<OTHER_T, T>
Matrix<ROWS, COLUMNS, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::operator/(const OTHER_T scalar) const {
    return divide(scalar);
}

// m += m
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::addEquals(const Matrix<ROWS, COLUMNS, OTHER_T>& other) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] += other.data[c][r];
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator+=(const Matrix<ROWS, COLUMNS, OTHER_T>& other) {
    return addEquals(other);
}

// m -= m
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::subtractEquals(const Matrix<ROWS, COLUMNS, OTHER_T>& other) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] -= other.data[c][r];
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator-=(const Matrix<ROWS, COLUMNS, OTHER_T>& other) {
    return subtractEquals(other);
}

// m *= #
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::multiplyEquals(const OTHER_T val) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] *= val;
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator*=(const OTHER_T val) {
    return multiplyEquals(val);
}

// m /= #
template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::divideEquals(const OTHER_T scalar) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            data[c][r] /= scalar;
        }
    }

    return *this;
}

template< int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T>
requires std::convertible_to<OTHER_T, T>
Matrix<ROWS, COLUMNS, T>& Matrix<ROWS, COLUMNS, T>::operator/=(const OTHER_T scalar) {
    return divideEquals(scalar);
}

template< int ROWS, int COLUMNS, scalar T>
T* Matrix<ROWS, COLUMNS, T>::operator[](const int index) {
    return &data[index][0];
}

template< int ROWS, int COLUMNS, scalar T>
const T* Matrix<ROWS, COLUMNS, T>::operator[](const int index) const {
    return &data[index][0];
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::operator-() const {
    Matrix<ROWS, COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = -data[c][r];
        }
    }

    return result;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::operator T*() {
    return &data[0][0];
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::operator const T*() const {
    return &data[0][0];
}

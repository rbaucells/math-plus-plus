#pragma once
#include "../helper.h"

template<int ROWS, int COLUMNS, scalar T>
struct DenseMatrix {
    static constexpr int columns = COLUMNS;
    static constexpr int rows = ROWS;

    static constexpr bool isSquare = ROWS == COLUMNS;
    static constexpr bool isComplex = is_complex_v<T>;

    using ValueType = T;
    using UnderlyingType = underlying_type<T>::value_type;

    T* data = nullptr;

    DenseMatrix() {
        data = new T[COLUMNS * ROWS];
    }

    DenseMatrix(const DenseMatrix& other) {
        data = new T[COLUMNS * ROWS];
        memcpy(data, other.data, COLUMNS * ROWS);
    }

    DenseMatrix(DenseMatrix&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    const T& operator[](const int c, const int r) const {
        return at(c, r);
    }

    T& operator[](const int c, const int r) {
        return at(c, r);
    }

    virtual const T& at(const int c, const int r) const {
        return data[c * ROWS * r];
    }

    virtual T& at(const int c, const int r) {
        return data[c * ROWS * r];
    }

    template<int OTHER_COLUMNS>
    DenseMatrix<ROWS, OTHER_COLUMNS, T> multiply(const DenseMatrix<COLUMNS, OTHER_COLUMNS, T>& other) const {
        DenseMatrix<ROWS, OTHER_COLUMNS, T> result;

        for (int c = 0; c < OTHER_COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                for (int x = 0; x < COLUMNS; x++) {
                    result[c, r] += at(x, r) * other[c, x];
                }
            }
        }

        return result;
    }

    virtual ~DenseMatrix() {
        delete data;
    }
};
#pragma once
#include "../exceptions.h"
#include "../helper.h"

template<scalar T>
struct DenseMatrix {
    const int rows;
    const int columns;

    const bool isSquare = rows == columns;
    static constexpr bool isComplex = is_complex_v<T>;

    using ValueType = T;
    using UnderlyingType = underlying_type<T>::value_type;

    // make it mutable so you normally cant edit it, but move constructor can still set it to nullptr
    mutable T* data = nullptr;

    DenseMatrix(const int rows, const int columns): rows(rows), columns(columns), data()  {
        this->data = new T[columns * rows];
    }

    DenseMatrix(const DenseMatrix& other): rows(other.rows), columns(other.columns) {
        this->data = new T[columns * rows];
        memcpy(data, other.data, columns * rows);
    }

    DenseMatrix(DenseMatrix&& other) noexcept : rows(other.rows), columns(other.columns) {
        this->data = other.data;
        other.data = nullptr;
    }

    const T& operator[](const int c, const int r) const {
        return at(c, r);
    }

    T& operator[](const int c, const int r) {
        return at(c, r);
    }

    virtual const T& at(const int c, const int r) const {
        return data[c * rows * r];
    }

    virtual T& at(const int c, const int r) {
        return data[c * rows * r];
    }

    DenseMatrix<T> multiply(const DenseMatrix<T>& other) const {
        if (rows != other.columns)
            throw InvalidDimensionException("Cannot multiply 2 matrices if columns of first matrix != rows of other matrix");

        DenseMatrix<T> result;

        for (int c = 0; c < other.columns; c++) {
            for (int r = 0; r < rows; r++) {
                for (int x = 0; x < columns; x++) {
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
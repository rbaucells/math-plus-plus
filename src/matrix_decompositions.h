#pragma once
#include <complex>
#include "matrix.h"

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LUPDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::lupDecomposition(int* numRowSwaps) const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<COLUMNS, ROWS, T> u = *this;
    Matrix<ROWS, ROWS, T> p = Matrix<ROWS, ROWS, T>::identity();

    // use std::min so we never access the pivot that's out of the matrix
    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        // handle row swaps
        {
            int rowIndex = -1;
            UnderlyingType rowValue = std::norm(u[c][c]);

            // iterate through rows of this column. Looking for the biggest boi
            for (int r = c + 1; r < ROWS; r++) {
                UnderlyingType curValue = std::norm(u[c][r]);

                if (curValue > rowValue) {
                    rowIndex = r;
                    rowValue = curValue;
                }
            }

            // we found nothing but we needed to find something
            if (rowIndex == -1 && compare(rowValue, 0)) {
                throw std::runtime_error("Cannot LUP decompose singular matrix");
            }

            if (rowIndex != -1) {
                // swap u and p rows like normal
                u = u.swapRows(c, rowIndex);
                p = p.swapRows(c, rowIndex);

                // swap rows of l before column c
                for (int i = 0; i < c; ++i) {
                    T temp = l[i][c];
                    l[i][c] = l[i][rowIndex];
                    l[i][rowIndex] = temp;
                }

                if (numRowSwaps != nullptr)
                    (*numRowSwaps)++;
            }
        }

        T pivot = u[c][c];

        // iterate through things beneath that pivot in the matrix
        for (int r = c + 1; r < ROWS; r++) {
            T val = u[c][r];

            T multiplierToPivotRow = val / pivot;

            l[c][r] = multiplierToPivotRow;

            // do this row minus other row times multiplier
            for (int i = c; i < COLUMNS; i++) {
                u[i][r] += -multiplierToPivotRow * u[i][c];
            }
        }
    }

    return {l, u, p};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LUPQDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, COLUMNS, T>> Matrix<COLUMNS, ROWS, T>::lupqDecomposition(int* numRowSwaps, int* numColumnSwaps) const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<COLUMNS, ROWS, T> u = *this;
    Matrix<ROWS, ROWS, T> p = Matrix<ROWS, ROWS, T>::identity();
    Matrix<COLUMNS, COLUMNS, T> q = Matrix<COLUMNS, COLUMNS, T>::identity();

    // use std::min so we never access the pivot that's out of the matrix
    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        // handle row AND column swaps
        {
            int rowIndex = -1;
            int columnIndex = -1;

            const T pivot = u[c][c];

            UnderlyingType maxValue = std::norm(pivot);

            for (int i = c; i < COLUMNS; i++) {
                for (int j = c; j < ROWS; j++) {
                    UnderlyingType curValue = std::norm(u[i][j]);

                    if (curValue > maxValue) {
                        maxValue = curValue;
                        columnIndex = i;
                        rowIndex = j;
                    }
                }
            }

            if (rowIndex == -1 && columnIndex == -1 && compare(pivot, 0)) {
                throw std::runtime_error("Cannot LUPQ decompose singular matrix");
            }

            if (rowIndex != c) {
                u = u.swapRows(c, rowIndex);
                p = p.swapRows(c, rowIndex);
                // swap rows of L before column c
                for (int i = 0; i < c; ++i) {
                    T temp = l[i][c];
                    l[i][c] = l[i][rowIndex];
                    l[i][rowIndex] = temp;
                }

                if (numRowSwaps != nullptr)
                    (*numRowSwaps)++;
            }

            if (columnIndex != c) {
                u = u.swapColumns(c, columnIndex);
                q = q.swapColumns(c, columnIndex);

                if (numColumnSwaps != nullptr)
                    (*numColumnSwaps)++;
            }
        }

        T pivot = u[c][c];

        // iterate through things beneath that pivot in the matrix
        for (int r = c + 1; r < ROWS; r++) {
            T val = u[c][r];

            T multiplierToPivotRow = val / pivot;

            l[c][r] = multiplierToPivotRow;

            // do this row minus other row times multiplier
            for (int i = c; i < COLUMNS; i++) {
                u[i][r] += -multiplierToPivotRow * u[i][c];
            }
        }
    }

    return {l, u, p, q};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::luDecomposition() const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<COLUMNS, ROWS, T> u = *this;

    // use std::min so we never access the pivot that's out of the matrix
    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        T pivot = u[c][c];

        if (compare(pivot, 0))
            throw std::runtime_error("Cannot LU decompose matrix due to zero pivot, try LUP or LUPQ");

        // iterate through things beneath that pivot in the matrix
        for (int r = c + 1; r < ROWS; r++) {
            T val = u[c][r];

            T multiplierToPivotRow = val / pivot;

            l[c][r] = multiplierToPivotRow;

            // do this row minus other row times multiplier
            for (int i = c; i < COLUMNS; i++) {
                u[i][r] += -multiplierToPivotRow * u[i][c];
            }
        }
    }

    return {l, u};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LDUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::lduDecomposition() const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<ROWS, ROWS, T> d = Matrix<ROWS, ROWS, T>::identity();
    Matrix<COLUMNS, ROWS, T> u = *this;

    // use std::min so we never access the pivot that's out of the matrix
    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        T pivot = u[c][c];

        if (compare(pivot, 0))
            throw std::runtime_error("Cannot LDU decompose matrix due to zero pivot");

        // iterate through things beneath that pivot in the matrix
        for (int r = c + 1; r < ROWS; r++) {
            T val = u[c][r];

            T multiplierToPivotRow = val / pivot;

            l[c][r] = multiplierToPivotRow;

            // do this row minus other row times multiplier
            for (int i = c; i < COLUMNS; i++) {
                u[i][r] += -multiplierToPivotRow * u[i][c];
            }
        }
    }

    for (int c = 0; c < COLUMNS; c++) {
        d[c][c] = u[c][c];

        for (int r = 0; r < ROWS; r++) {
            u[c][r] /= d[c][c];
        }
    }

    return {l, d, u};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template CholeskyDecomposition<Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<COLUMNS, ROWS, T>::choleskyDecomposition(const bool allowPositiveSemiDefinite) const requires (isSquare) {
    if (!isHermitian()) {
        throw std::runtime_error("Cannot find Cholesky Decomposition of non hermitian/symmetric matrix");
    }

    Matrix<COLUMNS, ROWS, T> l;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r <= c; r++) {
            if (r == c) {
                T value = data[c][c];

                for (int k = 0; k < c; k++) {
                    value -= std::norm(l[k][c]);
                }

                if (value < 0) {
                    throw std::runtime_error("Cannot cholesky decompose non positive definite matrix");
                }

                if (compare(value, 0) && !allowPositiveSemiDefinite) {
                    throw std::runtime_error("Cannot cholesky decompose non semi-positive definite matrix");
                }

                l[c][c] = std::sqrt(value);
            }
            else if (r > c) {
                T value = data[c][r];

                for (int k = 0; k < c; k++) {
                    value -= l[k][r] * l[k][c];
                }

                l[c][r] = value / l[c][c];
            }
        }
    }

    return {l, l.conjugateTranspose()};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LDLDecomposition<Matrix<COLUMNS, ROWS, T>, Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<COLUMNS, ROWS, T>::ldlDecomposition() const requires (isSquare) {
    Matrix<COLUMNS, ROWS, T> l;
    Matrix<COLUMNS, ROWS, T> d;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r <= c; r++) {
            if (r == c) {
                T value = data[c][c];

                for (int k = 0; k < c; k++) {
                    value -= std::norm(l[k][c]) * d[k][k];
                }

                d[c][c] = value;
            }
            else if (r > c) {
                T value = data[c][r];

                for (int k = 0; k < c; k++) {
                    if constexpr (!isComplex) {
                        value -= l[k][r] * l[k][c] * d[k][k];
                    }
                    else {
                        value -= l[k][r] * std::conj(l[k][c]) * d[k][k];
                    }

                    l[c][r] = (1 / d[c][c]) * value;
                }
            }
        }
    }

    return {l, d, l.conjugateTranspose()};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template QRDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::qrDecomposition() const requires (isSquare) {
    std::array<Vector<ROWS>, COLUMNS> a = getColumnVectors();
    std::array<Vector<ROWS>, COLUMNS> u = {};
    Matrix<ROWS, ROWS, T> q;

    for (int k = 0; k < COLUMNS; k++) {
        u[k] = a[k];

        for (int j = 0; j < k; j++) {
            u[k] -= u[j].projection(a[k]);
        }

        T uMagnitude = u[k].magnitude();

        for (int i = 0; i < ROWS; i++) {
            q[k][i] = u[k][i] / uMagnitude;
        }
    }

    Matrix<COLUMNS, ROWS, T> r = q.transpose() * *this;

    return {q, r};
}
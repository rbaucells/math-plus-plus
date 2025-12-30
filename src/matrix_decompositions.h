#pragma once
#include <complex>
#include "matrix.h"
#include "matrix_exceptions.h"

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::fullLuDecomposition(const bool skipZeroColumns) const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<COLUMNS, ROWS, T> u = *this;

    // use std::min so we never access the pivot that's out of the matrix
    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        T pivot = u[c][c];

        if (compare(pivot, 0)) {
            if (!skipZeroColumns)
                throw ZeroPivotException("Cannot LU decompose matrix due to zero pivot, try LUP or LUPQ");

            for (int r = c + 1; r < ROWS; r++) {
                if (!compare(u[c][r], 0))
                    throw ZeroPivotException("Cannot LU decompose matrix due to zero pivot, try LUP or LUPQ");
            }

            // skip this entire column
            continue;
        }

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
Matrix<COLUMNS, ROWS, T>::template LDUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::fullLduDecomposition() const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<ROWS, ROWS, T> d;
    Matrix<COLUMNS, ROWS, T> u = *this;

    // use std::min so we never access the pivot that's out of the matrix
    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        T pivot = u[c][c];

        if (compare(pivot, 0)) {
            throw ZeroPivotException("Cannot LU decompose matrix due to zero pivot, try LUP or LUPQ");
        }

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

    for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
        T pivot = u[c][c];

        d[c][c] = pivot;

        for (int i = c; i < COLUMNS; i++) {
            u[i][c] /= pivot;
        }
    }

    return {l, d, u};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LUPDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, ROWS, T>> Matrix<COLUMNS, ROWS, T>::fullLupDecomposition(const LUPDecompositionParams& params) const {
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
                if (params.skipZeroColumns)
                    continue;

                throw SingularMatrixException("Cannot LUP decompose singular matrix");
            }

            if (rowIndex != -1) {
                // swap u and p rows like normal
                u = u.swapRows(c, rowIndex);
                p = p.swapRows(c, rowIndex);

                // swap rows of l before column c
                for (int i = 0; i < c; i++) {
                    T temp = l[i][c];
                    l[i][c] = l[i][rowIndex];
                    l[i][rowIndex] = temp;
                }

                if (params.numRowSwaps != nullptr)
                    ++(*params.numRowSwaps);
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
Matrix<COLUMNS, ROWS, T>::template LUPQDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, COLUMNS, T>> Matrix<COLUMNS, ROWS, T>::fullLupqDecomposition(const LUPQDecompositionParams& params) const {
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

            UnderlyingType maxValue = std::norm(u[c][c]);

            for (int i = c + 1; i < COLUMNS; i++) {
                for (int j = c + 1; j < ROWS; j++) {
                    UnderlyingType curValue = std::norm(u[i][j]);

                    if (curValue > maxValue) {
                        maxValue = curValue;
                        columnIndex = i;
                        rowIndex = j;
                    }
                }
            }

            if (rowIndex == -1 && columnIndex == -1 && compare(maxValue, 0)) {
                if (params.skipZeroSections)
                    return {l, u, p, q};

                throw SingularMatrixException("Cannot LUPQ decompose singular matrix");
            }

            if (rowIndex != -1) {
                u = u.swapRows(c, rowIndex);
                p = p.swapRows(c, rowIndex);
                // swap rows of L before column c
                for (int i = 0; i < c; i++) {
                    T temp = l[i][c];
                    l[i][c] = l[i][rowIndex];
                    l[i][rowIndex] = temp;
                }

                if (params.numRowSwaps != nullptr)
                    ++(*params.numRowSwaps);
            }

            if (columnIndex != -1) {
                u = u.swapColumns(c, columnIndex);
                q = q.swapColumns(c, columnIndex);

                if (params.numColumnSwaps != nullptr)
                    ++(*params.numColumnSwaps);
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
Matrix<COLUMNS, ROWS, T>::template CholeskyDecomposition<Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<COLUMNS, ROWS, T>::choleskyDecomposition() const requires (isSquare) {
    if (!isHermitian())
        throw NotSymmetricOrHermitian("Cholesky decomposition is not valid for non symmetric / hermitian matrices");

    Matrix<COLUMNS, ROWS, T> l;
    Matrix<ROWS, COLUMNS, T> lt;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c; r < ROWS; r++) {
            if (c == r) {
                // data[c][c] is guaranteed to be real since matrix is hermitian, so just take real part
                UnderlyingType sum = std::real(data[c][c]);

                for (int k = 0; k < c; k++) {
                    sum -= std::norm(l[k][r]);
                }

                if (sum < 0 || compare(sum, 0, 0.001f))
                    throw NotPositiveDefinite("Cannot cholesky decompose matrix if not positive definite");

                T sqrt = std::sqrt(sum);

                l[c][c] = sqrt;
                lt[c][c] = sqrt;
            }
            else {
                T sum = data[c][r];

                for (int k = 0; k < c; k++) {
                    if constexpr (isComplex) {
                        sum -= std::conj(l[k][c]) * l[k][r];
                    }
                    else {
                        sum -= l[k][c] * l[k][r];
                    }
                }

                T val = sum / l[c][c];
                l[c][r] = val;

                if constexpr (isComplex)
                    lt[r][c] = std::conj(val);
                else
                    lt[r][c] = val;
            }
        }
    }

    return {l, lt};
}

template<int COLUMNS, int ROWS, scalar T>
Matrix<COLUMNS, ROWS, T>::template LDLDecomposition<Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<COLUMNS, ROWS, T>::ldlDecomposition(bool allowSemidefinite) const requires (isSquare) {
    if (!isHermitian())
        throw NotSymmetricOrHermitian("Cholesky decomposition is not valid for non symmetric / hermitian matrices");

    Matrix<COLUMNS, ROWS, T> l;
    Matrix<ROWS, ROWS, T> d;
    Matrix<ROWS, COLUMNS, T> lt;

    for (int c = 0; c < COLUMNS; c++) {
        d[c][c] = data[c][c];

        for (int k = 0; k < c; k++) {
            d[c][c] -= std::norm(l[k][c]);
        }

        for (int r = c; r < ROWS; r++) {
            T sum = data[c][r];

            for (int k = 0; k < c; k++) {
                if constexpr (isComplex) {
                    sum -= l[k][r] * std::conj(l[k][c]) * d[k][k];
                }
                else {
                    sum -= l[k][r] * l[k][c] * d[k][k];
                }
            }

            if (compare(d[c][c], 0)) {
                if (!allowSemidefinite)
                    throw NotPositiveDefinite("Could not LDL decompose non positive definite matrix");

                l[c][r] = 0;
                lt[r][c] = 0;
            }
            else {
                T val = sum / d[c][c];
                l[c][r] = val;

                if constexpr (isComplex)
                    lt[r][c] = std::conj(val);
                else
                    lt[r][c] = val;
            }
        }
    }

    return {l, d, lt};
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

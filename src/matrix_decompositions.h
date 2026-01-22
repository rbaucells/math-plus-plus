#pragma once
#include <complex>
#include "matrix.h"
#include "matrix_exceptions.h"

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template LUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::fullLuDecomposition(const bool skipZeroColumns) const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<ROWS, COLUMNS, T> u = *this;

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

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template LDUDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::fullLduDecomposition() const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<ROWS, ROWS, T> d;
    Matrix<ROWS, COLUMNS, T> u = *this;

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

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template LUPDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, ROWS, T>> Matrix<ROWS, COLUMNS, T>::fullLupDecomposition(const LUPDecompositionParams& params) const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<ROWS, COLUMNS, T> u = *this;
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

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template LUPQDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::fullLupqDecomposition(const LUPQDecompositionParams& params) const {
    Matrix<ROWS, ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
    Matrix<ROWS, COLUMNS, T> u = *this;
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

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template CholeskyDecomposition<Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::choleskyDecomposition(CholeskyDecompositionParams params) const requires (isSquare) {
    if (!params.skipChecks && !isHermitian())
        throw NotSymmetricOrHermitian("Cholesky decomposition is not valid for non symmetric / hermitian matrices");

    Matrix<ROWS, COLUMNS, T> l;
    Matrix<ROWS, COLUMNS, T> lt;

    for (int c = 0; c < COLUMNS; c++) {
        // data[c][c] is guaranteed to be real since matrix is hermitian, so just take real part
        UnderlyingType pivot = std::real(data[c][c]);

        for (int k = 0; k < c; k++) {
            pivot -= std::norm(l[k][c]);
        }

        if (compare(pivot, 0, params.precision)) {
            if (!params.allowPositiveSemiDefinite)
                throw NotPositiveDefinite("Cannot continue cholesky decomposition as matrix is not positive definite (0 found on l's diagonal)");

            // set it to exactly zero to avoid floating point arithmetic
            l[c][c] = 0;
        }
        else if (pivot < 0)
            throw NotPositiveDefinite("Cannot cholesky decompose matrix if not positive definite");
        else
            l[c][c] = lt[c][c] = std::sqrt(pivot);

        for (int r = c + 1; r < ROWS; r++) {
            T sum = data[c][r];

            for (int k = 0; k < c; k++) {
                if constexpr (isComplex) {
                    sum -= std::conj(l[k][c]) * l[k][r];
                }
                else {
                    sum -= l[k][c] * l[k][r];
                }
            }

            if (compare(l[c][c], 0)) {
                if (!params.allowPositiveSemiDefinite)
                    throw NotPositiveDefinite("Cannot continue cholesky decomposition as matrix is not positive definite (0 found on l's diagonal)");

                l[c][r] = 0;
                lt[r][c] = 0;
            }
            else {
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

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template PivotedCholeskyDecomposition<Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::pivotedCholeskyDecomposition(PivotedCholeskyDecompositionParams params) const requires (isSquare) {
    if (!params.skipChecks && !isHermitian())
        throw NotSymmetricOrHermitian("Cholesky decomposition is not valid for non symmetric / hermitian matrices");

    Matrix<ROWS, COLUMNS, T> l;
    Matrix<ROWS, COLUMNS, T> lt;
    Matrix<ROWS, COLUMNS, T> p = Matrix<ROWS, COLUMNS, T>::identity();
    Matrix<ROWS, COLUMNS, T> pt = Matrix<ROWS, COLUMNS, T>::identity();

    Matrix<ROWS, COLUMNS, T> a = *this;

    for (int c = 0; c < COLUMNS; c++) {
        // use std::real cuz main diagonal of hermitian matrix is real
        UnderlyingType value = std::real(a[c][c]);
        int index = -1;

        for (int i = c; i < COLUMNS; i++) {
            UnderlyingType curValue = std::real(a[i][i]);

            if (curValue > value) {
                index = i;
                value = curValue;
            }
        }

        // we did what we could, this reveals the rank
        if (index == -1 && compare(value, 0, params.precision))
            break;

        {
            // use std::real cuz main diagonal of hermitian matrix is real
            UnderlyingType sum = std::real(a[c][c]);

            for (int k = 0; k < c; k++) {
                sum -= std::norm(l[k][c]);
            }

            if (compare(sum, 0, params.precision))
                break;

            if (sum < 0)
                throw NotPositiveDefinite("Cannot cholesky decompose matrix if not positive definite");

            l[c][c] = lt[c][c] = std::sqrt(sum);
        }

        for (int r = c + 1; r < ROWS; r++) {
            T sum = a[c][r];

            for (int k = 0; k < c; k++) {
                if constexpr (isComplex) {
                    sum -= std::conj(l[k][c]) * l[k][r];
                }
                else {
                    sum -= l[k][c] * l[k][r];
                }
            }

            if (compare(l[c][c], 0))
                return {l, lt, p, pt};

            T val = sum / l[c][c];
            l[c][r] = val;

            if constexpr (isComplex)
                lt[r][c] = std::conj(val);
            else
                lt[r][c] = val;
        }
    }

    return {l, lt, p, pt};
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template LDLDecomposition<Matrix<ROWS, COLUMNS, T>, Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::ldlDecomposition(const bool allowSemidefinite, const UnderlyingType precision) const requires (isSquare) {
    if (!isHermitian())
        throw NotSymmetricOrHermitian("Cholesky decomposition is not valid for non symmetric / hermitian matrices");

    Matrix<ROWS, COLUMNS, T> l;
    Matrix<ROWS, COLUMNS, T> d;

    for (int c = 0; c < COLUMNS; c++) {
        d[c][c] = data[c][c];

        for (int k = 0; k < c; k++) {
            d[c][c] -= std::norm(l[k][c]) * d[k][k];
        }

        for (int r = c; r < ROWS; r++) {
            if (compare(d[c][c], 0, precision)) {
                if (!allowSemidefinite)
                    throw NotPositiveDefinite("Could not LDL' decompose matrix if not PD");

                l[c][r] = 0;
            }
            else {
                T sum = data[c][r];

                for (int k = 0; k < c; k++) {
                    if constexpr (isComplex)
                        sum -= l[k][r] * std::conj(l[k][c]) * d[k][k];
                    else
                        sum -= l[k][r] * l[k][c] * d[k][k];
                }

                l[c][r] = sum / d[c][c];
            }
        }
    }

    return {l, d, l.conjugateTranspose()};
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template QRDecomposition<Matrix<ROWS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> Matrix<ROWS, COLUMNS, T>::qrDecomposition() const requires (isSquare) {
    std::array<Vector<ROWS>, COLUMNS> a = getColumnVectors();
    std::array<Vector<ROWS>, COLUMNS> u = {};
    Matrix<ROWS, ROWS, T> q;

    for (int k = 0; k < COLUMNS; k++) {
        u[k] = a[k];

        for (int j = 0; j < k; j++) {
            u[k] -= u[j].vectorProjectOnto(a[k]);
        }

        T uMagnitude = u[k].euclidianNorm();

        for (int i = 0; i < ROWS; i++) {
            q[k][i] = u[k][i] / uMagnitude;
        }
    }

    Matrix<ROWS, COLUMNS, T> r = q.transpose() * *this;

    return {q, r};
}

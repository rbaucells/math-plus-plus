#pragma once
#include <complex>

#include "matrix.h"

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isRowEchelon(bool pivotMustBeOne) const {
    bool foundZeroRows = false;
    int lastPivotColumn = -1;
    for (int r = 0; r < ROWS; r++) {
        bool foundNonZero = false;
        for (int c = 0; c < COLUMNS; c++) {
            // found non-zero
            if (!compare(data[c][r], 0)) {
                // pivot
                if (!foundNonZero) {
                    // we are to the left or at same level as last pivot.
                    if (c <= lastPivotColumn)
                        return false;

                    // pivot needed to be 1, it wasn't
                    if (!compare(data[c][r], 1) && pivotMustBeOne)
                        return false;

                    lastPivotColumn = c;
                }

                foundNonZero = true;
            }
        }

        // non zero row when supposed to
        if (foundNonZero && foundZeroRows)
            return false;

        // zero row
        if (!foundNonZero) {
            foundZeroRows = true;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isReducedRowEchelon() const {
    bool foundZeroRows = false;
    int lastPivotColumn = -1;

    for (int r = 0; r < ROWS; r++) {
        bool foundNonZero = false;

        for (int c = 0; c < COLUMNS; c++) {
            T curValue = data[c][r];
            if (!compare(curValue, 0)) {
                // if we havent found nonzero, this is a pivot
                if (!foundNonZero) {
                    // pivot is to left of last pivot
                    if (c <= lastPivotColumn)
                        return false;

                    // pivots need to be 1
                    if (!compare(curValue, 1)) {
                        return false;
                    }

                    // check that this column doesnt have any other non zero numbers
                    for (int rr = 0; rr < ROWS; rr++) {
                        if (rr == r)
                            continue;

                        if (!compare(data[c][rr], 0))
                            return false;
                    }

                    foundNonZero = true;
                    lastPivotColumn = c;
                }

                foundNonZero = true;
            }
        }

        // non zero row when supposed to
        if (foundNonZero && foundZeroRows)
            return false;

        // zero row
        if (!foundNonZero) {
            foundZeroRows = true;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isSymmetrical() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (!compare(data[c][r], data[r][c]))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isSkewSymmetrical() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (!compare(data[c][r], -data[r][c]))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isHermitian() const requires (isSquare) {
    if constexpr (!isComplex)
        return isSymmetrical();
    else {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], std::conj(data[r][c]))) {
                    return false;
                }
            }
        }

        return true;
    }
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isSkewHermitian() const requires (isSquare) {
    if constexpr (!isComplex)
        return isSkewSymmetrical();
    else {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], -std::conj(data[r][c])))
                    return false;
            }
        }

        return true;
    }
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isPositiveDefinite(const PositiveDefiniteAlgorithm algorithm) const requires (isSquare) {
    switch (algorithm) {
        case PositiveDefiniteAlgorithm::ldl:
            return isPositiveDefiniteLdl();
        case PositiveDefiniteAlgorithm::sylvester:
        default:
            return isPositiveDefiniteSylvester();
    }
}

template<int COLUMNS, int ROWS, scalar T>
template<int K>
bool Matrix<COLUMNS, ROWS, T>::isPositiveDefiniteSylvester() const requires (isSquare) {
    if constexpr (K > COLUMNS)
        return true;
    else {
        T upperLeftSubMatrixDeterminant = upperLeftSubMatrix<K>().determinant(Matrix<K, K, T>::DeterminantAlgorithm::lu);
        bool isPositiveDefiniteK1 = isPositiveDefiniteSylvester<K + 1>();
        return upperLeftSubMatrixDeterminant > 0 && isPositiveDefiniteK1;
    }
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isPositiveDefiniteLdl() const requires (isSquare) {

}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isPositiveSemiDefinite() const requires (isSquare) {}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isNegativeDefinite() const requires (isSquare) {}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isNegativeSemiDefinite() const requires (isSquare) {}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isUnitary() const requires (isSquare) {
    return conjugateTranspose() * *this == identity();
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isSpecialUnitary() const requires (isSquare) {
    return conjugateTranspose() * *this == identity() && compare(determinant(), 1);
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isOrthogonal() const requires (!isComplex && isSquare) {
    return transpose() * *this == identity();
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isSpecialOrthogonal() const requires (!isComplex && isSquare) {
    return transpose() * *this == identity() && compare(determinant(), 1);
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isSemiOrthogonal() const requires (!isComplex && !isSquare) {
    if constexpr (COLUMNS > ROWS) { // wide
        return multiply(transpose()) == identity();
    }
    else { // tall
        return transpose() * *this == identity();
    }
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isUpperTriangleMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        // dont worry about out of bounds, loop wont even run if c + 1 is too big
        for (int r = c + 1; r < ROWS; r++) {
            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isLowerTriangleMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < c; r++) {
            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isDiagonalMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            if (c == r)
                continue;

            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isUpperUnitriangularMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c; r < ROWS; r++) {
            if (c == r) {
                if (!compare(data[c][r], 1)) {
                    return false;
                }
            }
            else if (!compare(data[c][r], 0)) {
                return false;
            }
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isLowerUnitriangularMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r <= c; r++) {
            if (c == r) {
                if (!compare(data[c][r], 1)) {
                    return false;
                }
            }
            else if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isStrictlyUpperTriangularMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c; r < ROWS; r++) {
            if (!compare(data[c][r], 0)) {
                return false;
            }
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isStrictlyLowerTriangularMatrix() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r <= c; r++) {
            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isFrobeniusMatrix() const requires (isSquare) {
    int columnWithNonZero = -1;
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            // not a one on diagonal
            if (c == r && !compare(data[c][r], 1)) {
                return false;
            }
            if (!compare(data[c][r], 0)) {
                // its above
                if (r <= c)
                    return false;

                // too many columns with nonzero
                if (columnWithNonZero != c)
                    return false;

                columnWithNonZero = c;
            }
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isUpperHessenberg() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c + 2; r < ROWS; r++) {
            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isUnreducedUpperHessenberg() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c + 1; r < ROWS; r++) {
            // subdiagonal
            if (r == c + 1) {
                if (compare(data[c][r], 0)) {
                    return false;
                }
            }
            else {
                if (!compare(data[c][r], 0)) {
                    return false;
                }
            }
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isLowerHessenberg() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c - 2; r >= 0; r--) {
            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isUnreducedLowerHessenberg() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = c - 1; r >= 0; r--) {
            // supra-diagonal
            if (r == c - 1) {
                if (compare(data[c][r], 0)) {
                    return false;
                }
            }
            else {
                if (!compare(data[c][r], 0)) {
                    return false;
                }
            }
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isTridiagonal() const requires (isSquare) {
    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            // diagonal, subdiagonal, supradiagonal
            if (c == r || c == r + 1 || c == r - 1)
                continue;

            if (!compare(data[c][r], 0))
                return false;
        }
    }

    return true;
}

template<int COLUMNS, int ROWS, scalar T>
bool Matrix<COLUMNS, ROWS, T>::isRowEchelonOfThis(const Matrix<COLUMNS, ROWS, T>& ref, const Matrix<COLUMNS, ROWS, T>::UnderlyingType precision) const {
    if (!ref.isRowEchelon())
        return false;

    const Matrix<COLUMNS, ROWS, T> rrefOfRef = ref.toReducedRowEchelon();
    const Matrix<COLUMNS, ROWS, T> rrefOfThis = toReducedRowEchelon();

    return rrefOfRef.equals(rrefOfThis, precision);
}

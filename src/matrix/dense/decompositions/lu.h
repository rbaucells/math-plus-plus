#pragma once
#include "../helper.h"
#include "../matrix.h"
#include "../../exceptions.h"

template<scalar T>
struct DenseLuDecomposition {
    DenseMatrix<T> l;
    DenseMatrix<T> u;
};

template<scalar T>
DenseLuDecomposition<T> lu_decomposition(const DenseMatrixBase<T>& m, const bool skipZeroColumns = false) {
    const int rows = m.rows;
    const int columns = m.columns;

    DenseMatrix<T> l = DenseMatrix<T>::identity(rows);
    DenseMatrix<T> u = m;

    for (int c = 0; c < std::min(rows, columns); c++) {
        const T pivot = m[c, c];

        if (compare(pivot, 0)) {
            if (!skipZeroColumns) {
                throw InvalidPivotException("Zero pivot in lu_decomposition");
            }

            for (int r = c + 1; r < rows; r++) {
                if (!compare(u[c, r], 0)) {
                    throw InvalidPivotException("Zero column in lu_decomposition (skipZeroColumns = false)");
                }
            }

            // skip this entire column
            continue;
        }

        // iterate through things beneath that pivot in the matrix
        for (int r = c + 1; r < rows; r++) {
            T val = u[c, r];

            T multiplierToPivotRow = val / pivot;

            l[c, r] = multiplierToPivotRow;

            // do this row minus other row times multiplier
            for (int i = c; i < columns; i++) {
                u[i, r] += -multiplierToPivotRow * u[i, c];
            }
        }
    }

    return {std::move(l), std::move(u)};
}
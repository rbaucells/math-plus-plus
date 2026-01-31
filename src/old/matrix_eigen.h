#pragma once
#include "matrix.h"
#include "matrix_exceptions.h"

template< int ROWS, int COLUMNS, scalar T>
template<int ITER>
Matrix<ROWS, COLUMNS, T>::template LanczosAlgorithm<Matrix<ITER, ITER, T>, Matrix<COLUMNS, ITER + 1, T>> Matrix<ROWS, COLUMNS, T>::lanczosAlgorithm() const requires (isSquare) {
    if (!isHermitian())
        throw NotSymmetricOrHermitian("Cannot do Lanczos algorithm on non hermitian matrix");

    std::array<Vector<COLUMNS, T>, ITER + 1> q;

    Matrix<ITER, ITER, T> t;
    Matrix<COLUMNS, ITER + 1, T> qMatrix;

    qMatrix.setColumnVector(0, Vector<COLUMNS, T>::random().normalize());

    for (int m = 0; m < ITER; m++) {
        Vector<COLUMNS, T> v = multiply(q[m]);
        t[m][m] = q[m] * v;

        if (m == 0) {
            v -= t[m][m] * q[m];
        }
        else {
            v -= t[m][m - 1] * q[m - 1] - t[m][m] * q[m];
        }

        T vNorm = v.euclidianNorm();

        if (m != ITER - 1) {
            t[m][m + 1] = t[m + 1][m] = vNorm;
        }

        q[m + 1] = v / vNorm;

        qMatrix.setColumnVector(m + 1, q[m + 1]);
    }

    return {t, qMatrix};
}

template< int ROWS, int COLUMNS, scalar T>
T Matrix<ROWS, COLUMNS, T>::rayleighQuotient(const Vector<COLUMNS, T>& vec) const {
    return vec.dot(multiply(vec)) / vec.euclidianNormSquared();
}

template< int ROWS, int COLUMNS, scalar T>
Vector<COLUMNS, T> Matrix<ROWS, COLUMNS, T>::inverseIteration(InverseIterationParams<Vector<COLUMNS, T>, T, UnderlyingType> params) const {
    Vector<COLUMNS, T> b_k = params.startingVector;
    Matrix<ROWS, COLUMNS, T> thisMinusEigenIdentityInverse = subtract(params.eigenVal * identity()).inverse();

    for (int k = 0; k < params.maxIterations; k++) {
        Vector<COLUMNS, T> b_k1 = (thisMinusEigenIdentityInverse * b_k).normalized();

        if (params.tolerance > 0 && (b_k - b_k1).euclidianNorm() < params.tolerance)
            return b_k1;

        b_k = b_k1;
    }

    return b_k;
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template EigenPair<Vector<COLUMNS, T>, T> Matrix<ROWS, COLUMNS, T>::rayleighQuotientIteration(RayleighQuotientIterationParams<Vector<COLUMNS, T>, T, UnderlyingType> params ) const {
    Vector<COLUMNS, T> b_k = params.vectorApproximation;
    T u_k = params.valueApproximation.value_or(rayleighQuotient(b_k));

    for (int k = 0; k < params.maxIterations; k++) {
        Vector<COLUMNS, T> b_k1 = (subtract(u_k * identity()).inverse() * b_k).normalized();
        T u_k1 = rayleighQuotient(b_k1);

        if (params.tolerance > 0 && (b_k - b_k1).euclidianNorm() < params.tolerance && std::abs(u_k - u_k1) < params.tolerance)
            return {b_k1, u_k1};

        b_k = b_k1;
        u_k = u_k1;
    }

    return {b_k, u_k};
}

template< int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T>::template EigenPair<Vector<COLUMNS, T>, T> Matrix<ROWS, COLUMNS, T>::powerIteration(PowerIterationParams<Vector<COLUMNS, T>, UnderlyingType> params) const {
    Vector<COLUMNS, T> b_k = params.vectorApproximation;
    T u_k = {};

    for (int k = 0; k < params.maxIterations; k++) {
        Vector<COLUMNS, T> b_k1 = multiply(b_k).normalized();
        T u_k1 = rayleighQuotient(b_k1);

        if (params.tolerance > 0 && (b_k - b_k1).euclidianNorm() < params.tolerance && std::abs(u_k - u_k1) < params.tolerance)
            return {b_k1, u_k1};

        b_k = b_k1;
        u_k = u_k1;
    }

    return {b_k, u_k};
}

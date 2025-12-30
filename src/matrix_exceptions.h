#pragma once
#include <stdexcept>

class MatrixException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class SingularMatrixException : public MatrixException {
    using MatrixException::MatrixException;
};

class ZeroPivotException : public MatrixException {
    using MatrixException::MatrixException;
};

class NotPositiveDefinite : public MatrixException {
    using MatrixException::MatrixException;
};

class NotSymmetricOrHermitian : public MatrixException {
    using MatrixException::MatrixException;
};

class NotPositiveDefiniteOrPositiveSemiDefinite : public MatrixException {
    using MatrixException::MatrixException;
};

#pragma once
#include "matrix.h"

class MatrixException : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class SingularMatrixException : public MatrixException
{
    using MatrixException::MatrixException;
};

class ZeroPivotException : public MatrixException
{
    using MatrixException::MatrixException;
};

class NonHermitianException : public MatrixException
{
    using MatrixException::MatrixException;
};

class NotPositiveDefiniteException : public MatrixException
{
    using MatrixException::MatrixException;
};

class NotPositiveSemiDefiniteException : public MatrixException
{
    using MatrixException::MatrixException;
};

class InvalidDimension : public std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};

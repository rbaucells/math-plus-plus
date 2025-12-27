#pragma once
#include "matrix.h"

class MatrixException : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class SingularMatrix : public MatrixException
{
    using MatrixException::MatrixException;
};

class ZeroPivot : public MatrixException
{
    using MatrixException::MatrixException;
};

class NonHermitian : public MatrixException
{
    using MatrixException::MatrixException;
};

class NotPositiveDefinite : public MatrixException
{
    using MatrixException::MatrixException;
};

class NotPositiveSemiDefinite : public MatrixException
{
    using MatrixException::MatrixException;
};

class InvalidDimension : public std::invalid_argument
{
    using std::invalid_argument::invalid_argument;
};

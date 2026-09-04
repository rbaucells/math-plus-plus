#ifndef MATHPY_MATRIX_DENSE_H
#define MATHPY_MATRIX_DENSE_H

#include <variant>
#include "mathpp/implementation/matrix/dense/matrix.h"

#include <cstdint>

struct Py_DenseMatrix final : std::variant<DenseMatrix<int8_t>, DenseMatrix<uint8_t>, DenseMatrix<int16_t>, DenseMatrix<uint16_t>, DenseMatrix<int32_t>, DenseMatrix<uint32_t>, DenseMatrix<int64_t>, DenseMatrix<uint64_t>, DenseMatrix<float>, DenseMatrix<double>, DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<double>>>, DenseMatrixLikeBase {
    using std::variant<DenseMatrix<int8_t>, DenseMatrix<uint8_t>, DenseMatrix<int16_t>, DenseMatrix<uint16_t>, DenseMatrix<int32_t>, DenseMatrix<uint32_t>, DenseMatrix<int64_t>, DenseMatrix<uint64_t>, DenseMatrix<float>, DenseMatrix<double>, DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<double>>>::variant;
};

#endif // MATHPY_MATRIX_DENSE_H

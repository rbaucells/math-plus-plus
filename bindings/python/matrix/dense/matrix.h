#ifndef MATHPY_MATRIX_DENSE_H
#define MATHPY_MATRIX_DENSE_H

#include "../../main.h"
#include "mathpp/implementation/matrix/dense/matrix.h"
#include <variant>
#include <cstdint>

using Py_DenseMatrix = PyWrapper<std::variant<DenseMatrix<int8_t>, DenseMatrix<uint8_t>, DenseMatrix<int16_t>, DenseMatrix<uint16_t>, DenseMatrix<int32_t>, DenseMatrix<uint32_t>, DenseMatrix<int64_t>, DenseMatrix<uint64_t>, DenseMatrix<float>, DenseMatrix<double>, DenseMatrix<std::complex<float>>, DenseMatrix<std::complex<double>>>>;

#endif // MATHPY_MATRIX_DENSE_H

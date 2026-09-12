#ifndef MATHPY_VECTOR_DENSE_VECTOR_H
#define MATHPY_VECTOR_DENSE_VECTOR_H

#include <variant>
#include "mathpp/implementation/vector/dense/vector.h"

#include <cstdint>

struct Py_DenseVector : std::variant<DenseVector<int8_t>, DenseVector<uint8_t>, DenseVector<int16_t>, DenseVector<uint16_t>, DenseVector<int32_t>, DenseVector<uint32_t>, DenseVector<int64_t>, DenseVector<uint64_t>, DenseVector<float>, DenseVector<double>, DenseVector<std::complex<float>>, DenseVector<std::complex<double>>>, DenseVectorLikeBase {
    using std::variant<DenseVector<int8_t>, DenseVector<uint8_t>, DenseVector<int16_t>, DenseVector<uint16_t>, DenseVector<int32_t>, DenseVector<uint32_t>, DenseVector<int64_t>, DenseVector<uint64_t>, DenseVector<float>, DenseVector<double>, DenseVector<std::complex<float>>, DenseVector<std::complex<double>>>::variant;
};

#endif // MATHPY_VECTOR_DENSE_VECTOR_H

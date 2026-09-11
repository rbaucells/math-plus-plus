#ifndef MATHPY_MATRIX_DENSE_VIEW_H
#define MATHPY_MATRIX_DENSE_VIEW_H

#include <variant>
#include "mathpp/implementation/matrix/dense/view.h"

#include <cstdint>

struct Py_DenseMatrixView final : std::variant<std::shared_ptr<const DenseMatrixView<int8_t>>, std::shared_ptr<const DenseMatrixView<uint8_t>>, std::shared_ptr<const DenseMatrixView<int16_t>>, std::shared_ptr<const DenseMatrixView<uint16_t>>, std::shared_ptr<const DenseMatrixView<int32_t>>, std::shared_ptr<const DenseMatrixView<uint32_t>>, std::shared_ptr<const DenseMatrixView<int64_t>>, std::shared_ptr<const DenseMatrixView<uint64_t>>, std::shared_ptr<const DenseMatrixView<float>>, std::shared_ptr<const DenseMatrixView<double>>, std::shared_ptr<const DenseMatrixView<std::complex<float>>>, std::shared_ptr<const DenseMatrixView<std::complex<double>>>>, DenseMatrixLikeBase {
    using std::variant<std::shared_ptr<const DenseMatrixView<int8_t>>, std::shared_ptr<const DenseMatrixView<uint8_t>>, std::shared_ptr<const DenseMatrixView<int16_t>>, std::shared_ptr<const DenseMatrixView<uint16_t>>, std::shared_ptr<const DenseMatrixView<int32_t>>, std::shared_ptr<const DenseMatrixView<uint32_t>>, std::shared_ptr<const DenseMatrixView<int64_t>>, std::shared_ptr<const DenseMatrixView<uint64_t>>, std::shared_ptr<const DenseMatrixView<float>>, std::shared_ptr<const DenseMatrixView<double>>, std::shared_ptr<const DenseMatrixView<std::complex<float>>>, std::shared_ptr<const DenseMatrixView<std::complex<double>>>>::variant;
};

#endif // MATHPY_MATRIX_DENSE_VIEW_H

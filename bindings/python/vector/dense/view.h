#ifndef MATHPY_VECTOR_DENSE_VIEW_H
#define MATHPY_VECTOR_DENSE_VIEW_H

#include <variant>
#include "mathpp/implementation/vector/dense/view.h"

#include <cstdint>

struct Py_DenseVectorView final : std::variant<std::shared_ptr<const DenseVectorView<int8_t>>, std::shared_ptr<const DenseVectorView<uint8_t>>, std::shared_ptr<const DenseVectorView<int16_t>>, std::shared_ptr<const DenseVectorView<uint16_t>>, std::shared_ptr<const DenseVectorView<int32_t>>, std::shared_ptr<const DenseVectorView<uint32_t>>, std::shared_ptr<const DenseVectorView<int64_t>>, std::shared_ptr<const DenseVectorView<uint64_t>>, std::shared_ptr<const DenseVectorView<float>>, std::shared_ptr<const DenseVectorView<double>>, std::shared_ptr<const DenseVectorView<std::complex<float>>>, std::shared_ptr<const DenseVectorView<std::complex<double>>>>, DenseVectorLikeBase {
    using std::variant<std::shared_ptr<const DenseVectorView<int8_t>>, std::shared_ptr<const DenseVectorView<uint8_t>>, std::shared_ptr<const DenseVectorView<int16_t>>, std::shared_ptr<const DenseVectorView<uint16_t>>, std::shared_ptr<const DenseVectorView<int32_t>>, std::shared_ptr<const DenseVectorView<uint32_t>>, std::shared_ptr<const DenseVectorView<int64_t>>, std::shared_ptr<const DenseVectorView<uint64_t>>, std::shared_ptr<const DenseVectorView<float>>, std::shared_ptr<const DenseVectorView<double>>, std::shared_ptr<const DenseVectorView<std::complex<float>>>, std::shared_ptr<const DenseVectorView<std::complex<double>>>>::variant;
};

#endif // MATHPY_VECTOR_DENSE_VIEW_H

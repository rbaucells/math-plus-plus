#ifndef MATHPY_COMMON_PRECISION_H
#define MATHPY_COMMON_PRECISION_H
#include <cstdint>
#include <variant>
#include "../main.h"
#include "mathpp/implementation/common/precision.h"

using Py_Precision = PyWrapper<std::variant<Precision<int8_t>, Precision<uint8_t>, Precision<int16_t>, Precision<uint16_t>, Precision<int32_t>, Precision<uint32_t>, Precision<int64_t>, Precision<uint64_t>, Precision<float>, Precision<double>>>;

#endif // MATHPY_COMMON_PRECISION_H

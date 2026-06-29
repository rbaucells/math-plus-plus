#ifndef MATHPP_IMPLEMENTATION_MATRIX_COMMON_ASSERTS
#define MATHPP_IMPLEMENTATION_MATRIX_COMMON_ASSERTS

#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/telemetry.h"
#include "traits.h"

template<matrix_like T, matrix_like U, matrix_like... ARGS>
void assert_same_dimensions(const T& a, const U& b, const ARGS&... args) {
    Telemetry::emit_dimension_check();
    if (!(a.columns() == b.columns() && a.rows() == b.rows() && ((a.columns() == args.columns() && a.rows() == args.rows()) && ...))) {
        throw InvalidDimensionException("Provided matrices must all have same dimensions");
    }
}

template<matrix_like T>
void assert_square(const T& m) {
    Telemetry::emit_dimension_check();
    if (m.columns() != m.rows()) {
        throw InvalidDimensionException("Provided matrix must be square");
    }
}

template<matrix_like T>
void assert_wide(const T& m) {
    Telemetry::emit_dimension_check();
    if (m.columns() <= m.rows()) {
        throw InvalidDimensionException("Provided matrix must be wide");
    }
}

template<matrix_like T>
void assert_tall(const T& m) {
    Telemetry::emit_dimension_check();
    if (m.columns() >= m.rows()) {
        throw InvalidDimensionException("Provided matrix must be tall");
    }
}

template<matrix_like T, matrix_like U>
void assert_can_multiply(const T& a, const U& b) {
    Telemetry::emit_dimension_check();
    if (a.columns() != b.rows()) {
        throw InvalidDimensionException("Provided matrices must have matching inner dimensions to multiply (a.columns() == b.rows())");
    }
}

#endif // MATHPP_IMPLEMENTATION_MATRIX_COMMON_ASSERTS

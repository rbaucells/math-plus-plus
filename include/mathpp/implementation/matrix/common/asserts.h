#ifndef MATHPP_IMPLEMENTATION_MATRIX_COMMON_ASSERTS_H
#define MATHPP_IMPLEMENTATION_MATRIX_COMMON_ASSERTS_H

#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/telemetry.h"
#include "traits.h"
#include <ranges>

template<matrix_like T, matrix_like U, matrix_like... ARGS>
void assert_same_dimensions(const T& a, const U& b, const ARGS&... args) {
    Telemetry::emit_dimension_check();
    if (!(a.columns() == b.columns() && a.rows() == b.rows() && ((a.columns() == args.columns() && a.rows() == args.rows()) && ...))) {
        throw InvalidSizeException("Provided matrices must all have same dimensions");
    }
}

template<std::ranges::range R, dense_matrix_like T = std::ranges::range_value_t<R>> requires (dense_matrix_like<std::ranges::range_value_t<R>>)
void assert_same_dimensions(const R& args) {
    Telemetry::emit_dimension_check();

    const std::size_t rows = (*args.begin()).rows();
    const std::size_t columns = (*args.begin()).columns();

    for (const T& m: args) {
        if (m.rows() != rows || m.columns() != columns) {
            throw InvalidSizeException("Provided matrices must all have same dimensions");
        }
    }
}

template<matrix_like T>
void assert_square(const T& m) {
    Telemetry::emit_dimension_check();
    if (m.columns() != m.rows()) {
        throw InvalidSizeException("Provided matrix must be square");
    }
}

template<matrix_like T>
void assert_wide(const T& m) {
    Telemetry::emit_dimension_check();
    if (m.columns() <= m.rows()) {
        throw InvalidSizeException("Provided matrix must be wide");
    }
}

template<matrix_like T>
void assert_tall(const T& m) {
    Telemetry::emit_dimension_check();
    if (m.columns() >= m.rows()) {
        throw InvalidSizeException("Provided matrix must be tall");
    }
}

template<matrix_like T, matrix_like U>
void assert_can_multiply(const T& a, const U& b) {
    Telemetry::emit_dimension_check();
    if (a.columns() != b.rows()) {
        throw InvalidSizeException("Provided matrices must have matching inner dimensions to multiply (a.columns() == b.rows())");
    }
}

#endif // MATHPP_IMPLEMENTATION_MATRIX_COMMON_ASSERTS_H

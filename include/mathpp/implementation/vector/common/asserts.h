#ifndef MATHPP_IMPLEMENTATION_VECTOR_COMMON_ASSERTS_H
#define MATHPP_IMPLEMENTATION_VECTOR_COMMON_ASSERTS_H

#include "mathpp/implementation/common/exceptions.h"
#include "mathpp/implementation/common/telemetry.h"

#include "traits.h"

template<vector_like T, vector_like U, vector_like... ARGS>
inline void assert_same_size(const T& a, const U& b, const ARGS&... args) {
    Telemetry::emit_dimension_check();
    if (!(a.n() == b.n() && ((a.n() == args.n()) && ...))) {
        throw InvalidSizeException("Dense vectors must all be of same size");
    }
}

template<std::ranges::range R, vector_like T = std::ranges::range_value_t<R>> requires (vector_like<std::ranges::range_value_t<R>>)
void assert_same_size(const R& args) {
    Telemetry::emit_dimension_check();

    const std::size_t n = (*args.begin()).n();

    for (const T& v: args) {
        if (v.n() != n) {
            throw InvalidSizeException("Provided vectors must all have same size");
        }
    }
}

#endif // MATHPP_IMPLEMENTATION_VECTOR_COMMON_ASSERTS_H

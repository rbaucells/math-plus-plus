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

#endif // MATHPP_IMPLEMENTATION_VECTOR_COMMON_ASSERTS_H

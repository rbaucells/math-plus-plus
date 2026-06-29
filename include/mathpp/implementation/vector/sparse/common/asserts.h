#ifndef MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_ASSERTS
#define MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_ASSERTS

#include "mathpp/implementation/common/exceptions.h"
#include "traits.h"

template<sparse_vector_like T, sparse_vector_like U, sparse_vector_like... ARGS>
inline void assert_same_size(const T& a, const U& b, const ARGS&... args) {
    if (!(a.n() == b.n() && ((a.n() == args.n()) && ...))) {
        throw InvalidDimensionException("Sparse vectors must all be of same size");
    }
}

#endif // MATHPP_IMPLEMENTATION_VECTOR_SPARSE_COMMON_ASSERTS

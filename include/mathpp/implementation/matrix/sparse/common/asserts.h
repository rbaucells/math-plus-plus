#ifndef MATHPP_IMPLEMENTATION_MATRIX_SPARSE_COMMON_ASSERTS
#define MATHPP_IMPLEMENTATION_MATRIX_SPARSE_COMMON_ASSERTS

#include "mathpp/implementation/common/exceptions.h"

#include "traits.h"

template<sparse_matrix_like T, sparse_matrix_like U, sparse_matrix_like... ARGS>
inline void assert_same_dimensions(const T& a, const U& b, const ARGS&... args) {
    if (!(a.columns() == b.columns() && a.rows() == b.rows() && ((a.columns() == args.columns() && a.rows() == args.rows()) && ...))) {
        throw InvalidDimensionException("Sparse matrices must all have same dimensions");
    }
}

template<sparse_matrix_like T>
inline void assert_square(const T& m) {
    if (m.columns() != m.rows()) {
        throw InvalidDimensionException("Sparse matrix must be square");
    }
}

#endif // MATHPP_IMPLEMENTATION_MATRIX_SPARSE_COMMON_ASSERTS

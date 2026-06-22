#pragma once
#include "mathpp/implementation/common/exceptions.h"

#include "traits.h"

template<vector_like T, vector_like U, vector_like... ARGS>
inline void assert_same_size(const T& a, const U& b, const ARGS&... args) {
    if (!(a.n() == b.n() && ((a.n() == args.n()) && ...))) {
        throw InvalidDimensionException("Dense vectors must all be of same size");
    }
}

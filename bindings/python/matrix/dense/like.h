#ifndef MATHPY_MATRIX_DENSE_LIKE_H
#define MATHPY_MATRIX_DENSE_LIKE_H
#include "../common/like.h"

struct DenseMatrixLikeBase : MatrixLikeBase {
    virtual ~DenseMatrixLikeBase() = default;
};

#endif // MATHPY_MATRIX_DENSE_LIKE_H

#pragma once
#include "matrix.h"

template<int ROWS, int COLUMNS, scalar T>
Vector<COLUMNS - 1, T> Matrix<ROWS, COLUMNS, T>::applyHomogeneousTransformation(const Vector<COLUMNS - 1, T>& point, const T lastElement) const requires (isSquare) {
    Vector<COLUMNS, T> resizedPoint;

    for (int i = 0; i < COLUMNS - 1; i++) {
        resizedPoint[i] = point[i];
    }

    resizedPoint[COLUMNS - 1] = lastElement;

    Vector<COLUMNS, T> transformedPoint = multiply(resizedPoint);

    Vector<COLUMNS - 1, T> result;

    for (int i = 0; i < COLUMNS - 1; i++) {
        result[i] = transformedPoint[i];
    }

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<COLUMNS - 1, std::common_type_t<T, OTHER_T>> Matrix<ROWS, COLUMNS, T>::applyHomogeneousTransformation(const Vector<COLUMNS - 1, OTHER_T>& point, const std::common_type_t<T, OTHER_T> lastElement) const requires (isSquare) {
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> resizedPoint;

    for (int i = 0; i < COLUMNS - 1; i++) {
        resizedPoint[i] = point[i];
    }

    resizedPoint[COLUMNS - 1] = lastElement;

    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> transformedPoint = multiply(resizedPoint);

    Vector<COLUMNS - 1, std::common_type_t<T, OTHER_T>> result;

    for (int i = 0; i < COLUMNS - 1; i++) {
        result[i] = transformedPoint[i];
    }

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::scalingMatrix(const Vector<COLUMNS, T>& factors) requires (isSquare) {
    Matrix<ROWS, COLUMNS, T> matrix;

    for (int c = 0; c < COLUMNS; c++) {
        matrix[c][c] = factors[c];
    }

    return matrix;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::shearMatrix(const int i, const int j, const T k) requires (isSquare) {
    Matrix<ROWS, COLUMNS, T> matrix = identity();

    matrix[j][i] = k;

    return matrix;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::squeezeMatrix(const int i, const int j, const T k) requires (isSquare) {
    Matrix<ROWS, COLUMNS, T> matrix = identity();

    matrix[i][i] = k;
    matrix[j][j] = UnderlyingType(1) / k;

    return matrix;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::rotationMatrixAboutOrigin(const T rot, const RotationType rotationType) requires (isSquare && COLUMNS == 2) {
    T asRadians = convert(rotationType, RotationType::radians, rot);

    T sin = std::sin(asRadians);
    T cos = std::cos(asRadians);

    Matrix<ROWS, COLUMNS, T> rotation;

    rotation[0][0] = cos;
    rotation[1][0] = -sin;
    rotation[0][1] = sin;
    rotation[1][1] = cos;

    return rotation;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS + 1, COLUMNS + 1, T> Matrix<ROWS, COLUMNS, T>::rotationMatrixAboutPoint(const Vector<COLUMNS, T>& p, const T rot, const RotationType rotationType) requires (isSquare && COLUMNS == 2) {
    T asRadians = convert(rotationType, RotationType::radians, rot);

    T sin = std::sin(asRadians);
    T cos = std::cos(asRadians);

    Matrix<ROWS + 1, COLUMNS + 1, T> rotation = Matrix<ROWS + 1, COLUMNS + 1, T>::identity();

    rotation[0][0] = cos;
    rotation[1][0] = -sin;
    rotation[0][1] = sin;
    rotation[1][1] = cos;

    Matrix<ROWS + 1, COLUMNS + 1, T> translationToOrigin = Matrix<ROWS, COLUMNS, T>::translationMatrix(p);
    Matrix<ROWS + 1, COLUMNS + 1, T> translationBack = Matrix<ROWS, COLUMNS, T>::translationMatrix(-p);

    Matrix<ROWS + 1, COLUMNS + 1, T> result = translationToOrigin * rotation * translationBack;

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::rotationMatrixAroundAxisThroughOrigin(const Vector<COLUMNS, T>& axis, const T rot, const RotationType rotationType) requires (isSquare && COLUMNS == 3) {
    T asRadians = convert(rotationType, RotationType::radians, rot);

    T sin = std::sin(asRadians);
    T cos = std::cos(asRadians);

    Matrix<ROWS, COLUMNS, T> crossProductMatrix = axis.crossProductMatrix();

    return identity() + (sin * crossProductMatrix) + (1 - cos) * crossProductMatrix.pow(2);
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS + 1, COLUMNS + 1, T> Matrix<ROWS, COLUMNS, T>::rotationMatrixAroundAxisNotThroughOrigin(const Vector<COLUMNS, T>& axis, const Vector<COLUMNS, T>& p, const T rot, const RotationType rotationType) requires (isSquare && COLUMNS == 3) {
    Matrix<ROWS, COLUMNS, T> smallRotation = rotationMatrixAroundAxisThroughOrigin(axis, rot, rotationType);

    Matrix<ROWS + 1, COLUMNS + 1, T> rotation = Matrix<ROWS + 1, COLUMNS + 1, T>::identity();

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            rotation[c][r] = smallRotation[c][r];
        }
    }

    Matrix<ROWS + 1, COLUMNS + 1, T> translationToOrigin = Matrix<ROWS, COLUMNS, T>::translationMatrix(p);
    Matrix<ROWS + 1, COLUMNS + 1, T> translationBack = Matrix<ROWS, COLUMNS, T>::translationMatrix(-p);

    Matrix<ROWS + 1, COLUMNS + 1, T> result = translationToOrigin * rotation * translationBack;

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::rotationMatrixInPlaneThroughOrigin(const Vector<COLUMNS, T>& v1, const Vector<COLUMNS, T>& v2, const T rot, const RotationType rotationType) requires (isSquare && COLUMNS >= 3) {
    T asRadians = convert(rotationType, RotationType::radians, rot);

    T sin = std::sin(asRadians);
    T cos = std::cos(asRadians);

    auto [n1, n2] = Vector<COLUMNS, T>::template orthonormalize<2>({v1, v2});

    Matrix<ROWS, COLUMNS, T> result = identity() + (n2.outerProductMatrix(v1) - n1.outerProductMatrix(v2)) * sin + (n1.outerProductMatrix(n1) + n2.outerProductMatrix(n2)) * (cos - 1);

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::rotationMatrixInPLaneNotThroughOrigin(const Vector<COLUMNS, T>& v1, const Vector<COLUMNS, T>& v2, const Vector<COLUMNS, T>& p, const T rot, const RotationType rotationType) requires (isSquare && COLUMNS >= 3) {
    Matrix<ROWS, COLUMNS, T> smallRotation = rotationMatrixInPlaneThroughOrigin(v1, v2, rot, rotationType);

    Matrix<ROWS + 1, COLUMNS + 1, T> rotation = Matrix<ROWS + 1, COLUMNS + 1, T>::identity();

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            rotation[c][r] = smallRotation[c][r];
        }
    }

    Matrix<ROWS + 1, COLUMNS + 1, T> translationToOrigin = Matrix<ROWS, COLUMNS, T>::translationMatrix(p);
    Matrix<ROWS + 1, COLUMNS + 1, T> translationBack = Matrix<ROWS, COLUMNS, T>::translationMatrix(-p);

    Matrix<ROWS + 1, COLUMNS + 1, T> result = translationToOrigin * rotation * translationBack;

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::reflectionMatrixAlongAxisThroughOrigin(const Vector<COLUMNS, T>& axis) requires (isSquare) {
    return 2 * axis.outerProduct(axis) - identity();
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS + 1, COLUMNS + 1, T> Matrix<ROWS, COLUMNS, T>::reflectionMatrixAlongAxisNotThroughOrigin(const Vector<COLUMNS, T>& axis, const Vector<COLUMNS, T>& point) requires (isSquare) {
    Matrix<ROWS, COLUMNS, T> reflectionMatrix = reflectionMatrixAlongAxisThroughOrigin(axis);
    Vector<COLUMNS, T> translationVector = (identity() - 2 * axis.outerProduct(axis)) * point;

    Matrix<ROWS + 1, COLUMNS + 1, T> result = Matrix<ROWS + 1, COLUMNS + 1, T>::identity();

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[c][r] = reflectionMatrix[c][r];
        }
    }

    for (int r = 0; r < ROWS; r++) {
        result[COLUMNS][r] = translationVector[r];
    }

    return result;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS + 1, COLUMNS + 1, T> Matrix<ROWS, COLUMNS, T>::translationMatrix(const Vector<COLUMNS, T>& translation) requires (isSquare) {
    Matrix<ROWS + 1, COLUMNS + 1, T> matrix = Matrix<ROWS + 1, COLUMNS + 1, T>::identity();

    for (int r = 0; r < ROWS; r++) {
        matrix[COLUMNS][r] = translation[r];
    }

    return matrix;
}

template<int ROWS, int COLUMNS, scalar T>
Matrix<ROWS, COLUMNS, T> Matrix<ROWS, COLUMNS, T>::orthoMatrix(const T left, const T right, const T bottom, const T top, const T near, const T far) requires (isSquare && COLUMNS == 4) {
    // identity
    Matrix<ROWS, COLUMNS, T> transformation = Matrix<ROWS, COLUMNS, T>::identity();
    // transformation
    transformation.data[0][0] = 2 / (right - left);
    transformation.data[1][1] = 2 / (top - bottom);
    transformation.data[2][2] = -2 / (far - near);
    transformation.data[3][0] = -(right + left) / (right - left);
    transformation.data[3][1] = -(top + bottom) / (top - bottom);
    transformation.data[3][2] = -(far + near) / (far - near);
    // return
    return transformation;
}

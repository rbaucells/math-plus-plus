#pragma once

#include <cassert>
#include <complex>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include "helper.h"
#include "vector.h"

template<int COLUMNS, int ROWS, is_scalar_v T>
struct Matrix;

template<typename T>
struct is_matrix : std::false_type {};

template<int COLUMNS, int ROWS, is_scalar_v T>
struct is_matrix<Matrix<COLUMNS, ROWS, T>> : std::true_type {};

template<typename T>
concept is_matrix_v = is_matrix<T>::value;

template<int COLUMNS, int ROWS, is_scalar_v T = float>
struct Matrix {
    static constexpr int columns = COLUMNS;
    static constexpr int rows = ROWS;

    static constexpr bool isSquare = ROWS == COLUMNS;
    static constexpr bool isComplex = is_complex_v<T>;

    static constexpr T epsilon = ::epsilon<T>();

    T data[COLUMNS][ROWS] = {};

    Matrix() = default;

    constexpr Matrix(std::initializer_list<std::initializer_list<T>> initializerList) {
        int r = 0;
        for (const auto& row : initializerList) {
            int c = 0;

            for (const auto element : row) {
                data[c][r] = element;
                c++;
            }

            r++;
        }
    }

    // copy constructor with same type
    Matrix(const Matrix<COLUMNS, ROWS, T>& other) {
        memcpy(data, other.data, sizeof(T) * ROWS * COLUMNS);
    }

    // copy constructor with different type
    template<is_convertable_to<T> OTHER_T>
    Matrix(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] = other.data[c][r];
            }
        }
    }

    // m = m
    Matrix<COLUMNS, ROWS, T>& operator=(const Matrix<COLUMNS, ROWS, T>& other) {
        if (this != &other) {
            memcpy(data, other.data, sizeof(T) * COLUMNS * ROWS);
        }

        return *this;
    }

    // m == m
    bool equals(const Matrix<COLUMNS, ROWS, T>& other) const {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], other.data[c][r]))
                    return false;
            }
        }

        return true;
    }

    bool operator==(const Matrix<COLUMNS, ROWS, T>& other) const {
        return equals(other);
    }

    // m + m
    Matrix<COLUMNS, ROWS, T> add(const Matrix<COLUMNS, ROWS, T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] + other.data[c][r];
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> operator+(const Matrix<COLUMNS, ROWS, T>& other) const {
        return add(other);
    }

    // m - m
    Matrix<COLUMNS, ROWS, T> subtract(const Matrix<COLUMNS, ROWS, T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] - other.data[c][r];
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> operator-(const Matrix<COLUMNS, ROWS, T>& other) const {
        return subtract(other);
    }

    // m * m
    template<int OTHER_COLUMNS>
    Matrix<OTHER_COLUMNS, ROWS, T> multiply(const Matrix<OTHER_COLUMNS, COLUMNS, T>& other) const {
        Matrix<OTHER_COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                for (int x = 0; x < COLUMNS; x++) {
                    result[c][r] += data[x][r] * other.data[c][x];
                }
            }
        }

        return result;
    }

    template<int OTHER_COLUMNS>
    Matrix<OTHER_COLUMNS, ROWS, T> operator*(const Matrix<OTHER_COLUMNS, COLUMNS, T>& other) const {
        return multiply(other);
    }

    // m * v
    Vector<COLUMNS, T> multiply(const Vector<COLUMNS, T>& other) const {
        Vector<COLUMNS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[r] += data[c][r] * other[c];
            }
        }

        return result;
    }

    Vector<COLUMNS, T> operator*(const Vector<COLUMNS, T>& other) const {
        return multiply(other);
    }

    // m * #
    Matrix<COLUMNS, ROWS, T> multiply(const T val) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] * val;
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> operator*(const T val) const {
        return multiply(val);
    }

    // m / #
    Matrix<COLUMNS, ROWS, T> divide(const T scalar) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] / scalar;
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> operator/(const T scalar) const {
        return divide(scalar);
    }

    // m += m
    Matrix<COLUMNS, ROWS, T>& addEquals(const Matrix<COLUMNS, ROWS, T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] += other.data[c][r];
            }
        }

        return *this;
    }

    Matrix<COLUMNS, ROWS, T>& operator+=(const Matrix<COLUMNS, ROWS, T>& other) {
        return addEquals(other);
    }

    // m -= m
    Matrix<COLUMNS, ROWS, T>& subtractEquals(const Matrix<COLUMNS, ROWS, T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] -= other.data[c][r];
            }
        }

        return *this;
    }

    Matrix<COLUMNS, ROWS, T> operator-=(const Matrix<COLUMNS, ROWS, T>& other) {
        return subtractEquals(other);
    }

    // m *= #
    Matrix<COLUMNS, ROWS, T>& multiplyEquals(const T val) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] *= val;
            }
        }

        return *this;
    }

    Matrix<COLUMNS, ROWS, T>& operator*=(const T val) const {
        return multiplyEquals(val);
    }

    // m /= #
    Matrix<COLUMNS, ROWS, T>& divideEquals(const T scalar) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] /= scalar;
            }
        }

        return *this;
    }

    Matrix<COLUMNS, ROWS, T>& operator/=(const T scalar) {
        return divideEquals(scalar);
    }

    // m = m
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator=(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        if (static_cast<void*>(this) != static_cast<void*>(&other)) {
            for (int c = 0; c < COLUMNS; c++) {
                for (int r = 0; r < ROWS; r++) {
                    data[c][r] = other.data[c][r];
                }
            }
        }

        return *this;
    }

    // m == m
    template<is_convertable_to<T> OTHER_T>
    bool equals(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], other.data[c][r]))
                    return false;
            }
        }

        return true;
    }

    template<is_convertable_to<T> OTHER_T>
    bool operator==(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        return equals(other);
    }

    // m + m
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> add(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] + other.data[c][r];
            }
        }

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator+(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        return add(other);
    }

    // m - m
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> subtract(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] - other.data[c][r];
            }
        }

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator-(const Matrix<COLUMNS, ROWS, OTHER_T>& other) const {
        return subtract(other);
    }

    // m * m
    template<int OTHER_COLUMNS, is_convertable_to<T> OTHER_T>
    Matrix<OTHER_COLUMNS, ROWS, T> multiply(const Matrix<OTHER_COLUMNS, COLUMNS, OTHER_T>& other) const {
        Matrix<OTHER_COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                for (int x = 0; x < COLUMNS; x++) {
                    result[c][r] += data[x][r] * other.data[c][x];
                }
            }
        }

        return result;
    }

    template<int OTHER_COLUMNS, is_convertable_to<T> OTHER_T>
    Matrix<OTHER_COLUMNS, ROWS, T> operator*(const Matrix<OTHER_COLUMNS, COLUMNS, OTHER_T>& other) const {
        return multiply(other);
    }

    // m * v
    template<is_convertable_to<T> OTHER_T>
    Vector<COLUMNS, T> multiply(const Vector<COLUMNS, OTHER_T>& other) const {
        Vector<COLUMNS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[r] += data[c][r] * other[c];
            }
        }

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<COLUMNS, T> operator*(const Vector<COLUMNS, OTHER_T>& other) const {
        return multiply(other);
    }

    // m * #
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> multiply(const OTHER_T val) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] * val;
            }
        }

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator*(const OTHER_T val) const {
        return multiply(val);
    }

    // m / #
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> divide(const OTHER_T scalar) const {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = data[c][r] / scalar;
            }
        }

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator/(const OTHER_T scalar) const {
        return divide(scalar);
    }

    // m += m
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& addEquals(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] += other.data[c][r];
            }
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator+=(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        return addEquals(other);
    }

    // m -= m
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& subtractEquals(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] -= other.data[c][r];
            }
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T> operator-=(const Matrix<COLUMNS, ROWS, OTHER_T>& other) {
        return subtractEquals(other);
    }

    // m *= #
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& multiplyEquals(const OTHER_T val) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] *= val;
            }
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator*=(const OTHER_T val) const {
        return multiplyEquals(val);
    }

    // m /= #
    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& divideEquals(const OTHER_T scalar) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] /= scalar;
            }
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Matrix<COLUMNS, ROWS, T>& operator/=(const OTHER_T scalar) {
        return divideEquals(scalar);
    }

    template<int N>
    Vector<N, T> applyHomogeneousTransformation(const Vector<N, T>& point) const requires (isSquare) {
        Vector<COLUMNS, T> resizedPoint;

        for (int i = 0; i < N; i++) {
            resizedPoint[i] = point[i];
        }

        Vector<COLUMNS, T> transformedPoint = multiply(resizedPoint);

        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = transformedPoint[i];
        }

        return result;
    }

    template<int N, is_convertable_to<T> OTHER_T>
    Vector<N, T> applyHomogeneousTransformation(const Vector<N, OTHER_T>& point) const requires (isSquare) {
        Vector<COLUMNS, T> resizedPoint;

        for (int i = 0; i < N; i++) {
            resizedPoint[i] = point[i];
        }

        Vector<COLUMNS, T> transformedPoint = multiply(resizedPoint);

        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = transformedPoint[i];
        }

        return result;
    }

    // subscript
    T* operator[](const int index) {
        return &data[index][0];
    }

    // const subscript
    const T* operator[](const int index) const {
        return &data[index][0];
    }

    Matrix<ROWS, COLUMNS, T> transpose() const {
        Matrix<ROWS, COLUMNS, T> result;

        for (int c = 0; c < ROWS; c++) {
            for (int r = 0; r < COLUMNS; r++) {
                result[c][r] = data[r][c];
            }
        }

        return result;
    }

    Matrix<ROWS, COLUMNS, T> conjugateTranspose() const {
        if constexpr (!isComplex) {
            return transpose();
        }

        Matrix<ROWS, COLUMNS, T> result;

        for (int c = 0; c < ROWS; c++) {
            for (int r = 0; r < COLUMNS; r++) {
                result[c][r] = std::conj(data[r][c]);
            }
        }

        return result;
    }

    Matrix<COLUMNS, ROWS, T> inverse() const requires (isSquare) {
        if constexpr (ROWS == 1) { // its a one by one, we can just return 1 / value
            if (compare(data[0][0], 0)) {
                throw std::runtime_error("Cannot find inverse of singular matrix");
            }

            Matrix<1, 1, T> result;

            result[0][0] = 1 / data[0][0];
            return result;
        }
        else if constexpr (ROWS == 2) { // its a two by two, we can do the special fast thing
            T det = determinant();

            if (compare(det, 0)) {
                throw std::runtime_error("Cannot find inverse of singular matrix");
            }

            Matrix<2, 2, T> result;

            result[0][0] = data[1][1] / det;
            result[0][1] = -data[0][1] / det;
            result[1][0] = -data[1][0] / det;
            result[1][1] = data[0][0] / det;

            return result;
        }
        else {
            Matrix<COLUMNS, ROWS, T> left = *this;
            Matrix<COLUMNS, ROWS, T> right = identity();

            for (int c = 0; c < COLUMNS; c++) {
                // handle row swaps for performance
                int rowIndex = -1;
                T value = left[c][c];

                // only check for rows to swap with below main diagonal
                for (int i = c; i < ROWS; i++) {
                    T norm = std::norm(left[c][i]);

                    if (norm > value) {
                        value = norm;
                        rowIndex = i;
                    }
                }

                // if we didnt swap, but needed to have
                if (rowIndex == -1 && compare(value, 0))
                    throw std::runtime_error("Cannot find inverse of singular matrix");

                // swap if we can
                if (rowIndex != -1) {
                    left = left.swapRows(c, rowIndex);
                    right = right.swapRows(c, rowIndex);
                }

                {
                    // normalize pivot row
                    T pivot = left[c][c];
                    for (int cc = c; cc < COLUMNS; cc++) {
                        left[cc][c] /= pivot;
                        right[cc][c] /= pivot;
                    }
                }

                for (int r = 0; r < ROWS; r++) {
                    if (c == r)
                        continue;

                    T multiplierToPivotRow = left[c][r];
                    for (int i = c; i < COLUMNS; i++) {
                        left[i][r] += -multiplierToPivotRow * left[i][c];
                        right[i][r] += -multiplierToPivotRow * left[i][c];
                    }
                }
            }

            return right;
        }
    }

    enum DeterminantAlgorithm {
        laplace,
        triangular,
        hessenberg
    };

    T determinant(const DeterminantAlgorithm algorithm = laplace) const requires (isSquare) {
        if constexpr (COLUMNS == 1) {
            return data[0][0];
        }
        else if constexpr (COLUMNS == 2) {
            // ad - bc
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        else if constexpr (COLUMNS == 3) {
            // aei + bfg + cdh - ceg - bdi - afh
            return (data[0][0] * data[1][1] * data[2][2]) + (data[1][0] * data[2][1] * data[0][2]) + (data[2][0] * data[0][1] * data[1][2]) - (data[2][0] * data[1][1] * data[0][2]) - (data[1][0] * data[0][1] * data[2][2]) - (data[0][0] * data[2][1] * data[1][2]);
        }

        switch (algorithm) {
            case triangular:
                return triangularDeterminant();
            case hessenberg:
                return 0;
            default:
                return laplaceDeterminant();
        }
    }

private:
    T laplaceDeterminant() const requires (isSquare) {
        T result = {};
        int sign = 1;

        for (int c = 0; c < COLUMNS; c++) {
            Matrix<COLUMNS - 1, ROWS - 1, T> insideMatrix = removeColumnsAndRows({c}, {0});

            result += sign * data[c][0] * insideMatrix.determinant();
            sign *= -1;
        }

        return result;
    }

    T triangularDeterminant() const requires (isSquare) {
        T result = {};

        for (int i = 0; i < COLUMNS; i++) {
            result *= data[i][i];
        }

        return result;
    }

public:
    static Matrix<COLUMNS, ROWS, T> scalingMatrix(const Vector<COLUMNS, T>& factors) requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> matrix;

        for (int c = 0; c < COLUMNS; c++) {
            matrix[c][c] = factors[c];
        }

        return matrix;
    }

    static Matrix<COLUMNS, ROWS, T> shearMatrix(const int i, const int j, const T k) requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> matrix = identity();

        matrix[j][i] = k;

        return matrix;
    }

    static Matrix<COLUMNS, ROWS, T> squeezeMatrix(const int i, const int j, const T k) requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> matrix = identity();

        matrix[i][i] = k;
        matrix[j][j] = 1 / k;

        return matrix;
    }

    static Matrix<COLUMNS, ROWS, T> rotationMatrixAboutOrigin(const T rot, const RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 2) {
        T asRadians = convert(rotationType, RotationType::radians, rot);

        T sin = std::sin(asRadians);
        T cos = std::cos(asRadians);

        Matrix<COLUMNS, ROWS, T> r;

        r[0][0] = cos;
        r[1][0] = -sin;
        r[0][1] = sin;
        r[1][1] = cos;

        return r;
    }

    static Matrix<COLUMNS + 1, ROWS + 1, T> rotationMatrixAboutPoint(const Vector<COLUMNS, T>& p, const T rot, const RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 2) {
        Matrix<COLUMNS, ROWS, T> rotationMatrix = rotationMatrixAboutOrigin(rot, rotationType);
        Vector<COLUMNS, T> translationVector = (identity() - rotationMatrix) * p;

        Matrix<COLUMNS + 1, ROWS + 1, T> result = Matrix<COLUMNS + 1, ROWS + 1, T>::identity();

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = rotationMatrix[c][r];
            }
        }

        for (int r = 0; r < ROWS; r++) {
            result[COLUMNS][r] = translationVector[r];
        }

        return result;
    }

    static Matrix<COLUMNS, ROWS, T> rotationMatrixAroundAxisThroughOrigin(const Vector<COLUMNS, T>& axis, const T rot, const RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 3) {
        T asRadians = convert(rotationType, RotationType::radians, rot);

        T sin = std::sin(asRadians);
        T cos = std::cos(asRadians);

        Matrix<COLUMNS, ROWS, T> r = identity() * cos + (1 - cos) * axis.outerProduct(axis) + axis.crossProductMatrix() * sin;

        return r;
    }

    static Matrix<COLUMNS + 1, ROWS + 1, T> rotationMatrixAroundAxisNotThroughOrigin(const Vector<COLUMNS, T>& axis, const Vector<COLUMNS, T>& point, const T rot, const RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS == 3) {
        Vector<COLUMNS, T> u = axis.normalize();

        Matrix<COLUMNS, ROWS, T> rotationMatrix = rotationMatrixAroundAxisThroughOrigin(u, rot, rotationType);
        Vector<COLUMNS, T> translationVector = (identity() - rotationMatrix) * point;

        Matrix<COLUMNS + 1, ROWS + 1, T> result = Matrix<COLUMNS + 1, ROWS + 1, T>::identity();

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = rotationMatrix[c][r];
            }
        }

        for (int r = 0; r < ROWS; r++) {
            result[COLUMNS][r] = translationVector[r];
        }

        return result;
    }

    static Matrix<COLUMNS, ROWS, T> rotationMatrixInPlaneThroughOrigin(const Vector<COLUMNS, T>& v1, const Vector<COLUMNS, T>& v2, const T rot, const RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS >= 3) {
        T asRadians = convert(rotationType, RotationType::radians, rot);

        T sin = std::sin(asRadians);
        T cos = std::cos(asRadians);

        auto orthonormalized = Vector<COLUMNS, T>::orthonormalize({v1, v2});

        Vector<COLUMNS, T> u = orthonormalized[0];
        Vector<COLUMNS, T> v = orthonormalized[1];

        Matrix<COLUMNS, ROWS, T> r = identity() + (cos - 1) * (u.outerProduct(u) + v.outerProduct(v)) + sin * (v.outerProduct(u) - u.outerProduct(v));

        return r;
    }

    static Matrix<COLUMNS, ROWS, T> rotationMatrixInPLaneNotThroughOrigin(const Vector<COLUMNS, T>& v1, const Vector<COLUMNS, T>& v2, const Vector<COLUMNS, T>& point, const T rot, const RotationType rotationType = RotationType::radians) requires (isSquare && COLUMNS >= 3) {
        auto orthonormalized = Vector<COLUMNS, T>::orthonormalize({v1, v2});

        Vector<COLUMNS, T> u = orthonormalized[0];
        Vector<COLUMNS, T> v = orthonormalized[1];

        Matrix<COLUMNS, ROWS, T> rotationMatrix = rotationMatrixInPlaneThroughOrigin(u, v, rot, rotationType);

        Vector<COLUMNS, T> translationVector = (identity() - rotationMatrix) * point;

        Matrix<COLUMNS + 1, ROWS + 1, T> result = Matrix<COLUMNS + 1, ROWS + 1, T>::identity();

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = rotationMatrix[c][r];
            }
        }

        for (int r = 0; r < ROWS; r++) {
            result[COLUMNS][r] = translationVector[r];
        }

        return result;
    }

    static Matrix<COLUMNS, ROWS, T> reflectionMatrixAlongAxisThroughOrigin(const Vector<COLUMNS, T>& axis) requires (isSquare) {
        return 2 * axis.outerProduct(axis) - identity();
    }

    static Matrix<COLUMNS + 1, ROWS + 1, T> reflectionMatrixAlongAxisNotThroughOrigin(const Vector<COLUMNS, T>& axis, const Vector<COLUMNS, T>& point) requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> reflectionMatrix = reflectionMatrixAlongAxisThroughOrigin(axis);
        Vector<COLUMNS, T> translationVector = (identity() - 2 * axis.outerProduct(axis)) * point;

        Matrix<COLUMNS + 1, ROWS + 1, T> result = Matrix<COLUMNS + 1, ROWS + 1, T>::identity();

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

    static Matrix<COLUMNS + 1, ROWS + 1, T> translationMatrix(const Vector<COLUMNS, T>& translation) requires (isSquare) {
        Matrix<COLUMNS + 1, ROWS + 1, T> matrix = Matrix<COLUMNS + 1, ROWS + 1, T>::identity();

        for (int r = 0; r < ROWS; r++) {
            matrix[COLUMNS][r] = translation[r];
        }

        return matrix;
    }

    static Matrix<COLUMNS, ROWS, T> orthoMatrix(const T left, const T right, const T bottom, const T top, const T near, const T far) requires (isSquare && COLUMNS == 4) {
        // identity
        Matrix<COLUMNS, ROWS, T> transformation = Matrix<COLUMNS, ROWS, T>::identity();
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

    std::string toString() const {
        std::stringstream ss;
        ss.precision(2);

        ss << "[";

        for (int r = 0; r < ROWS; r++) {
            ss << "[";
            for (int c = 0; c < COLUMNS; c++) {
                ss << data[c][r];

                if (c < COLUMNS - 1)
                    ss << ", ";
            }

            ss << "]";

            if (r < ROWS - 1)
                ss << ", ";
        }

        ss << "]";
        return ss.str();
    }

    std::string toLaTex() const {
        std::stringstream ss;
        ss.precision(2);

        ss << "\\begin{bmatrix}";

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLUMNS; c++) {
                ss << data[c][r];

                if (c < COLUMNS - 1)
                    ss << " & ";
            }

            if (r < ROWS - 1)
                ss << "\\\\";
        }

        ss << "\\end{bmatrix}";
        return ss.str();
    }

    template<int NUM_COLUMNS_TO_REMOVE>
    Matrix<COLUMNS - NUM_COLUMNS_TO_REMOVE, ROWS, T> removeColumns(const std::array<int, NUM_COLUMNS_TO_REMOVE>& columnsToRemove) const {
        Matrix<COLUMNS - NUM_COLUMNS_TO_REMOVE, ROWS, T> m;

        for (int c = 0; c < COLUMNS; c++) {
            if (std::find(columnsToRemove.begin(), columnsToRemove.end(), c))
                continue;

            for (int r = 0; r < ROWS; r++) {
                m[c][r] = data[c][r];
            }
        }

        return m;
    }

    template<int NUM_ROWS_TO_REMOVE>
    Matrix<COLUMNS, ROWS - NUM_ROWS_TO_REMOVE, T> removeRows(const std::array<int, NUM_ROWS_TO_REMOVE>& rowsToRemove) const {
        Matrix<COLUMNS, ROWS - NUM_ROWS_TO_REMOVE, T> m;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (std::find(rowsToRemove.begin(), rowsToRemove.end(), r))
                    continue;

                m[c][r] = data[c][r];
            }
        }

        return m;
    }

    template<int NUM_COLUMNS_TO_REMOVE, int NUM_ROWS_TO_REMOVE>
    Matrix<COLUMNS - NUM_COLUMNS_TO_REMOVE, ROWS - NUM_ROWS_TO_REMOVE, T> removeColumnsAndRows(const std::array<int, NUM_COLUMNS_TO_REMOVE>& columnsToRemove, const std::array<int, NUM_ROWS_TO_REMOVE>& rowsToRemove) const {
        Matrix<COLUMNS, ROWS - NUM_ROWS_TO_REMOVE, T> m;

        for (int c = 0; c < COLUMNS; c++) {
            if (std::find(columnsToRemove.begin(), columnsToRemove.end(), c))
                continue;

            for (int r = 0; r < ROWS; r++) {
                if (std::find(rowsToRemove.begin(), rowsToRemove.end(), r))
                    continue;

                m[c][r] = data[c][r];
            }
        }

        return m;
    }

    Matrix<COLUMNS, ROWS, T> swapRows(const int rowA, const int rowB) {
        Matrix<COLUMNS, ROWS, T> m = *this;

        T temp[COLUMNS] = {};

        for (int c = 0; c < COLUMNS; c++) {
            temp[c] = m[c][rowA];
        }

        for (int c = 0; c < COLUMNS; c++) {
            m[c][rowA] = m[c][rowB];
        }

        for (int c = 0; c < COLUMNS; c++) {
            m[c][rowB] = temp[c];
        }

        return m;
    }

    Matrix<COLUMNS, ROWS, T> swapColumns(const int columnA, const int columnB) {
        Matrix<COLUMNS, ROWS, T> m = *this;

        T temp[ROWS] = {};

        for (int r = 0; r < ROWS; r++) {
            temp[r] = m[columnA][r];
        }

        for (int r = 0; r < COLUMNS; r++) {
            m[columnA][r] = m[columnB][r];
        }

        for (int r = 0; r < COLUMNS; r++) {
            m[columnB][r] = temp[r];
        }

        return m;
    }

    explicit operator const T*() const {
        return &data[0][0];
    }

    explicit operator T*() {
        return &data[0][0];
    }

    static Matrix<COLUMNS, ROWS, T> identity() requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> result;

        for (int i = 0; i < COLUMNS; i++) {
            result[i][i] = 1;
        }

        return result;
    }

    bool isRowEchelon(bool pivotMustBeOne = false) const {
        int lastPivotColumn = -1;

        for (int r = 0; r < ROWS; r++) {
            bool foundNonZero = false;

            for (int c = 0; c < COLUMNS; c++) {
                // this is a pivot
                if (!foundNonZero && !compare(data[c][r], 0)) {
                    // this is to the left of the last pivot
                    if (c < lastPivotColumn)
                        return false;

                    // the pivot must be one and it isn't
                    if (!compare(data[c][r], 1) && pivotMustBeOne)
                        return false;

                    lastPivotColumn = c;
                }

                if (!compare(data[c][r], 0))
                    foundNonZero = true;
            }

            // this entire row was zeros, and this wasn't the last row
            if (!foundNonZero || r != ROWS - 1) {
                return false;
            }
        }

        return true;
    }

    Matrix<COLUMNS, ROWS, T> toRowEchelon() const {
        Matrix<COLUMNS, ROWS, T> m = *this;

        for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
            // handle row swaps
            {
                int rowIndex = -1;
                const T pivot = m[c][c];
                T rowValue = std::abs(pivot);

                // iterate through rows of this column. Looking for the biggest boi
                for (int r = c + 1; r < ROWS; r++) {
                    T curValue = std::abs(m[c][r]);

                    if (curValue > rowValue) {
                        rowIndex = r;
                        rowValue = curValue;
                    }
                }

                // we found nothing so we skip this column
                if (rowIndex == -1 && compare(pivot, 0)) {
                    continue;
                }

                if (rowIndex != -1 && rowIndex != c) {
                    // swap u and p rows like normal
                    m.swapRows(c, rowIndex);
                }
            }

            const T pivot = m[c][c];

            // iterate through things beneath that pivot in the matrix
            for (int r = c + 1; r < ROWS; r++) {
                T val = m[c][r];

                T multiplierToPivotRow = val / pivot;

                // do this row minus other row times multiplier
                for (int i = c; i < COLUMNS; i++) {
                    m[i][r] += -multiplierToPivotRow * m[i][c];
                }
            }
        }

        return m;
    }

    bool isReducedRowEchelon() const {
        int lastPivotColumn = -1;

        for (int r = 0; r < ROWS; r++) {
            bool foundNonZero = false;

            for (int c = 0; c < COLUMNS; c++) {
                // this is a pivot
                if (!foundNonZero && !compare(data[c][r], 0)) {
                    // this is to the left of the last pivot
                    if (c < lastPivotColumn)
                        return false;

                    // the pivot isn't 1
                    if (!compare(data[c][r], 1))
                        return false;

                    // check that no other number in that column is a nonzero value
                    for (int i = 0; i < ROWS; i++) {
                        if (!compare(data[c][i], 0) && !compare(data[c][i], data[c][r]))
                            return false;
                    }

                    lastPivotColumn = c;
                }

                if (!compare(data[c][r], 0))
                    foundNonZero = true;
            }

            // this entire row was zeros, and this wasn't the last row
            if (!foundNonZero || r != ROWS - 1) {
                return false;
            }
        }

        return true;
    }

    Matrix<COLUMNS, ROWS, T> toReducedRowEchelon() const {
        Matrix<COLUMNS, ROWS, T> m = *this;

        for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
            // handle row swaps
            {
                int rowIndex = -1;
                const T pivot = m[c][c];
                T rowValue = std::abs(pivot);

                // iterate through rows of this column. Looking for the biggest boi
                for (int r = c + 1; r < ROWS; r++) {
                    T curValue = std::abs(m[c][r]);

                    if (curValue > rowValue) {
                        rowIndex = r;
                        rowValue = curValue;
                    }
                }

                // we found nothing so we skip this column
                if (rowIndex == -1 && compare(pivot, 0)) {
                    continue;
                }

                if (rowIndex != -1 && rowIndex != c) {
                    // swap u and p rows like normal
                    m.swapRows(c, rowIndex);
                }
            }

            {
                // normalize pivot row to 1
                T value = m[c][c];
                for (int cc = c + 1; cc < COLUMNS; cc++) {
                    m[cc][c] /= value;
                }
                m[c][c] = 1;
            }

            const T pivot = m[c][c];

            // iterate through things beneath that pivot in the matrix
            for (int r = c + 1; r < ROWS; r++) {
                T val = m[c][r];

                T multiplierToPivotRow = val / pivot;

                // do this row minus other row times multiplier
                for (int i = c; i < COLUMNS; i++) {
                    m[i][r] += -multiplierToPivotRow * m[i][c];
                }
            }
        }

        return m;
    }

    int rank() const {
        Matrix<COLUMNS, ROWS, T> ref = toRowEchelon();
        int result = 0;

        for (int r = 0; r < ROWS; r++) {
            if (!compare(ref[0][r], 0)) {
                result++;
            }
            else {
                bool nonZero = false;

                for (int c = 0; c < COLUMNS; c++) {
                    if (!compare(ref[c][r], 0)) {
                        nonZero = true;
                        break;
                    }
                }

                if (nonZero)
                    result++;
            }
        }

        return result;
    }

    bool isSymmetrical() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], data[r][c]))
                    return false;
            }
        }

        return true;
    }

    bool isSkewSymmetrical() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], -data[r][c]))
                    return false;
            }
        }

        return true;
    }

    bool isHermitian() const requires (isSquare) {
        if constexpr (!isComplex)
            return isSymmetrical();

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], std::conj(data[r][c]))) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isSkewHermitian() const requires (isSquare) {
        if constexpr (!isComplex)
            return isSkewSymmetrical();

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (!compare(data[c][r], -std::conj(data[r][c])))
                    return false;
            }
        }

        return true;
    }

    bool isPositiveDefinite() const requires (isSquare) {
        // TODO:
    }

    bool isPositiveSemiDefinite() const requires (isSquare) {
        // TODO:
    }

    bool isNegativeDefinite() const requires (isSquare) {
        // TODO:
    }

    bool isNegativeSemiDefinite() const requires (isSquare) {
        // TODO:
    }

    Vector<ROWS, T> getColumnVector(const int i) const {
        Vector<ROWS, T> v;

        for (int j = 0; j < ROWS; j++) {
            v[j] = data[i][j];
        }

        return v;
    }

    std::array<Vector<ROWS>, COLUMNS> getColumnVectors() const {
        std::array<Vector<ROWS>, COLUMNS> vecs;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                vecs[c][r] = data[c][r];
            }
        }

        return vecs;
    }

    Vector<COLUMNS, T> getRowVector(const int i) const {
        Vector<COLUMNS, T> v;

        for (int j = 0; j < COLUMNS; j++) {
            v[j] = data[j][i];
        }

        return v;
    }

    std::array<Vector<COLUMNS>, ROWS> getRowVectors() const {
        std::array<Vector<COLUMNS>, ROWS> vecs;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLUMNS; c++) {
                vecs[r][c] = data[c][r];
            }
        }

        return vecs;
    }

    void setColumnVectors(const std::array<Vector<ROWS, T>, COLUMNS>& columnVectors) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] = columnVectors[c][r];
            }
        }
    }

    void setColumnVector(const int i, const Vector<ROWS, T>& v) {
        for (int j = 0; j < ROWS; j++) {
            data[i][j] = v[j];
        }
    }

    void setRowVectors(const std::array<Vector<COLUMNS, T>, ROWS> rowVectors) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                data[c][r] = rowVectors[r][c];
            }
        }
    }

    void setRowVector(const int i, const Vector<COLUMNS, T>& v) {
        for (int j = 0; j < COLUMNS; j++) {
            data[j][i] = v[j];
        }
    }

    T trace() const requires (isSquare) {
        T sum = {};

        for (int c = 0; c < COLUMNS; c++) {
            sum += data[c][c];
        }

        return sum;
    }

    bool isUnitary() const requires (isSquare) {
        // TODO:
    }

    bool isSpecialUnitary() const requires (isSquare) {
        // TODO:
    }

    bool isOrthogonal() const requires (!isComplex && isSquare) {
        // TODO:
    }

    bool isSpecialOrthogonal() const requires (!isComplex && isSquare) {
        // TODO:
    }

    bool isUpperTriangleMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            // dont worry about out of bounds, loop wont even run if c + 1 is too big
            for (int r = c + 1; r < ROWS; r++) {
                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isLowerTriangleMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < c; r++) {
                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isDiagonalMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                if (c == r)
                    continue;

                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isUpperUnitriangularMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = c; r < ROWS; r++) {
                if (c == r) {
                    if (!compare(data[c][r], 1)) {
                        return false;
                    }
                }
                else if (!compare(data[c][r], 0)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isLowerUnitriangularMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r <= c; r++) {
                if (c == r) {
                    if (!compare(data[c][r], 1)) {
                        return false;
                    }
                }
                else if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isStrictlyUpperTriangularMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = c; r < ROWS; r++) {
                if (!compare(data[c][r], 0)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool isStrictlyLowerTriangularMatrix() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r <= c; r++) {
                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isFrobeniusMatrix() const requires (isSquare) {
        int columnWithNonZero = -1;
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                // not a one on diagonal
                if (c == r && !compare(data[c][r], 1)) {
                    return false;
                }
                if (!compare(data[c][r], 0)) {
                    // its above
                    if (r <= c)
                        return false;

                    // too many columns with nonzero
                    if (columnWithNonZero != c)
                        return false;

                    columnWithNonZero = c;
                }
            }
        }

        return true;
    }

    template<typename L_TYPE, typename U_TYPE, typename P_TYPE>
    struct LUPDecomposition {
        L_TYPE l;
        U_TYPE u;
        P_TYPE p;
    };

    LUPDecomposition<Matrix<std::min(ROWS, COLUMNS), ROWS, T>, Matrix<COLUMNS, std::min(ROWS, COLUMNS), T>, Matrix<ROWS, ROWS, T>> lupDecomposition() const {
        Matrix<std::min(ROWS, COLUMNS), ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
        Matrix<COLUMNS, std::min(ROWS, COLUMNS), T> u = *this;
        Matrix<ROWS, ROWS, T> p = Matrix<ROWS, ROWS, T>::identity();

        // use std::min so we never access the pivot that's out of the matrix
        for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
            // handle row swaps
            {
                int rowIndex = -1;
                const T pivot = u[c][c];
                T rowValue = std::abs(pivot);

                // iterate through rows of this column. Looking for the biggest boi
                for (int r = c + 1; r < ROWS; r++) {
                    T curValue = std::abs(u[c][r]);

                    if (curValue > rowValue) {
                        rowIndex = r;
                        rowValue = curValue;
                    }
                }

                // we found nothing but we needed to find something
                if (rowIndex == -1 && compare(pivot, 0)) {
                    throw std::runtime_error("Cannot LUP decompose singular matrix");
                }

                if (rowIndex != -1) {
                    // swap u and p rows like normal
                    u.swapRows(c, rowIndex);
                    p.swapRows(c, rowIndex);

                    // swap rows of l before column c
                    for (int i = 0; i < c; ++i) {
                        T temp = l[i][c];
                        l[i][c] = l[i][rowIndex];
                        l[i][rowIndex] = temp;
                    }
                }
            }

            T pivot = u[c][c];

            // iterate through things beneath that pivot in the matrix
            for (int r = c + 1; r < ROWS; r++) {
                T val = u[c][r];

                T multiplierToPivotRow = val / pivot;

                l[c][r] = multiplierToPivotRow;

                // do this row minus other row times multiplier
                for (int i = c; i < COLUMNS; i++) {
                    u[i][r] += -multiplierToPivotRow * u[i][c];
                }
            }
        }

        return {l, u, p};
    }

    template<typename L_TYPE, typename U_TYPE, typename P_TYPE, typename Q_TYPE>
    struct LUPQDecomposition {
        L_TYPE l;
        U_TYPE u;
        P_TYPE p;
        Q_TYPE q;
    };

    LUPQDecomposition<Matrix<std::min(ROWS, COLUMNS), ROWS, T>, Matrix<COLUMNS, std::min(ROWS, COLUMNS), T>, Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, COLUMNS, T>> lupqDecomposition() const {
        Matrix<std::min(ROWS, COLUMNS), ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
        Matrix<COLUMNS, std::min(ROWS, COLUMNS), T> u = *this;
        Matrix<ROWS, ROWS, T> p = Matrix<ROWS, ROWS, T>::identity();
        Matrix<COLUMNS, COLUMNS, T> q = Matrix<COLUMNS, COLUMNS, T>::identity();

        // use std::min so we never access the pivot that's out of the matrix
        for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
            // handle row AND column swaps
            {
                int rowIndex = -1;
                int columnIndex = -1;

                const T pivot = u[c][c];

                T maxValue = std::abs(pivot);

                for (int i = c; i < COLUMNS; i++) {
                    for (int j = c; j < ROWS; j++) {
                        T curValue = std::abs(u[i][j]);

                        if (curValue > maxValue) {
                            maxValue = curValue;
                            columnIndex = i;
                            rowIndex = j;
                        }
                    }
                }

                if (rowIndex == -1 && columnIndex == -1 && compare(pivot, 0)) {
                    throw std::runtime_error("Cannot LUPQ decompose singular matrix");
                }

                if (rowIndex != c) {
                    u.swapRows(c, rowIndex);
                    p.swapRows(c, rowIndex);
                    // swap rows of L before column c
                    for (int i = 0; i < c; ++i) {
                        T temp = l[i][c];
                        l[i][c] = l[i][rowIndex];
                        l[i][rowIndex] = temp;
                    }
                }

                if (columnIndex != c) {
                    u.swapColumns(c, columnIndex);
                    q.swapColumns(c, columnIndex);
                }
            }

            T pivot = u[c][c];

            // iterate through things beneath that pivot in the matrix
            for (int r = c + 1; r < ROWS; r++) {
                T val = u[c][r];

                T multiplierToPivotRow = val / pivot;

                l[c][r] = multiplierToPivotRow;

                // do this row minus other row times multiplier
                for (int i = c; i < COLUMNS; i++) {
                    u[i][r] += -multiplierToPivotRow * u[i][c];
                }
            }
        }

        return {l, u, p, q};
    }

    template<typename L_TYPE, typename U_TYPE>
    struct LUDecomposition {
        L_TYPE l;
        U_TYPE u;
    };

    LUDecomposition<Matrix<std::min(ROWS, COLUMNS), ROWS, T>, Matrix<COLUMNS, std::min(ROWS, COLUMNS), T>> luDecomposition() const {
        Matrix<std::min(ROWS, COLUMNS), ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
        Matrix<COLUMNS, std::min(ROWS, COLUMNS), T> u = *this;

        // use std::min so we never access the pivot that's out of the matrix
        for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
            T pivot = u[c][c];

            if (compare(pivot, 0))
                throw std::runtime_error("Cannot LU decompose matrix due to zero pivot, try LUP or LUPQ");

            // iterate through things beneath that pivot in the matrix
            for (int r = c + 1; r < ROWS; r++) {
                T val = u[c][r];

                T multiplierToPivotRow = val / pivot;

                l[c][r] = multiplierToPivotRow;

                // do this row minus other row times multiplier
                for (int i = c; i < COLUMNS; i++) {
                    u[i][r] += -multiplierToPivotRow * u[i][c];
                }
            }
        }

        return {l, u};
    }

    template<typename L_TYPE, typename D_TYPE, typename U_TYPE>
    struct LDUDecomposition {
        L_TYPE l;
        D_TYPE d;
        U_TYPE u;
    };

    LDUDecomposition<Matrix<std::min(ROWS, COLUMNS), ROWS, T>, Matrix<std::min(ROWS, COLUMNS), std::min(ROWS, COLUMNS), T>, Matrix<COLUMNS, std::min(ROWS, COLUMNS), T>> lduDecomposition() const {
        Matrix<std::min(ROWS, COLUMNS), ROWS, T> l = Matrix<ROWS, ROWS, T>::identity();
        Matrix<std::min(ROWS, COLUMNS), std::min(ROWS, COLUMNS), T> d = Matrix<std::min(ROWS, COLUMNS), std::min(ROWS, COLUMNS), T>::identity();
        Matrix<COLUMNS, std::min(ROWS, COLUMNS), T> u = *this;

        // use std::min so we never access the pivot that's out of the matrix
        for (int c = 0; c < std::min(ROWS, COLUMNS); c++) {
            T pivot = u[c][c];

            if (compare(pivot, 0))
                throw std::runtime_error("Cannot LDU decompose matrix due to zero pivot");

            // iterate through things beneath that pivot in the matrix
            for (int r = c + 1; r < ROWS; r++) {
                T val = u[c][r];

                T multiplierToPivotRow = val / pivot;

                l[c][r] = multiplierToPivotRow;

                // do this row minus other row times multiplier
                for (int i = c; i < COLUMNS; i++) {
                    u[i][r] += -multiplierToPivotRow * u[i][c];
                }
            }
        }

        for (int c = 0; c < COLUMNS; c++) {
            d[c][c] = u[c][c];

            for (int r = 0; r < ROWS; r++) {
                u[c][r] /= d[c][c];
            }
        }

        return {l, d, u};
    }

    template<typename L_TYPE, typename L_TRANSPOSE_TYPE>
    struct CholeskyDecomposition {
        L_TYPE l;
        L_TRANSPOSE_TYPE lTranspose;
    };

    CholeskyDecomposition<Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> choleskyDecomposition(const bool allowPositiveSemiDefinite = false) const requires (isSquare) {
        if (!isHermitian()) {
            throw std::runtime_error("Cannot find Cholesky Decomposition of non hermitian/symmetric matrix");
        }

        Matrix<COLUMNS, ROWS, T> l;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r <= c; r++) {
                if (r == c) {
                    T value = data[c][c];

                    for (int k = 0; k < c; k++) {
                        // TODO: Find a way to replace this if
                        if constexpr (isComplex) {
                            value -= l[k][c] * std::conj(l[k][c]);
                        }
                        else {
                            value -= std::pow(l[k][c], 2);
                        }
                    }

                    if (value < 0) {
                        throw std::runtime_error("Cannot cholesky decompose non positive definite matrix");
                    }

                    if (compare(value, 0) && !allowPositiveSemiDefinite) {
                        throw std::runtime_error("Cannot cholesky decompose non semi-positive definite matrix");
                    }

                    l[c][c] = std::sqrt(value);
                }
                else if (r > c) {
                    T value = data[c][r];

                    for (int k = 0; k < c; k++) {
                        value -= l[k][r] * l[k][c];
                    }

                    l[c][r] = value / l[c][c];
                }
            }
        }

        return {l, l.conjugateTranspose()};
    }

    template<typename L_TYPE, typename D_TYPE, typename L_TRANSPOSE_TYPE>
    struct LDLDecomposition {
        L_TYPE l;
        D_TYPE d;
        L_TRANSPOSE_TYPE lTranspose;
    };

    LDLDecomposition<Matrix<COLUMNS, ROWS, T>, Matrix<COLUMNS, ROWS, T>, Matrix<ROWS, COLUMNS, T>> ldlDecomposition() const requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> l;
        Matrix<COLUMNS, ROWS, T> d;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r <= c; r++) {
                if constexpr (!isComplex) {
                    if (r == c) {
                        T value = data[c][c];

                        for (int k = 0; k < c; k++) {
                            value -= std::pow(l[k][c], 2) * d[k][k];
                        }

                        d[c][c] = value;
                    }
                    else if (r > c) {
                        T value = data[c][r];

                        for (int k = 0; k < c; k++) {
                            value -= l[k][r] * l[k][c] * d[k][k];
                        }

                        l[c][r] = (1 / d[c][c]) * value;
                    }
                }
                else {
                    if (r == c) {
                        T value = data[c][c];

                        for (int k = 0; k < c; k++) {
                            T complexConjugate = l[k][c];
                            complexConjugate.imag *= -1;
                            value -= l[k][c] * complexConjugate * d[k][k];
                        }

                        d[c][c] = value;
                    }
                    else if (r > c) {
                        T value = data[c][r];

                        for (int k = 0; k < c; k++) {
                            T complexConjugate = l[k][c];
                            complexConjugate.imag *= -1;

                            value -= l[k][r] * complexConjugate * d[k][k];
                        }

                        l[c][r] = (1 / d[c][c]) * value;
                    }
                }
            }
        }

        return {l, d, l.conjugateTranspose()};
    }

    template<typename Q_TYPE, typename R_TYPE>
    struct QRDecomposition {
        Q_TYPE q;
        R_TYPE r;
    };

    QRDecomposition<Matrix<ROWS, ROWS, T>, Matrix<COLUMNS, ROWS, T>> qrDecomposition() const requires (isSquare) {
        std::array<Vector<ROWS>, COLUMNS> a = getColumnVectors();
        std::array<Vector<ROWS>, COLUMNS> u = {};
        Matrix<ROWS, ROWS, T> q;

        for (int k = 0; k < COLUMNS; k++) {
            u[k] = a[k];

            for (int j = 0; j < k; j++) {
                u[k] -= u[j].projection(a[k]);
            }

            T uMagnitude = u[k].magnitude();

            for (int i = 0; i < ROWS; i++) {
                q[k][i] = u[k][i] / uMagnitude;
            }
        }

        Matrix<COLUMNS, ROWS, T> r = q.transpose() * *this;

        return {q, r};
    }

    T minorOfElement(const int c, const int r) const requires (isSquare) {
        return removeColumnsAndRows({c}, {r}).determinant();
    }

    Matrix<COLUMNS, ROWS, T> minorMatrix() const requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = minorOfElement(c, r);
            }
        }

        return result;
    }

    T cofactorOfElement(const int c, const int r) const requires (isSquare) {
        return minorOfElement(c, r) * std::pow(-1, c + r);
    }

    Matrix<COLUMNS, ROWS, T> cofactorMatrix() const requires (isSquare) {
        Matrix<COLUMNS, ROWS, T> result;

        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                result[c][r] = cofactorOfElement(c, r);
            }
        }

        return result;
    }

    Matrix<ROWS, COLUMNS, T> adjoint() const requires (isSquare) {
        return cofactorMatrix().transpose();
    }

    bool isUpperHessenberg() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = c + 2; r < ROWS; r++) {
                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isUnreducedUpperHessenberg() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = c + 1; r < ROWS; r++) {
                // subdiagonal
                if (r == c + 1) {
                    if (compare(data[c][r], 0)) {
                        return false;
                    }
                }
                else {
                    if (!compare(data[c][r], 0)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool isLowerHessenberg() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = c - 2; r >= 0; r--) {
                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    bool isUnreducedLowerHessenberg() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = c - 1; r >= 0; r--) {
                // supra-diagonal
                if (r == c - 1) {
                    if (compare(data[c][r], 0)) {
                        return false;
                    }
                }
                else {
                    if (!compare(data[c][r], 0)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool isTridiagonal() const requires (isSquare) {
        for (int c = 0; c < COLUMNS; c++) {
            for (int r = 0; r < ROWS; r++) {
                // diagonal, subdiagonal, supradiagonal
                if (c == r || c == r + 1 || c == r - 1)
                    continue;

                if (!compare(data[c][r], 0))
                    return false;
            }
        }

        return true;
    }

    template<typename T_TYPE, typename Q_TYPE>
    struct LanczosAlgorithm {
        T_TYPE t;
        Q_TYPE q;
    };

    template<int ITER>
    LanczosAlgorithm<Matrix<ITER, ITER, T>, Matrix<ITER + 1, COLUMNS, T>> lanczosAlgorithm() const requires (isSquare) {
        if (!isHermitian())
            throw std::runtime_error("Cannot do Lanczos algorithm on non hermitian matrix");

        std::array<Vector<COLUMNS, T>, ITER + 1> q;

        Matrix<ITER, ITER, T> t;
        Matrix<ITER + 1, COLUMNS, T> qMatrix;

        qMatrix.setColumnVector(0, Vector<COLUMNS, T>::random().normalize());

        for (int m = 0; m < ITER; m++) {
            Vector<COLUMNS, T> v = multiply(q[m]);
            t[m][m] = q[m] * v;

            if (m == 0) {
                v -= t[m][m] * q[m];
            }
            else {
                v -= t[m][m - 1] * q[m - 1] - t[m][m] * q[m];
            }

            T vNorm = v.euclidianNorm();

            if (m != ITER - 1) {
                t[m][m + 1] = t[m + 1][m] = vNorm;
            }

            q[m + 1] = v / vNorm;

            qMatrix.setColumnVector(m + 1, q[m + 1]);
        }

        return {t, qMatrix};
    }

    /**
     * Used to get an eigen-value approximation from an eigen-vector approximation
     * @param vec eigen-vector approximation
     * @return corresponding eigen-value approximation for given vector @a vec
     */
    T rayleighQuotient(const Vector<COLUMNS, T>& vec) const {
        return (vec * *this * vec) / (vec * vec);
    }

    template<typename EIGENVECTOR_TYPE, typename EIGENVALUE_TYPE>
    struct PowerIteration {
        EIGENVECTOR_TYPE vector;
        EIGENVALUE_TYPE value;
    };

    PowerIteration<Vector<COLUMNS, T>, T> powerIteration(const int maxIterations, const T tolerance = epsilon) const {
        Vector<COLUMNS, T> vec = Vector<COLUMNS, T>::random();
        T val = {};

        for (int i = 0; i < maxIterations; i++) {
            vec = multiply(vec).normalize();
            T nextVal = rayleighQuotient(vec);

            if (std::abs(val - nextVal) < tolerance) {
                return {vec, nextVal};
            }

            val = nextVal;
        }

        return {vec, val};
    }
};

template<int COLUMNS, int ROWS, is_scalar_v T>
Matrix<COLUMNS, ROWS, T> multiply(const T lhs, const Matrix<COLUMNS, ROWS, T>& rhs) {
    return rhs.multiply(lhs);
}

template<int COLUMNS, int ROWS, is_scalar_v T>
Matrix<COLUMNS, ROWS, T> operator*(const T lhs, const Matrix<COLUMNS, ROWS, T>& rhs) {
    return multiply(lhs, rhs);
}

template<int COLUMNS, int ROWS, is_scalar_v T, is_convertable_to<T> OTHER_T>
Matrix<COLUMNS, ROWS, T> multiply(const OTHER_T lhs, const Matrix<COLUMNS, ROWS, T>& rhs) {
    return rhs.multiply(lhs);
}

template<int COLUMNS, int ROWS, is_scalar_v T, is_convertable_to<T> OTHER_T>
Matrix<COLUMNS, ROWS, T> operator*(const OTHER_T lhs, const Matrix<COLUMNS, ROWS, T>& rhs) {
    return multiply(lhs, rhs);
}

template<int N, is_scalar_v T>
Matrix<N, N, T> Vector<N, T>::crossProductMatrix() const requires (N == 3) {
    return {{0, -data[2], data[1]}, {data[2], 0, -data[0]}, {-data[1], data[0], 0}};
}

template<int N, is_scalar_v T>
template<int OTHER_N>
Matrix<OTHER_N, N, T> Vector<N, T>::outerProductMatrix(const Vector<OTHER_N, T>& v) const {
    Matrix<OTHER_N, N, T> result;

    for (int c = 0; c < result.columns; c++) {
        for (int r = 0; r < result.rows; r++) {
            if constexpr (isComplex)
                result[c][r] = data[r] * std::conj(v[c]);
            else
                result[c][r] = data[r] * v[c];
        }
    }

    return result;
}

template<int N, is_scalar_v T>
template<int OTHER_N, is_convertable_to<T> OTHER_T>
Matrix<OTHER_N, N, T> Vector<N, T>::outerProductMatrix(const Vector<OTHER_N, OTHER_T>& v) const {
    Matrix<OTHER_N, N, T> result;

    for (int c = 0; c < result.columns; c++) {
        for (int r = 0; r < result.rows; r++) {
            if (isComplex)
                result[c][r] = data[r] * std::conj(v[c]);
            else
                result[c][r] = data[r] * v[c];
        }
    }

    return result;
}

template<int N, is_scalar_v T>
template<int ROWS>
Vector<N, T> Vector<N, T>::multiply(const Matrix<N, ROWS, T>& m) const {
    Vector<N, T> result;

    for (int c = 0; c < N; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[r] += data[c] * m.data[c][r];
        }
    }

    return result;
}

template<int N, is_scalar_v T>
template<int ROWS>
Vector<N, T> Vector<N, T>::operator*(const Matrix<N, ROWS, T>& m) const {
    return multiply(m);
}

template<int N, is_scalar_v T>
template<int ROWS, is_convertable_to<T> OTHER_T>
Vector<N, T> Vector<N, T>::multiply(const Matrix<N, ROWS, OTHER_T>& m) const {
    Vector<N, T> result;

    for (int c = 0; c < N; c++) {
        for (int r = 0; r < ROWS; r++) {
            result[r] += data[c] * m.data[c][r];
        }
    }

    return result;
}

template<int N, is_scalar_v T>
template<int ROWS, is_convertable_to<T> OTHER_T>
Vector<N, T> Vector<N, T>::operator*(const Matrix<N, ROWS, OTHER_T>& m) const {
    return multiply(m);
}

template<int COLUMNS, int ROWS, int B_COLUMNS, int B_ROWS, is_scalar_v B_T>
struct Matrix<COLUMNS, ROWS, Matrix<B_COLUMNS, B_ROWS, B_T>> {
    static constexpr int columns = COLUMNS;
    static constexpr int rows = ROWS;
    static constexpr int bColumns = B_COLUMNS;
    static constexpr int bRows = B_ROWS;

    static constexpr bool isSquare = ROWS == COLUMNS;
    static constexpr bool bIsSquare = B_ROWS == B_COLUMNS;

    Matrix<B_COLUMNS, B_ROWS, B_T> data[COLUMNS][ROWS] = {};
};
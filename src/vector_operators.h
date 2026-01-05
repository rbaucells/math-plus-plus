#pragma once
#include "vector.h"
#include "matrix.h"

// v = v
template<int N, scalar T>
Vector<N, T>& Vector<N, T>::operator=(const Vector<N, T>& other) {
    if (this != &other) {
        for (int i = 0; i < N; i++) {
            data[i] = other.data[i];
        }
    }

    return *this;
}

// v == v
template<int N, scalar T>
bool Vector<N, T>::equals(const Vector<N, T>& other, underlying_type_t<T> precision) const {
    for (int i = 0; i < N; i++) {
        if (!compare(data[i], other.data[i], precision))
            return false;
    }

    return true;
}

template<int N, scalar T>
bool Vector<N, T>::operator==(const Vector<N, T>& other) const {
    return equals(other);
}

// v + v
template<int N, scalar T>
Vector<N, T> Vector<N, T>::add(const Vector<N, T>& other) const {
    Vector<N, T> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] + other[i];
    }

    return v;
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::operator+(const Vector<N, T>& other) const {
    return add(other);
}

// v - v
template<int N, scalar T>
Vector<N, T> Vector<N, T>::subtract(const Vector<N, T>& other) const {
    Vector<N, T> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] - other[i];
    }

    return v;
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::operator-(const Vector<N, T>& other) const {
    return subtract(other);
}

// v * #
template<int N, scalar T>
Vector<N, T> Vector<N, T>::multiply(const T scalar) const {
    Vector<N, T> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] * scalar;
    }

    return v;
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::operator*(const T scalar) const {
    return multiply(scalar);
}

// v / #
template<int N, scalar T>
Vector<N, T> Vector<N, T>::divide(const T scalar) const {
    Vector<N, T> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] / scalar;
    }

    return v;
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::operator/(const T scalar) const {
    return divide(scalar);
}

// v += v
template<int N, scalar T>
Vector<N, T>& Vector<N, T>::addEquals(const Vector<N, T>& other) {
    for (int i = 0; i < N; i++) {
        data[i] += other.data[i];
    }

    return *this;
}

template<int N, scalar T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& other) {
    return addEquals(other);
}

// v -= v
template<int N, scalar T>
Vector<N, T>& Vector<N, T>::subtractEquals(const Vector<N, T>& other) {
    for (int i = 0; i < N; i++) {
        data[i] -= other.data[i];
    }

    return *this;
}

template<int N, scalar T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& other) {
    return subtractEquals(other);
}

// v *= #
template<int N, scalar T>
Vector<N, T>& Vector<N, T>::multiplyEquals(const T scalar) {
    for (int i = 0; i < N; i++) {
        data[i] *= scalar;
    }

    return *this;
}

template<int N, scalar T>
Vector<N, T>& Vector<N, T>::operator*=(const T scalar) {
    return multiplyEquals(scalar);
}

// v /= #
template<int N, scalar T>
Vector<N, T>& Vector<N, T>::divideEquals(const T scalar) {
    for (int i = 0; i < N; i++) {
        data[i] /= scalar;
    }

    return *this;
}

template<int N, scalar T>
Vector<N, T>& Vector<N, T>::operator/=(const T scalar) {
    return divideEquals(scalar);
}

// v * m
template<int N, scalar T>
template<int COLUMNS>
Vector<COLUMNS, T> Vector<N, T>::multiply(const Matrix<COLUMNS, N, T>& m) const {
    Vector<COLUMNS, T> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < N; r++) {
            result[c] += data[r] * m[c][r];
        }
    }

    return result;
}

template<int N, scalar T>
template<int COLUMNS>
Vector<COLUMNS, T> Vector<N, T>::operator*(const Matrix<COLUMNS, N, T>& m) const {
    return multiply(m);
}

// v = v
template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::operator=(const Vector<N, OTHER_T>& other) {
    if (*this != other) {
        for (int i = 0; i < N; i++) {
            data[i] = other.data[i];
        }
    }

    return *this;
}

// v == v
template<int N, scalar T>
template<typename OTHER_T> requires std::equality_comparable_with<OTHER_T, T>
bool Vector<N, T>::equals(const Vector<N, OTHER_T>& other, const std::common_type_t<underlying_type_t<T>, underlying_type_t<OTHER_T>> precision) const {
    for (int i = 0; i < N; i++) {
        if (!compare(data[i], other.data[i], precision))
            return false;
    }

    return true;
}

template<int N, scalar T>
template<typename OTHER_T> requires std::equality_comparable_with<OTHER_T, T>
bool Vector<N, T>::operator==(const Vector<N, OTHER_T>& other) const {
    return equals(other);
}

// v + v
template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::add(const Vector<N, OTHER_T>& other) const {
    Vector<N, std::common_type_t<T, OTHER_T>> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] + other[i];
    }

    return v;
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::operator+(const Vector<N, OTHER_T>& other) const {
    return add(other);
}

// v - v
template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::subtract(const Vector<N, OTHER_T>& other) const {
    Vector<N, std::common_type_t<T, OTHER_T>> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] - other[i];
    }

    return v;
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::operator-(const Vector<N, OTHER_T>& other) const {
    return subtract(other);
}

// v * #
template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::multiply(const OTHER_T scalar) const {
    Vector<N, std::common_type_t<T, OTHER_T>> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] * scalar;
    }

    return v;
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::operator*(const OTHER_T scalar) const {
    return multiply(scalar);
}

// v / #
template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::divide(const OTHER_T scalar) const {
    Vector<N, std::common_type_t<T, OTHER_T>> v;

    for (int i = 0; i < N; i++) {
        v[i] = data[i] / scalar;
    }

    return v;
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::operator/(const OTHER_T scalar) const {
    return divide(scalar);
}

// v += v
template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::addEquals(const Vector<N, OTHER_T>& other) {
    for (int i = 0; i < N; i++) {
        data[i] += other.data[i];
    }

    return *this;
}

template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, OTHER_T>& other) {
    return addEquals(other);
}

// v -= v
template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::subtractEquals(const Vector<N, OTHER_T>& other) {
    for (int i = 0; i < N; i++) {
        data[i] -= other.data[i];
    }

    return *this;
}

template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, OTHER_T>& other) {
    return subtractEquals(other);
}

// v *= #
template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::multiplyEquals(const OTHER_T scalar) {
    for (int i = 0; i < N; i++) {
        data[i] *= scalar;
    }

    return *this;
}

template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::operator*=(const OTHER_T scalar) {
    return multiplyEquals(scalar);
}

// v /= #
template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::divideEquals(const OTHER_T scalar) {
    for (int i = 0; i < N; i++) {
        data[i] /= scalar;
    }

    return *this;
}

template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>& Vector<N, T>::operator/=(const OTHER_T scalar) {
    return divideEquals(scalar);
}

// v * m
template<int N, scalar T>
template<int COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<COLUMNS, std::common_type_t<T, OTHER_T>> Vector<N, T>::multiply(const Matrix<COLUMNS, N, OTHER_T>& m) const {
    Vector<COLUMNS, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < COLUMNS; c++) {
        for (int r = 0; r < N; r++) {
            result[c] += data[r] * m[c][r];
        }
    }

    return result;
}

template<int N, scalar T>
template<int COLUMNS, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<COLUMNS, std::common_type_t<T, OTHER_T>> Vector<N, T>::operator*(const Matrix<COLUMNS, N, OTHER_T>& m) const {
    return multiply(m);
}

template<int N, scalar T>
Vector<N, T>::operator T*() {
    return &data[0];
}

template<int N, scalar T>
Vector<N, T>::operator const T*() const {
    return &data[0];
}

template<int N, scalar T>
T& Vector<N, T>::operator[](const int index) {
    return data[index];
}

template<int N, scalar T>
const T& Vector<N, T>::operator[](const int index) const {
    return data[index];
}

template<int N, scalar T>
Vector<N, T> operator*(const T scalar, const Vector<N, T>& vector) {
    Vector<N, T> result;

    for (int i = 0; i < N; i++) {
        result[i] = scalar * vector[i];
    }

    return result;
}

template<int N, scalar T, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Vector<N, std::common_type_t<T, OTHER_T>> operator*(const OTHER_T scalar, const Vector<N, T>& vector) {
    Vector<N, std::common_type_t<T, OTHER_T>> result;

    for (int i = 0; i < N; i++) {
        result[i] = scalar * vector[i];
    }

    return result;
}

template<int N, scalar T>
T Vector<N, T>::dot(const Vector<N, T>& other, const DotProductConjugationBehavior behavior) const {
    T result = {};

    for (int i = 0; i < N; i++) {
        if constexpr (!isComplex) {
            result += data[i] * other[i];
        }
        else {
            switch (behavior) {
                case second_argument:
                    result += data[i] * std::conj(other[i]);
                    break;
                case neither:
                    result += data[i] * other[i];
                    break;
                case first_argument:
                default:
                    result += std::conj(data[i]) * other[i];
                    break;
            }
        }
    }

    return result;
}

template<int N, scalar T>
T Vector<N, T>::operator*(const Vector<N, T>& other) const {
    return dot(other);
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
std::common_type_t<T, OTHER_T> Vector<N, T>::dot(const Vector<N, OTHER_T>& other, const DotProductConjugationBehavior behavior) const {
    std::common_type_t<T, OTHER_T> result = {};

    for (int i = 0; i < N; i++) {
        switch (behavior) {
            case second_argument:
                result += data[i] * std::conj(other[i]);
                break;
            case neither:
                result += data[i] * other[i];
                break;
            case first_argument:
            default:
                result += std::conj(data[i]) * other[i];
                break;
        }
    }

    return result;
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
std::common_type_t<T, OTHER_T> Vector<N, T>::operator*(const Vector<N, OTHER_T>& other) const {
    return dot(other);
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::operator-() const {
    Vector<N, T> result;

    for (int i = 0; i < N; i++) {
        result[i] = -data[i];
    }

    return result;
}

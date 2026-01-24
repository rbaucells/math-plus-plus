#pragma once
#include <complex>
#include <cstring>
#include "exceptions.h"
#include "matrix.h"
#include "vector.h"

template<int N, scalar T>
constexpr Vector<N, T>::Vector(std::initializer_list<T> list) {
    // check correct number of elements
    if (list.size() != N)
        throw InvalidDimensionException("Incorrect number of elements in initializer list");
    // index
    int i = 0;
    // loop over each value
    for (const auto value : list) {
        // store value
        data[i] = value;
        // advance index
        i++;
    }
}

template<int N, scalar T>
Vector<N, T>::Vector(const Vector<N, T>& other) {
    memcpy(data, other.data, sizeof(T) * N);
}

template<int N, scalar T>
template<typename OTHER_T> requires std::convertible_to<OTHER_T, T>
Vector<N, T>::Vector(const Vector<N, OTHER_T>& other) {
    for (int i = 0; i < N; i++) {
        data[i] = other.data[i];
    }
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::random(const UnderlyingType min, const UnderlyingType max) {
    Vector<N, T> v;

    std::random_device dev;
    std::mt19937 eng(dev());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min, max);

        for (int i = 0; i < N; i++) {
            v[i] = dist(eng);
        }
    }
    else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(min, max);

        for (int i = 0; i < N; i++) {
            v[i] = dist(eng);
        }
    }
    else if constexpr (isComplex) {
        if constexpr (std::is_integral_v<UnderlyingType>) {
            std::uniform_int_distribution<UnderlyingType> realDist(min, max);
            std::uniform_int_distribution<UnderlyingType> imagDist(min, max);

            for (int i = 0; i < N; i++) {
                v[i] = std::complex<UnderlyingType>(realDist(eng), imagDist(eng));
            }
        }
        else {
            std::uniform_real_distribution<UnderlyingType> realDist(min, max);
            std::uniform_real_distribution<UnderlyingType> imagDist(min, max);

            for (int i = 0; i < N; i++) {
                v[i] = std::complex<UnderlyingType>(realDist(eng), imagDist(eng));
            }
        }
    }

    return v;
}

template<int N, scalar T>
template<int V_SIZE>
std::array<Vector<N, T>, V_SIZE> Vector<N, T>::orthonormalize(const std::array<Vector<N, T>, V_SIZE>& v) {
    auto orthoV = orthogonalize<V_SIZE>(v);

    for (auto& vec : orthoV) {
        vec = vec.normalized();
    }

    return orthoV;
}

template<int N, scalar T>
template<int V_SIZE>
std::array<Vector<N, T>, V_SIZE> Vector<N, T>::orthogonalize(const std::array<Vector<N, T>, V_SIZE>& v) {
    std::array<Vector<N, T>, V_SIZE> u;

    // first vectors always same
    u[1] = v[1];

    for (int k = 0; k < V_SIZE; k++) {
        u[k] = v[k];

        for (int i = 0; i < k; i++) {
            u[k] -= (v[k].dot(u[i]) / u[i].dot(u[i])) * u[i];
        }
    }

    return u;
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::conjugate() const {
    if constexpr (!isComplex)
        return *this;
    else {
        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = std::conj(data[i]);
        }

        return result;
    }
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::taxicabNorm() const {
    UnderlyingType result = {};

    for (int i = 0; i < N; i++) {
        result += std::abs(data[i]);
    }

    return result;
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::euclidianNorm() const {
    UnderlyingType result = {};

    for (int i = 0; i < N; i++) {
        result += std::norm(data[i]);
    }

    return std::sqrt(result);
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::euclidianNormSquared() const {
    UnderlyingType result = {};

    for (int i = 0; i < N; i++) {
        result += std::norm(data[i]);
    }

    return result;
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::maxNorm() const {
    UnderlyingType greatest = {};

    for (int i = 0; i < N; i++) {
        UnderlyingType abs = std::abs(data[i]);

        if (abs > greatest)
            greatest = abs;
    }

    return greatest;
}

template<int N, scalar T>
[[nodiscard]] std::string Vector<N, T>::toString(const int precision) const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision);

    ss << "[";
    for (int i = 0; i < N; i++) {
        if constexpr (isComplex) {
            ss << std::real(data[i]);

            ss << " ";

            UnderlyingType imag = std::imag(data[i]);

            if (imag < 0)
                ss << "- " << -imag << "i";
            else
                ss << "+ " << imag << "i";

        }
        else {
            ss << data[i];
        }

        if (i < N - 1)
            ss << ", ";
    }
    ss << "]";

    return ss.str();
}

template<int N, scalar T>
template<int OTHER_N>
Matrix<OTHER_N, N, T> Vector<N, T>::outerProductMatrix(const Vector<OTHER_N, T>& other, DotProductConjugationBehavior behavior) const {
    Matrix<OTHER_N, N, T> result;

    for (int c = 0; c < OTHER_N; c++) {
        for (int r = 0; r < N; r++) {
            if constexpr (isComplex) {
                switch (behavior) {
                    case second_argument:
                        result[c][r] = data[r] * std::conj(other[c]);
                        break;
                    case neither:
                        result[c][r] = data[r] * other[c];
                        break;
                    default:
                    case first_argument:
                        result[c][r] = std::conj(data[r]) * other[c];
                        break;
                }
            }
            else {
                result[c][r] = data[r] * other[c];
            }
        }
    }

    return result;
}

template<int N, scalar T>
template<int OTHER_N, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Matrix<OTHER_N, N, std::common_type_t<T, OTHER_T>> Vector<N, T>::outerProductMatrix(const Vector<OTHER_N, OTHER_T>& other, DotProductConjugationBehavior behavior) const {
    Matrix<OTHER_N, N, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < OTHER_N; c++) {
        for (int r = 0; r < N; r++) {
            if constexpr (isComplex || is_complex_v<OTHER_T>) {
                switch (behavior) {
                    case second_argument:
                        result[c][r] = data[r] * std::conj(other[c]);
                        break;
                    case neither:
                        result[c][r] = data[r] * other[c];
                        break;
                    default:
                    case first_argument:
                        result[c][r] = std::conj(data[r]) * other[c];
                        break;
                }
            }
            else {
                result[c][r] = data[r] * other[c];
            }
        }
    }

    return result;
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::cross(const Vector<N, T>& other) const requires (N == 3) {
    return {
        data[1] * other[2] - data[2] * other[1],
        data[2] * other[0] - data[0] * other[2],
        data[0] * other[1] - data[1] * other[0]
    };
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<T, OTHER_T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::cross(const Vector<N, OTHER_T>& other) const requires (N == 3) {
    return {
        data[1] * other[2] - data[2] * other[1],
        data[2] * other[0] - data[0] * other[2],
        data[0] * other[1] - data[1] * other[0]
    };
}

template<int N, scalar T>
Matrix<N, N, T> Vector<N, T>::crossProductMatrix() const requires (N == 3) {
    return {
        {0, -data[2], data[1]},
        {data[2], 0, -data[0]},
        {-data[1], data[0], 0}
    };
}

template<int N, scalar T>
Vector<N, std::common_type_t<T, typename Vector<N, T>::UnderlyingType>> Vector<N, T>::normalized() const {
    return divide(euclidianNorm());
}

template<int N, scalar T>
Vector<N * 2, typename Vector<N, T>::UnderlyingType> Vector<N, T>::toReal() const {
    Vector<N * 2, UnderlyingType> result;

    for (int k = 0; k < N; k++) {
        result[2 * k] = std::real(data[k]);
        result[2 * k + 1] = std::imag(data[k]);
    }

    return result;
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::euclidianAngle(const Vector<N, T>& other, const RotationType type) const {
    Vector<N * 2, UnderlyingType> realA = toReal();
    Vector<N * 2, UnderlyingType> realB = other.toReal();

    return convert(RotationType::radians, type, std::acos(realA.dot(realB) / (realA.euclidianNorm() * realB.euclidianNorm())));
}

template<int N, scalar T>
T Vector<N, T>::complexAngle(const Vector<N, T>& other, const DotProductConjugationBehavior behavior, const RotationType type) const {
    return convert(RotationType::radians, type, std::acos(dot(other, behavior) / (euclidianNorm() * other.euclidianNorm())));
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::hermitianAngle(const Vector<N, T>& other, const DotProductConjugationBehavior behavior, const RotationType type) const {
    return convert(RotationType::radians, type, std::acos(std::abs(dot(other, behavior)) / (euclidianNorm() * other.euclidianNorm())));
}

template<int N, scalar T>
T Vector<N, T>::scalarProjectOnto(const Vector<N, T>& v, DotProductConjugationBehavior behavior) const {
    return dot(v, behavior) / v.euclidianNorm();
}

template<int N, scalar T>
template<typename OTHER_T>
std::common_type_t<T, OTHER_T> Vector<N, T>::scalarProjectOnto(const Vector<N, OTHER_T>& v, DotProductConjugationBehavior behavior) const {
    return dot(v, behavior) / v.euclidianNorm();
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::vectorProjectOnto(const Vector<N, T>& v, DotProductConjugationBehavior behavior) const {
    return (dot(v, behavior) / v.euclidianNormSquared()) * v;
}

template<int N, scalar T>
template<typename OTHER_T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::vectorProjectOnto(const Vector<N, OTHER_T>& v, DotProductConjugationBehavior behavior) const {
    return (dot(v, behavior) / v.euclidianNormSquared()) * v;
}

template<int N, scalar T>
Vector<N, T>::UnderlyingType Vector<N, T>::scalarRejectFrom(const Vector<N, T>& v, DotProductConjugationBehavior behavior) const {
    return vectorRejectFrom(v, behavior).euclidianNorm();
}

template<int N, scalar T>
template<typename OTHER_T>
std::common_type_t<typename Vector<N, T>::UnderlyingType, underlying_type_t<OTHER_T>> Vector<N, T>::scalarRejectFrom(const Vector<N, OTHER_T>& v, DotProductConjugationBehavior behavior) const {
    return vectorRejectFrom(v, behavior).euclidianNorm();
}

template<int N, scalar T>
Vector<N, T> Vector<N, T>::vectorRejectFrom(const Vector<N, T>& v, DotProductConjugationBehavior behavior) const {
    return subtract(vectorProjectOnto(v, behavior));
}

template<int N, scalar T>
template<typename OTHER_T>
Vector<N, std::common_type_t<T, OTHER_T>> Vector<N, T>::vectorRejectFrom(const Vector<N, OTHER_T>& v, DotProductConjugationBehavior behavior) const {
    return subtract(vectorProjectOnto(v, behavior));
}

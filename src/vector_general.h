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
Vector<N, T> Vector<N, T>::random() {
    Vector<N, T> v;

    std::random_device dev;
    std::mt19937 eng(dev());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(0, 1);

        for (int i = 0; i < N; i++) {
            v[i] = dist(eng);
        }
    }
    else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(0, 1);

        for (int i = 0; i < N; i++) {
            v[i] = dist(eng);
        }
    }
    else if constexpr (isComplex) {
        std::uniform_real_distribution<UnderlyingType> realDist(0, 1);
        std::uniform_real_distribution<UnderlyingType> imagDist(0, 1);

        for (int i = 0; i < N; i++) {
            v[i] = std::complex<UnderlyingType>(realDist(eng), imagDist(eng));
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
[[nodiscard]] std::string Vector<N, T>::toString() const {
    std::stringstream ss;

    ss << "[";
    for (int i = 0; i < N; i++) {
        ss << data[i];

        if (i < N - 1)
            ss << ", ";
    }
    ss << "]";

    return ss.str();
}

template<int N, scalar T>
template<int OTHER_N>
Matrix<OTHER_N, N, T> Vector<N, T>::outerProductMatrix(const Vector<OTHER_N, T>& other) const {
    Matrix<OTHER_N, N, T> result;

    for (int c = 0; c < OTHER_N; c++) {
        for (int r = 0; r < N; r++) {
            result[c][r] = data[r] * other[c];
        }
    }

    return result;
}

template<int N, scalar T>
template<int OTHER_N, typename OTHER_T> requires HasCommonType<OTHER_T, T>
Matrix<OTHER_N, N, std::common_type_t<T, OTHER_T>> Vector<N, T>::outerProductMatrix(const Vector<OTHER_N, OTHER_T>& other) const {
    Matrix<OTHER_N, N, std::common_type_t<T, OTHER_T>> result;

    for (int c = 0; c < OTHER_N; c++) {
        for (int r = 0; r < N; r++) {
            result[c][r] = data[r] * other[c];
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
Vector<N, T>::UnderlyingType Vector<N, T>::angle(const Vector<N, T>& other, const RotationType type) const {
    UnderlyingType result = std::acos(std::real(dot(other)) / (euclidianNorm() * other.euclidianNorm()));
    return convert(RotationType::radians, type, result);
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<OTHER_T, T>
std::common_type_t<typename Vector<N, T>::UnderlyingType, typename Vector<N, OTHER_T>::UnderlyingType> Vector<N, T>::angle(const Vector<N, OTHER_T>& other, const RotationType type) const {
    std::common_type_t<UnderlyingType, typename Vector<N, OTHER_T>::UnderlyingType> result = std::acos(std::real(dot(other)) / (euclidianNorm() * other.euclidianNorm()));
    return convert(RotationType::radians, type, result);
}

template<int N, scalar T>
std::common_type_t<T, typename Vector<N, T>::UnderlyingType> Vector<N, T>::scalarProjection(const Vector<N, T>& other) const {
    return dot(other) / other.euclidianNorm();
}

template<int N, scalar T>
template<typename OTHER_T> requires HasCommonType<T, OTHER_T, typename Vector<N, OTHER_T>::UnderlyingType>
std::common_type_t<T, OTHER_T, typename Vector<N, OTHER_T>::UnderlyingType> Vector<N, T>::scalarProjection(const Vector<N, OTHER_T>& other) const {
    return dot(other) / other.euclidianNorm();
}


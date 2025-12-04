#pragma once
#include <array>
#include <complex>
#include <random>
#include <cstring>

#include "helper.h"
#include "rotation.h"
#include "vector.h"

template<int N, is_scalar_v T>
struct Vector;

template<typename T>
struct is_vector : std::false_type {};

template<int N, is_scalar_v T>
struct is_vector<Vector<N, T>> : std::true_type {};

template<typename T>
concept is_vector_v = is_vector<T>::value;

template<int COLUMNS, int ROWS, is_scalar_v T>
struct Matrix;

template<int N, is_scalar_v T = float>
struct Vector {
    static constexpr int n = N;

    static constexpr bool isComplex = is_complex_v<T>;

    static constexpr T epsilon = ::epsilon<T>();

    T data[N] = {};

    Vector() = default;

    Vector(std::initializer_list<T> list) {
        if (list.size() != N) {
            throw std::runtime_error("Incorrect number of elements in initializer list");
        }

        int i = 0;

        for (const auto value : list) {
            data[i] = value;
            i++;
        }
    }

    // same type copy constructor
    Vector(const Vector<N, T>& other) {
        memcpy(data, other.data, sizeof(T) * N);
    }

    // different type copy constructor
    template<is_convertable_to<T> OTHER_T>
    Vector(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] = other.data[i];
        }
    }

    static Vector<N, T> random() {
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
            std::uniform_real_distribution<typename T::value_type> realDist(0, 1);
            std::uniform_real_distribution<typename T::value_type> imagDist(0, 1);

            for (int i = 0; i < N; i++) {
                v[i] = {realDist(eng), imagDist(eng)};
            }
        }

        return v;
    }

    // v = v
    Vector<N, T>& operator=(const Vector<N, T>& other) {
        if (this != &other) {
            for (int i = 0; i < N; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // v == v
    bool equals(const Vector<N, T>& other) const {
        for (int i = 0; i < N; i++) {
            if (!compare(data[i], other.data[i]))
                return false;
        }

        return true;
    }

    bool operator==(const Vector<N, T>& other) const {
        return equals(other);
    }

    // v + v
    Vector<N, T> add(const Vector<N, T>& other) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] + other[i];
        }

        return v;
    }

    Vector<N, T> operator+(const Vector<N, T>& other) const {
        return add(other);
    }

    // v - v
    Vector<N, T> subtract(const Vector<N, T>& other) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] - other[i];
        }

        return v;
    }

    Vector<N, T> operator-(const Vector<N, T>& other) const {
        return subtract(other);
    }

    // v * #
    Vector<N, T> multiply(const T scalar) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] * scalar;
        }

        return v;
    }

    Vector<N, T> operator*(const T scalar) const {
        return multiply(scalar);
    }

    // v / #
    Vector<N, T> divide(const T scalar) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] / scalar;
        }

        return v;
    }

    Vector<N, T> operator/(const T scalar) const {
        return divide(scalar);
    }

    // v * v
    T componentDot(const Vector<N, T>& other) const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] * other[i];
        }

        return result;
    }

    T operator*(const Vector<N, T>& other) const {
        return componentDot(other);
    }

    // v += v
    Vector<N, T>& addEquals(const Vector<N, T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] += other.data[i];
        }

        return *this;
    }

    Vector<N, T>& operator+=(const Vector<N, T>& other) {
        return addEquals(other);
    }

    // v -= v
    Vector<N, T>& subtractEquals(const Vector<N, T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] -= other.data[i];
        }

        return *this;
    }

    Vector<N, T>& operator-=(const Vector<N, T>& other) {
        return subtractEquals(other);
    }

    // v *= #
    Vector<N, T>& multiplyEquals(const T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] *= scalar;
        }

        return *this;
    }

    Vector<N, T>& operator*=(const T scalar) {
        return multiplyEquals(scalar);
    }

    // v /= #
    Vector<N, T>& divideEquals(const T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] /= scalar;
        }

        return *this;
    }

    Vector<N, T>& operator/=(const T scalar) {
        return divideEquals(scalar);
    }

    // v = v
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& operator=(const Vector<N, OTHER_T>& other) {
        if (*this != other) {
            for (int i = 0; i < N; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // v == v
    template<is_convertable_to<T> OTHER_T>
    bool equals(const Vector<N, OTHER_T>& other) const {
        for (int i = 0; i < N; i++) {
            if (!compare(data[i], other.data[i]))
                return false;
        }

        return true;
    }

    template<is_convertable_to<T> OTHER_T>
    bool operator==(const Vector<N, OTHER_T>& other) const {
        return equals(other);
    }

    // v + v
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> add(const Vector<N, OTHER_T>& other) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] + other[i];
        }

        return v;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> operator+(const Vector<N, OTHER_T>& other) const {
        return add(other);
    }

    // v - v
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> subtract(const Vector<N, OTHER_T>& other) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] - other[i];
        }

        return v;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> operator-(const Vector<N, OTHER_T>& other) const {
        return subtract(other);
    }

    // v * #
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> multiply(const OTHER_T scalar) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] * scalar;
        }

        return v;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> operator*(const OTHER_T scalar) const {
        return multiply(scalar);
    }

    // v / #
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> divide(const OTHER_T scalar) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] / scalar;
        }

        return v;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T> operator/(const OTHER_T scalar) const {
        return divide(scalar);
    }

    // v * v
    template<is_convertable_to<T> OTHER_T>
    T componentDot(const Vector<N, OTHER_T>& other) const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] * other[i];
        }

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    T operator*(const Vector<N, OTHER_T>& other) const {
        return componentDot(other);
    }

    // v += v
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& addEquals(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] += other.data[i];
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& operator+=(const Vector<N, OTHER_T>& other) {
        return addEquals(other);
    }

    // v -= v
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& subtractEquals(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] -= other.data[i];
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& operator-=(const Vector<N, OTHER_T>& other) {
        return subtractEquals(other);
    }

    // v *= #
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& multiplyEquals(const OTHER_T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] *= scalar;
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& operator*=(const OTHER_T scalar) {
        return multiplyEquals(scalar);
    }

    // v /= #
    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& divideEquals(const OTHER_T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] /= scalar;
        }

        return *this;
    }

    template<is_convertable_to<T> OTHER_T>
    Vector<N, T>& operator/=(const OTHER_T scalar) {
        return divideEquals(scalar);
    }

    T angle(const Vector<N, T>& other, const RotationType type = RotationType::degrees) const {
        T radians = std::acos(componentDot(other) / (magnitude() * other.magnitude()));
        return convert(RotationType::radians, type, radians);
    }

    template<is_convertable_to<T> OTHER_T>
    T angle(const Vector<N, OTHER_T>& other, const RotationType type = RotationType::degrees) const {
        T radians = std::acos(componentDot(other) / (magnitude() * other.magnitude()));
        return convert(RotationType::radians, type, radians);
    }

    T magnitude() const {
        T result = {};

        for (int i = 0; i < N; i++) {
            if constexpr (isComplex) {
                result += data[i] * std::conj(data[i]);
            }
            else {
                result += std::pow(data[i], 2);
            }
        }

        return std::sqrt(result);
    }

    T geometricDot(const Vector<N, T>& other) const {
        T result = {};

        result = (magnitude() * other.magnitude() * std::cos(angle(other, RotationType::radians)));

        return result;
    }

    template<is_convertable_to<T> OTHER_T>
    T geometricDot(const Vector<N, OTHER_T>& other) const {
        T result = {};

        result = (magnitude() * other.magnitude() * std::cos(angle(other, RotationType::radians)));

        return result;
    }

    explicit operator T*() {
        return &data[0];
    }

    explicit operator const T*() const {
        return &data[0];
    }

    T& operator[](const int index) {
        return data[index];
    }

    const T& operator[](const int index) const {
        return data[index];
    }

    template<int V_SIZE>
    static std::array<Vector<N, T>, V_SIZE> orthonormalize(const std::array<Vector<N, T>, V_SIZE>& v) {
        auto orthoV = orthogonalize(v);

        for (auto& vec : orthoV) {
            vec = vec.normalize();
        }

        return orthoV;
    }

    template<int V_SIZE>
    static std::array<Vector<N, T>, V_SIZE> orthogonalize(const std::array<Vector<N, T>, V_SIZE>& v) {
        std::array<Vector<N, T>, V_SIZE> u;

        // first vectors always same
        u[1] = v[1];

        for (int k = 0; k < V_SIZE; k++) {
            u[k] = v[k];

            for (int i = 0; i < k; i++) {
                u[k] -= (v[k].componentDot(u[i]) / u[i].componentDot(u[i])) * u[i];
            }
        }

        return u;
    }

    template<int V_SIZE>
    static bool isOrthogonal(const std::array<Vector<N, T>, V_SIZE>& vectors) {
        for (int i = 0; i < vectors.size(); i++) {
            for (int j = i; j < vectors.size(); j++) {
                if (i == j)
                    continue;

                if (vectors[i].componentDot(vectors[j]) != 0) {
                    return false;
                }
            }
        }

        return true;
    }

    template<int V_SIZE>
    static bool isOrthonormal(const std::array<Vector<N, T>, V_SIZE>& vectors) {
        for (int i = 0; i < vectors.size(); i++) {
            if (vectors[i].componentDot(vectors[i]) != 1) {
                return false;
            }

            for (int j = i; j < vectors.size(); j++) {
                if (i == j)
                    continue;

                if (vectors[i].componentDot(vectors[j]) != 0) {
                    return false;
                }
            }
        }

        return true;
    }

    Vector<N, T> projection(const Vector<N, T>& other) {
        return (componentDot(other) / other.componentDot(other)) * other;
    }

    Vector<N, T> normalize() const {
        return *this / magnitude();
    }

    Vector<N, T> conjugate() const requires (is_complex<T>::value) {
        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = std::conj(data[i]);
        }

        return result;
    }

    T taxicabNorm() const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += std::abs(data[i]);
        }

        return result;
    }

    T euclidianNorm() const {
        return magnitude();
    }

    T maxNorm() const {
        T greatest = {};

        for (int i = 0; i < N; i++) {
            if (std::abs(data[i]) > greatest)
                greatest = std::abs(data[i]);
        }

        return greatest;
    }

    std::string toString() const {
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

    Matrix<N, N, T> crossProductMatrix() const requires (N == 3);

    template<int OTHER_N>
    Matrix<OTHER_N, N, T> outerProductMatrix(const Vector<OTHER_N, T>& v) const;

    template<int OTHER_N, is_convertable_to<T> OTHER_T>
    Matrix<OTHER_N, N, T> outerProductMatrix(const Vector<OTHER_N, OTHER_T>& v) const;

    template<int ROWS>
    Vector<N, T> multiply(const Matrix<N, ROWS, T>& m) const;

    template<int ROWS>
    Vector<N, T> operator*(const Matrix<N, ROWS, T>& m) const;

    template<int ROWS, is_convertable_to<T> OTHER_T>
    Vector<N, T> multiply(const Matrix<N, ROWS, OTHER_T>& m) const;

    template<int ROWS, is_convertable_to<T> OTHER_T>
    Vector<N, T> operator*(const Matrix<N, ROWS, OTHER_T>& m) const;
};

template<int N, is_scalar_v T>
Vector<N, T> operator*(const T lhs, const Vector<N, T>& rhs) {
    Vector<N, T> result;

    for (int i = 0; i < N; i++) {
        result[i] = lhs * rhs.data[i];
    }

    return result;
}

template<int N, is_scalar_v T, is_convertable_to<T> OTHER_T>
Vector<N, T> operator*(const OTHER_T lhs, const Vector<N, T>& rhs) {
    Vector<N, T> result;

    for (int i = 0; i < N; i++) {
        result[i] = lhs * rhs.data[i];
    }

    return result;
}
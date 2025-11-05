#pragma once
#include "rotation.h"

template<typename T, typename U>
concept IsConvertableTo = std::convertible_to<U, T>;

template<int N, typename T = float>
struct Vector {
    const int n = N;
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

    Vector(const Vector<N, T>& other) {
        memcpy(data, other.data, sizeof(T) * N);
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] = other.data[i];
        }
    }

    Vector<N, T>& operator=(const Vector<N, T>& other) {
        if (this != &other) {
            for (int i = 0; i < N; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T>& operator=(const Vector<N, OTHER_T>& other) {
        if (*this != other) {
            for (int i = 0; i < N; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    bool compare(const Vector<N, T>& other) const {
        if constexpr (std::is_floating_point_v<T>) {
            T epsilon = std::numeric_limits<T>::epsilon();
            for (int i = 0; i < N; i++) {
                if (std::abs(other.data[i] - data[i]) > epsilon)
                    return false;
            }

            return true;
        }
        else {
            for (int i = 0; i < N; i++) {
                if (other.data[i] == data[i])
                    return false;
            }

            return false;
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    bool compare(const Vector<N, OTHER_T>& other) const {
        if constexpr (std::is_floating_point_v<T>) {
            T epsilon = std::numeric_limits<T>::epsilon();
            for (int i = 0; i < N; i++) {
                if (std::abs(static_cast<T>(other.data[i]) - data[i]) > epsilon)
                    return false;
            }

            return true;
        }
        else {
            for (int i = 0; i < N; i++) {
                if (static_cast<T>(other.data[i]) == data[i])
                    return false;
            }

            return false;
        }
    }

    bool operator==(const Vector<N, T>& other) const {
        return compare(other);
    }

    template<IsConvertableTo<T> OTHER_T>
    bool operator==(const Vector<N, OTHER_T>& other) const {
        return compare(other);
    }

    Vector<N, T> add(const Vector<N, T>& other) const {
        Vector<N, T> v = *this;

        for (int i = 0; i < N; i++) {
            v[i] += other[i];
        }

        return v;
    }

    Vector<N, T> subtract(const Vector<N, T>& other) const {
        Vector<N, T> v = *this;

        for (int i = 0; i < N; i++) {
            v[i] -= other[i];
        }

        return v;
    }

    Vector<N, T> multiply(T scalar) const {
        Vector<N, T> v = *this;

        for (int i = 0; i < N; i++) {
            v[i] *= scalar;
        }

        return v;
    }

    Vector<N, T> divide(T scalar) const {
        Vector<N, T> v = *this;

        for (int i = 0; i < N; i++) {
            v[i] /= scalar;
        }

        return v;
    }

    Vector<N, T> operator+(const Vector<N, T>& other) const {
        return add(other);
    }

    Vector<N, T> operator-(const Vector<N, T>& other) const {
        return subtract(other);
    }

    Vector<N, T> operator*(T scalar) const {
        return multiply(scalar);
    }

    Vector<N, T> operator/(T scalar) const {
        return divide(scalar);
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T> add(const Vector<N, OTHER_T>& other) {
        Vector<N, T> v = *this;

        for (int i = 0; i < N; i++) {
            v[i] += other[i];
        }

        return v;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T> subtract(const Vector<N, OTHER_T>& other) {
        Vector<N, T> v = *this;

        for (int i = 0; i < N; i++) {
            v[i] -= other[i];
        }

        return v;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T> operator+(const Vector<N, OTHER_T>& other) const {
        return add(other);
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T> operator-(const Vector<N, OTHER_T>& other) const {
        return subtract(other);
    }

    void addEquals(const Vector<N, T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] += other[i];
        }
    }

    void subtractEquals(const Vector<N, T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] -= other[i];
        }
    }

    void multiplyEquals(T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] *= scalar;
        }
    }

    void divideEquals(T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] /= scalar;
        }
    }

    Vector<N, T>& operator+=(const Vector<N, T>& other) {
        addEquals(other);
        return *this;
    }

    Vector<N, T>& operator-=(const Vector<N, T>& other) {
        subtractEquals(other);
        return *this;
    }

    Vector<N, T>& operator*=(T scalar) {
        multiplyEquals(scalar);
        return *this;
    }

    Vector<N, T>& operator/=(T scalar) {
        divideEquals(scalar);
        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    void addEquals(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] += other[i];
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    void subtractEquals(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] -= other[i];
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T>& operator+=(const Vector<N, OTHER_T>& other) {
        addEquals(other);
        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector<N, T>& operator-=(const Vector<N, OTHER_T>& other) {
        subtractEquals(other);
        return *this;
    }

    T angle(const Vector<N, T>& other, const RotationType type = RotationType::degrees) const {
        T radians = {};

        radians = std::acos(componentDot(other) / (magnitude() * other.magnitude()));

        return convert(RotationType::radians, type, radians);
    }

    template<IsConvertableTo<T> OTHER_T>
    T angle(const Vector<N, OTHER_T>& other, const RotationType type = RotationType::degrees) const {
        T radians = {};

        radians = std::acos(componentDot(other) / (magnitude() * other.magnitude()));

        return convert(RotationType::radians, type, radians);
    }

    T magnitude() const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] * data[i];
        }

        return sqrt(result);
    }

    T componentDot(const Vector<N, T>& other) const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] * other[i];
        }

        return result;
    }

    template<IsConvertableTo<T> OTHER_T>
    T componentDot(const Vector<N, OTHER_T>& other) const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] * other[i];
        }

        return result;
    }

    T geometricDot(const Vector<N, T>& other) const {
        T result = {};

        result = (magnitude() * other.magnitude() * std::cos(angle(other, RotationType::radians)));

        return result;
    }

    template<IsConvertableTo<T> OTHER_T>
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

    template<unsigned long V_SIZE>
    static std::array<Vector<N, T>, V_SIZE> orthonormalize(const std::array<Vector<N, T>, V_SIZE>& vectors) {
        std::array<Vector<N, T>, V_SIZE> vecs = vectors;

        for (auto& v : vecs) {
            T magnitude = v.magnitude();
            v /= magnitude;
        }

        return vecs;
    }

    template<int V_SIZE>
    static bool orthogonal(const std::array<Vector<N, T>, V_SIZE>& vectors) {
        for (int i = 0; i < vectors.size(); i++) {
            for (int j = i; j < vectors.size(); j++) {
                if (vectors[i].componentDot(vectors[j]) == 0) {
                    return false;
                }
            }
        }

        return true;
    }

    template<int V_SIZE>
    static bool orthonormal(const std::array<Vector<N, T>, V_SIZE>& vectors) {
        if (!orthogonal(vectors))
            return false;

        for (int i = 0; i < vectors.size(); i++) {
            for (int j = i; j < vectors.size(); j++) {
                if (vectors[i].componentDot(vectors[i]) == 0) {
                    return false;
                }
            }
        }

        return true;
    }
};

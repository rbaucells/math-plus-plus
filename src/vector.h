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
        if (*this != other) {
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

    Vector operator+(const Vector<N, T>& other) const {
        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = data[i] + other[i];
        }

        return result;
    }

    Vector operator-(const Vector<N, T>& other) const {
        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = data[i] - other[i];
        }

        return result;
    }

    Vector& operator+=(const Vector<N, T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] += other[i];
        }

        return *this;
    }

    Vector& operator-=(const Vector<N, T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] -= other[i];
        }

        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector operator+(const Vector<N, OTHER_T>& other) const {
        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = data[i] + other[i];
        }

        return result;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector operator-(const Vector<N, OTHER_T>& other) const {
        Vector<N, T> result;

        for (int i = 0; i < N; i++) {
            result[i] = data[i] - other[i];
        }

        return result;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector& operator+=(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] += other[i];
        }

        return *this;
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector& operator-=(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] -= other[i];
        }

        return *this;
    }

    Vector<N, T> multiply(const T scalar) const {
        Vector<N, T> v;

        for (int i = 0; i < N; i++) {
            v[i] = data[i] * scalar;
        }

        return v;
    }

    Vector operator*(const T scalar) const {
        return multiply(scalar);
    }

    void multiplyEquals(const T scalar) {
        for (int i = 0; i < N; i++) {
            data[i] *= scalar;
        }
    }

    Vector& operator*=(const T scalar) {
        multiplyEquals(scalar);
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
};

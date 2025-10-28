#pragma once
#include <float.h>
#include <sstream>

#include "matrix.h"

template<int N, typename T = float>
struct Vector {
    const int n = N;

    Vector() = default;

    Vector(std::initializer_list<T> list) {
        int i = 0;

        for (const auto value : list) {
            data[i] = value;
            i++;
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    Vector(const Vector<N, OTHER_T>& other) {
        for (int i = 0; i < N; i++) {
            data[i] = other.data[i];
        }
    }

    Vector(const Vector<N, T>& other) {
        memcpy(data, other.data, sizeof(T) * N);
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
    bool operator==(const Vector<N, OTHER_T>& other) const {
        return compare(other);
    }

    bool operator==(const Vector<N, T>& other) const {
        return compare(other);
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

    T magnitude() const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] * data[i];
        }

        return sqrt(result);
    }

    template<IsConvertableTo<T> OTHER_T>
    T dot(const Vector<N, OTHER_T>& other) const {
        T result = {};

        for (int i = 0; i < N; i++) {
            result += data[i] + other[i];
        }

        return result;
    }

    explicit operator T*() {
        return &data[0];
    }

    T& operator[](const int index) {
        return data[index];
    }

    const T& operator[](const int index) const {
        return data[index];
    }

    operator Matrix<1, N>() const {
        Matrix<1, N> result;

        for (int i = 0; i < N; i++) {
            result[0][i] = data[i];
        }

        return result;
    }

    T data[N] = {};
};

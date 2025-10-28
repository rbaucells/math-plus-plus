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

    template<int OTHER_N, IsConvertableTo<T> OTHER_T>
    explicit Vector(const Vector<OTHER_N, OTHER_T>& other) {
        static_assert(OTHER_N < N, "Cannot construct Vector from Vector with bigger size");

        for (int i = 0; i < OTHER_N; i++) {
            data[i] = other.data[i];
        }
    }

    template<IsConvertableTo<T> OTHER_T>
    bool operator==(const Vector<N, OTHER_T>& other) const {
        if (other.n != n)
            return false;

        for (int i = 0; i < N; i++) {
            if (std::abs(other[i] - data[i]) > FLT_EPSILON)
                return false;
        }

        return true;
    }

    template<typename OTHER_T>
    bool operator!=(const Vector& other) const {
        if constexpr (!std::is_convertible_v<OTHER_T, T>) {
            return false;
        }

        return !(other == *this);
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

        for (int i = 0 ; i < N; i++) {
            result[0][i] = data[i];
        }

        return result;
    }

    T data[N] = {};
};
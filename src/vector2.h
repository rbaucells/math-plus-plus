#pragma once

struct Vector2 {
    float x = {};
    float y = {};

    // operator overloads
    Vector2 operator+(const Vector2& other) const;

    Vector2 operator-(const Vector2& other) const;

    Vector2 operator*(float scalar) const;

    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);

    Vector2& operator-=(const Vector2& other);

    Vector2& operator*=(float scalar);

    Vector2& operator/=(float scalar);

    bool operator==(const Vector2& other) const;

    // functions
    [[nodiscard]] float magnitude() const;

    [[nodiscard]] Vector2 normalized() const;

    [[nodiscard]] Vector2 hadamard(const Vector2& other) const;

    [[nodiscard]] float dot(const Vector2& other) const;
};

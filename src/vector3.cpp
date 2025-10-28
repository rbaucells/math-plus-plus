#include <cmath>
#include "vector3.h"

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3{x + other.x, y + other.y, z + other.z};
}
Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3{x - other.x, y - other.y, z - other.z};
}
Vector3 Vector3::operator*(float scalar) const {
    return Vector3{x * scalar, y * scalar, z * scalar};
}
Vector3 Vector3::operator/(float scalar) const {
    return Vector3{x / scalar, y / scalar, z / scalar};
}

Vector3& Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
Vector3& Vector3::operator-=(const Vector3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}
Vector3& Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}
Vector3& Vector3::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    y /= scalar;
    return *this;
}


float Vector3::magnitude() const {
    return std::sqrt((x * x) + (y * y) + (z * z));
}
Vector3 Vector3::normalized() const {
    float mag = magnitude();

    if (mag > 0) {
        return Vector3{x / mag, y / mag, z / mag};
    }

    return *this;
}
float Vector3::dot(const Vector3 &other) const {
    return (x * other.x + y * other.y + z * other.z);
}
Vector3 Vector3::cross(const Vector3 &other) const {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

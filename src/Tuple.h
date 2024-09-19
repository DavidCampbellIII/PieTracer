#pragma once

#include <cmath>
#include <cfloat>

struct Tuple
{
public:
    float x;
    float y;
    float z;
    float w;

    Tuple() : x(0), y(0), z(0), w(0) {}
    Tuple(const float _x, const float _y, const float _z, const float _w) :
        x(_x), y(_y), z(_z), w(_w) {}

    static Tuple PointZero()
    {
        return Tuple(0, 0, 0, 1);
    }

    static Tuple VectorZero()
    {
        return Tuple(0, 0, 0, 0);
    }

    static Tuple Point(const float _x, const float _y, const float _z)
    {
        return Tuple(_x, _y, _z, 1.f);
    }

    static Tuple Vector(const float _x, const float _y, const float _z)
    {
        return Tuple(_x, _y, _z, 0.f);
    }

#pragma region Addition

    Tuple operator+(const Tuple& other) const
    {
        return Tuple(
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w);
    }

    Tuple& operator+=(const Tuple& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

#pragma endregion 

#pragma region Subtraction
    
    Tuple operator-(const Tuple& other) const
    {
        return Tuple(
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w);
    }

    Tuple& operator-=(const Tuple& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

#pragma endregion
    
#pragma region Multiplication
    
    Tuple operator*(const float scalar) const
    {
        return Tuple(
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar);
    }

    Tuple& operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

#pragma endregion

#pragma region Division

    Tuple operator/(const float scalar) const
    {
        return Tuple(
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar);
    }

    Tuple& operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

#pragma endregion

    Tuple operator-() const
    {
        return Tuple(-x, -y, -z, -w);
    }

    bool operator==(const Tuple& other) const
    {
        return std::fabsf(x - other.x) < FLT_EPSILON &&
                std::fabsf(y - other.y) < FLT_EPSILON &&
                std::fabsf(z - other.z) < FLT_EPSILON &&
                std::fabsf(w - other.w) < FLT_EPSILON;
    }

    bool operator!=(const Tuple& other) const
    {
        return !(*this == other);
    }

    float Magnitude() const
    {
        return std::sqrt(
            x * x +
            y * y +
            z * z);
    }

    Tuple Normalize() const
    {
        const float magnitude = Magnitude();
        return Tuple(x / magnitude, y / magnitude, z / magnitude, w);
    }

    float Dot(const Tuple& other) const
    {
        return  x * other.x +
                y * other.y +
                z * other.z +
                w * other.w;
    }

    Tuple Cross(const Tuple& other) const
    {
        return Tuple(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
            0.f);
    }
};

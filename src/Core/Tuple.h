#pragma once

#include <cmath>

#include "Utilities/Constants.h"

struct Tuple
{
public:
    float x;
    float y;
    float z;
    float w;

    Tuple() : x(0), y(0), z(0), w(0) {}
	Tuple(const Tuple& other) : Tuple(other.x, other.y, other.z, other.w) {}
    Tuple(const float _x, const float _y, const float _z, const float _w) :
        x(_x), y(_y), z(_z), w(_w) {}

	static Tuple Zero()
	{
		return Tuple(0, 0, 0, 0);
	}

#pragma region Equality

    bool operator==(const Tuple& other) const
    {
        return std::fabsf(x - other.x) < EPSILON &&
                std::fabsf(y - other.y) < EPSILON &&
                std::fabsf(z - other.z) < EPSILON &&
                std::fabsf(w - other.w) < EPSILON;
    }

    bool operator!=(const Tuple& other) const
    {
        return !(*this == other);
    }

#pragma endregion

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

    Tuple operator*(const Tuple& other) const
    {
        return Tuple(
            x * other.x,
            y * other.y,
            z * other.z,
            w * other.w);
    }

    Tuple& operator*=(const Tuple& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
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
};

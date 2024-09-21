#pragma once

#include "Tuple.h"

struct Vector : public Tuple
{
	Vector(const float x, const float y, const float z) : Tuple(x, y, z, 0.f) {}
	Vector(const Tuple& tuple) : Tuple(tuple.x, tuple.y, tuple.z, 0.f) {}

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
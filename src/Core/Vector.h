#pragma once

#include "Tuple.h"

struct Vector : public Tuple
{
	Vector(const float _x, const float _y, const float _z) : Tuple(_x, _y, _z, 0.f) {}
	Vector(const Tuple& tuple) : Tuple(tuple.x, tuple.y, tuple.z, 0.f) {}

	static Vector Zero()
	{
		return Vector(0, 0, 0);
	}

	[[nodiscard]] float Magnitude() const
    {
        return std::sqrt(
            x * x +
            y * y +
            z * z);
    }

    [[nodiscard]] Vector Normalized() const
    {
        const float magnitude = Magnitude();
        return Vector(x / magnitude, y / magnitude, z / magnitude);
    }

	void Normalize()
	{
		const float magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

    [[nodiscard]] float Dot(const Tuple& other) const
    {
        return  x * other.x +
                y * other.y +
                z * other.z +
                w * other.w;
    }

    [[nodiscard]] Vector Cross(const Tuple& other) const
    {
        return Vector(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

	[[nodiscard]] Vector Reflect(const Vector& normal) const
	{
		return *this - normal * 2.f * Dot(normal);
	}

#pragma region Subtraction

	Vector operator-(const Vector& other) const
	{
		return Vector(
			x - other.x,
			y - other.y,
			z - other.z);
	}

	Vector operator-=(const Vector& other) const
	{
		return Vector(
			x - other.x,
			y - other.y,
			z - other.z);
	}

#pragma endregion

	Vector operator-() const
	{
		return Vector(-x, -y, -z);
    }
};
#pragma once

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"

class Ray
{
public:
	[[nodiscard]] const Point& GetOrigin() const { return origin; }
	[[nodiscard]] const Vector& GetDirection() const { return direction; }

	Ray(const Point& origin, const Vector& direction) : 
		origin(origin), direction(direction) {}

	[[nodiscard]] Point Position(const float t) const
	{
		return origin + direction * t;
	}

	[[nodiscard]] Ray Transform(const Matrix<4, 4>& transformation) const
	{
		return Ray(transformation * origin, transformation * direction);
	}

	bool operator==(const Ray& other) const
	{
		return origin == other.origin && direction == other.direction;
	}

	bool operator!=(const Ray& other) const
	{
		return !(*this == other);
	}

private:
	Point origin;
	Vector direction;
};
#pragma once

#include "Tuple.h"
#include "Vector.h"

struct Point : public Tuple
{
	Point(const float x, const float y, const float z) : Tuple(x, y, z, 1.f) {}
	Point(const Tuple& tuple) : Tuple(tuple.x, tuple.y, tuple.z, 1.f) {}

	static Point Zero()
	{
		return Point(0, 0, 0);
	}

	Vector operator-(const Point& other) const
	{
		return Vector(x - other.x, y - other.y, z - other.z);
	}
};

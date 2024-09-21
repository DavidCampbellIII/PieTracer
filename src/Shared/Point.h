#pragma once

#include "Tuple.h"

struct Point : public Tuple
{
	Point(const float x, const float y, const float z) : Tuple(x, y, z, 1.f) {}
	Point(const Tuple& tuple) : Tuple(tuple.x, tuple.y, tuple.z, 1.f) {}
};
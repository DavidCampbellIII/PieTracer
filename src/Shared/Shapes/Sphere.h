#pragma once

#include "../Traceable.h"

class Sphere : public Traceable
{
public:
	Sphere() : Traceable() {}
	Sphere(const Matrix<4, 4>& _transform) : Traceable(_transform) {}

	[[nodiscard]] std::array<Intersection, 2> Intersect(const Ray& ray) const override;
};

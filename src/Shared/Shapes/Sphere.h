#pragma once

#include "../Traceable.h"

class Sphere : public Traceable
{
public:
	Sphere() : Traceable() {}
	Sphere(const Matrix<4, 4>& _transform) : Traceable(_transform) {}

protected:
	[[nodiscard]] Vector NormalAt_Internal(const Point& worldPoint) const override;
	[[nodiscard]] std::array<Intersection, 2> Intersect_Internal(const Ray& ray) const override;
};

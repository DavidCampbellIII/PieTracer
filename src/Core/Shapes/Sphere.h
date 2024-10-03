#pragma once

#include "../Traceable.h"

class Sphere : public Traceable
{
public:
	Sphere() : Traceable() {}
	Sphere(const Matrix<4, 4>& _transform) : Traceable(_transform) {}
	Sphere(const Matrix<4, 4>& _transform, const std::shared_ptr<Material>& _material) : 
		Traceable(_transform, _material) {}

protected:
	[[nodiscard]] Vector NormalAt_Internal(const Point& worldPoint) const override;
	[[nodiscard]] std::vector<Intersection> Intersect_Internal(const Ray& ray) const override;
};

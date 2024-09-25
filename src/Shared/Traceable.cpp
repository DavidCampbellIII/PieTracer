#include "Traceable.h"

#include "Ray.h"
#include "Intersection.h"

Vector Traceable::NormalAt(const Point& worldPoint) const
{
	const Point objectPoint = transform.Inverse() * worldPoint;
	const Vector objectNormal = NormalAt_Internal(objectPoint);
	const Vector worldNormal = transform.Inverse().Transpose() * objectNormal;
	return worldNormal.Normalize();
}

std::array<Intersection, 2> Traceable::Intersect(const Ray& ray) const
{
	const Ray transformedRay = ray.Transform(transform.Inverse());
	return Intersect_Internal(transformedRay);
}

#include "Traceable.h"

#include "Ray.h"
#include "Intersection.h"

std::array<Intersection, 2> Traceable::Intersect(const Ray& ray) const
{
	const Ray transformedRay = ray.Transform(transform.Inverse());
	return Intersect_Internal(transformedRay);
}
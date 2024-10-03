#include "Sphere.h"

#include "../Point.h"
#include "../Ray.h"
#include "../Intersection.h"

Vector Sphere::NormalAt_Internal(const Point& worldPoint) const
{
	return worldPoint - Point::Zero();
}

std::vector<Intersection> Sphere::Intersect_Internal(const Ray& ray) const
{
	const Vector sphereToRay = ray.GetOrigin() - Point::Zero();
	const float a = ray.GetDirection().Dot(ray.GetDirection());
	const float b = 2.f * ray.GetDirection().Dot(sphereToRay);
	const float c = sphereToRay.Dot(sphereToRay) - 1.f;
	const float discriminant = b * b - 4.f * a * c;

	// If the discriminant is negative, there are no real roots meaning the ray missed the sphere and there are no intersections
	if (discriminant < 0.f)
	{
		return {Intersection::NO_INTERSECTION, Intersection::NO_INTERSECTION};
	}

	const std::shared_ptr<Traceable> traceable = std::make_shared<Sphere>(*this);
	const float sqrtDiscriminant = std::sqrt(discriminant);
	const float t1 = (-b - sqrtDiscriminant) / (2.f * a);
	const float t2 = (-b + sqrtDiscriminant) / (2.f * a);
	return {Intersection(t1, traceable), Intersection(t2, traceable)};
}

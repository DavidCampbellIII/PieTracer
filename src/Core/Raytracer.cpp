#include "Raytracer.h"

#include "Intersection.h"

std::shared_ptr<Intersection> Raytracer::Hit(const std::vector<Intersection>& intersections) const
{
	float minT = std::numeric_limits<float>::max();
	std::shared_ptr<Intersection> closestIntersection = nullptr;
	for (const Intersection& intersection : intersections)
	{
		const float t = intersection.GetT();
		if (t < minT && t > 0)
		{
			minT = t;
			closestIntersection = std::make_shared<Intersection>(intersection);
		}
	}
	return closestIntersection;
}

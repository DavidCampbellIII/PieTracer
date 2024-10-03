#include "Raytracer.h"

#include "Canvas.h"
#include "Color.h"
#include "Intersection.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include "World.h"
#include "Camera.h"
#include "Traceable.h"
#include <HitRecord.h>

#include "Material.h"

void Raytracer::Render(const World& world, const Camera& camera, Canvas& canvas) const
{
	//TODO implement camera

	const float wallSize = 10.f;
	const float wallZ = 10.f;

	const float pixelSize = wallSize / static_cast<float>(canvas.GetWidth());
	const float half = wallSize / 2.f;

	const Point rayOrigin = Point(0, -1, -5);
	for (int y = 0; y < canvas.GetHeight(); ++y)
    {
		const float worldY = half - pixelSize * y;
		for (int x = 0; x < canvas.GetWidth(); ++x)
		{
			const float worldX = -half + pixelSize * x;
			const Point position = Point(worldX, worldY, wallZ);
			const Vector direction = (position - rayOrigin).Normalized();
			const Ray ray(rayOrigin, direction);
			
			const Color color = CastRay(ray, world);
			canvas.WritePixel(x, y, color);
		}
	}
}

const Intersection* Raytracer::Hit(const std::vector<Intersection>& intersections) const
{
	float minT = std::numeric_limits<float>::max();
	const Intersection* closestIntersection = nullptr;
	for (const Intersection& intersection : intersections)
	{
		const float t = intersection.GetT();
		if (t < minT && t > 0)
		{
			minT = t;
			closestIntersection = &intersection;
		}
	}
	return closestIntersection;
}

Color Raytracer::CastRay(const Ray& ray, const World& world) const
{
	std::vector<Intersection> allIntersections;
	for (const std::shared_ptr<Traceable>& object : world.GetTraceables())
	{
		const std::vector<Intersection> intersections = object->Intersect(ray);
		allIntersections.insert(allIntersections.end(), intersections.begin(), intersections.end());
	}
	const Intersection* hit = Hit(allIntersections);


	Color finalColor = backgroundColor;
	if (hit)
	{
		const std::shared_ptr<Traceable> traceable = hit->GetTraceable();
		const Point hitPoint = ray.Position(hit->GetT());
		const Vector normal = traceable->NormalAt(hitPoint);
		const Vector eye = -ray.GetDirection();

		finalColor = ShadeHit(world, HitRecord(traceable, hitPoint, normal, eye));
	}
	return finalColor;
}

Color Raytracer::ShadeHit(const World& world, const HitRecord& hit) const
{
	const std::shared_ptr<Traceable> traceable = hit.GetTraceable();
	const Point hitPoint = hit.GetHitPoint();
	const Vector eye = hit.GetEye();
	const Vector normal = hit.GetNormal();

	Color finalColor = Color(0, 0, 0);
	for (const std::shared_ptr<Light>& light : world.GetLights())
	{
		finalColor += traceable->GetMaterial()->Lighting(*light, hitPoint, eye, normal);
	}

	return finalColor;
}

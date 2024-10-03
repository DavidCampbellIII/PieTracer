#pragma once

#include <vector>
#include "Color.h"


struct HitRecord;
class Intersection;
class World;
class Camera;
class Canvas;
class Ray;

class Raytracer
{
public:
	Color backgroundColor;

	Raytracer() = default;

	void Render(const World& world, const Camera& camera, Canvas& canvas) const;

	
private:
	[[nodiscard]] const Intersection* Hit(const std::vector<Intersection>& intersections) const;
	Color CastRay(const Ray& ray, const World& world) const;
	Color ShadeHit(const World& world, const HitRecord& hit) const;
};
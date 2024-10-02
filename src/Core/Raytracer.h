#pragma once

#include <vector>
#include <memory>

class Intersection;

class Raytracer
{
public:
	Raytracer() = default;

	[[nodiscard]] std::shared_ptr<Intersection> Hit(const std::vector<Intersection>& intersections) const;
private:

};
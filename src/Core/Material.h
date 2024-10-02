#pragma once

#include "Color.h"

struct Light;
struct Point;
struct Vector;

class Material
{
public:
	Color color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;

	Material() : 
		color(Color(1.f, 1.f, 1.f)), ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f) {}
	Material(const Color& _color, const float _ambient, const float _diffuse, const float _specular, const float _shininess) :
		color(_color), ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess) {}

	[[nodiscard]] Color Lighting(const Light& light, const Point& position, const Vector& eye, const Vector& normal) const;
};

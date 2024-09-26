#pragma once
#include "Point.h"
#include "Color.h"

struct Light
{
public:
	Point position;
	Color color;

	Light(const Point& _position, const Color& _color) : 
		position(_position), color(_color) {}
};
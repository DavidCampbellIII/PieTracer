#pragma once

struct Point;
struct Color;

struct Light
{
public:
	Point position;
	Color color;

	Light(const Point& _position, const Color& _color) : 
		position(_position), color(_color) {}
};
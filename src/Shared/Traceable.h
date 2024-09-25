#pragma once

#include "Matrix.h"

class Ray;
class Intersection;
struct Point;
struct Vector;

class Traceable
{
public:
	[[nodiscard]] Matrix<4, 4> GetTransform() const { return transform; }
	void SetTransform(const Matrix<4, 4>& _transform) { transform = _transform; }

	Traceable() : transform(Matrix<4, 4>::Identity()) {}
	Traceable(const Matrix<4, 4>& _transform) : transform(_transform) {}

	[[nodiscard]] virtual Vector NormalAt(const Point& worldPoint) const;
	[[nodiscard]] std::array<Intersection, 2> Intersect(const Ray& ray) const;

	[[nodiscard]] bool operator==(const Traceable& other) const { return id == other.id; }
	[[nodiscard]] bool operator!=(const Traceable& other) const { return !(*this == other); }

protected:
	[[nodiscard]] virtual Vector NormalAt_Internal(const Point& worldPoint) const = 0;
	[[nodiscard]] virtual std::array<Intersection, 2> Intersect_Internal(const Ray& ray) const = 0;

private:
	static inline int nextId{0};
	const int id{nextId++};
	Matrix<4, 4> transform;
};

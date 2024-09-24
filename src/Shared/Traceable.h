#pragma once

#include "Matrix.h"

class Ray;
class Intersection;

class Traceable
{
public:
	[[nodiscard]] Matrix<4, 4> GetTransform() const { return transform; }
	void SetTransform(const Matrix<4, 4>& _transform) { transform = _transform; }

	Traceable() : transform(Matrix<4, 4>::Identity()) {}
	Traceable(const Matrix<4, 4>& _transform) : transform(_transform) {}

	[[nodiscard]] virtual std::array<Intersection, 2> Intersect(const Ray& ray) const = 0;

	[[nodiscard]] bool operator==(const Traceable& other) const { return id == other.id; }
	[[nodiscard]] bool operator!=(const Traceable& other) const { return !(*this == other); }

private:
	static inline int nextId{0};
	const int id{nextId++};
	Matrix<4, 4> transform;
};
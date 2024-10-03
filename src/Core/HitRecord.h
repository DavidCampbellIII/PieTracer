#pragma once

#include <memory>

#include "Point.h"
#include "Traceable.h"
#include "Vector.h"

struct HitRecord
{
	[[nodiscard]] std::shared_ptr<Traceable> GetTraceable() const { return traceable; }
	[[nodiscard]] Point GetHitPoint() const { return hitPoint; }
	[[nodiscard]] Vector GetNormal() const { return normal; }
	[[nodiscard]] Vector GetEye() const { return eye; }

	HitRecord(const std::shared_ptr<Traceable>& _traceable, Point _hitPoint, Vector _normal, Vector _eye) :
		traceable(_traceable), hitPoint(std::move(_hitPoint)), normal(std::move(_normal)), eye(std::move(_eye))
	{}

private:
	std::shared_ptr<Traceable> traceable;
	Point hitPoint;
	Vector normal;
	Vector eye;
};
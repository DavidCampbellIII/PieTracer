#pragma once  

#include <memory>
#include <cmath>

#include "Utilities/Constants.h"

class Traceable;

class Intersection
{  
public:  
	static const Intersection NO_INTERSECTION;

	[[nodiscard]] float GetT() const { return t; }
	[[nodiscard]] std::shared_ptr<Traceable> GetTraceable() const { return traceable; }

	Intersection() : t(0), traceable(nullptr) {}
	Intersection(const float _t, const std::shared_ptr<Traceable>& _traceable) : 
		t(_t), traceable(_traceable) {}

	[[nodiscard]] bool operator==(const Intersection& other) const 
	{ 
		return std::fabsf(t - other.t) < EPSILON && traceable == other.traceable; 
	}

	[[nodiscard]] bool operator!=(const Intersection& other) const 
	{ 
		return !(*this == other); 
	}

private:
   float t;  
   std::shared_ptr<Traceable> traceable;
};

#include <catch2/catch_all.hpp>
#include "../src/Shared/Matrix.h"
#include "../src/Shared/Tuple.h"
#include <cmath>

#include "Point.h"
#include "Vector.h"

using namespace Catch::Matchers;

TEST_CASE("Ray creation", "[rays]")
{
	const Point origin(1, 2, 3);
	const Vector direction(4, 5, 6);
	const Ray r(origin, direction);
	REQUIRE(r.Origin() == origin);
	REQUIRE(r.Direction() == direction);
}

TEST_CASE("Ray position", "[rays]")
{
	const Ray r(Point(2, 3, 4), Vector(1, 0, 0));
	REQUIRE(r.Position(0) == Point(2, 3, 4));
	REQUIRE(r.Position(1) == Point(3, 3, 4));
	REQUIRE(r.Position(-1) == Point(1, 3, 4));
	REQUIRE(r.Position(2.5) == Point(4.5, 3, 4));
}

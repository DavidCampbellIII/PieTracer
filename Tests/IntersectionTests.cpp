#include <catch2/catch_all.hpp>
#include "../src/Core/Matrix.h"
#include "../src/Core/Tuple.h"
#include <cmath>
#pragma once
#include <optional>

#include "Intersection.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include "Shapes/Sphere.h"
#include <Raytracer.h>

using namespace Catch::Matchers;

TEST_CASE("Ray creation", "[rays]")
{
	const Point origin(1, 2, 3);
	const Vector direction(4, 5, 6);
	const Ray r(origin, direction);
	REQUIRE(r.GetOrigin() == origin);
	REQUIRE(r.GetDirection() == direction);
}

TEST_CASE("Ray position", "[rays]")
{
	const Ray r(Point(2, 3, 4), Vector(1, 0, 0));
	REQUIRE(r.Position(0) == Point(2, 3, 4));
	REQUIRE(r.Position(1) == Point(3, 3, 4));
	REQUIRE(r.Position(-1) == Point(1, 3, 4));
	REQUIRE(r.Position(2.5) == Point(4.5, 3, 4));
}

TEST_CASE("Sphere intersection", "[sphere intersection]")
{
	const Sphere s;

	SECTION("Sphere intersection at two points")
	{
		const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
		const std::array<Intersection, 2> xs = s.Intersect(r);
		REQUIRE_THAT(xs[0].GetT(), WithinRel(4.0f));
		REQUIRE_THAT(xs[1].GetT(), WithinRel(6.0f));
	}

	SECTION("Sphere intersection at a tangent")
	{
		const Ray r(Point(0, 1, -5), Vector(0, 0, 1));
		const std::array<Intersection, 2> xs = s.Intersect(r);
		REQUIRE_THAT(xs[0].GetT(), WithinRel(5.0f));
		REQUIRE_THAT(xs[1].GetT(), WithinRel(5.0f));
	}

	SECTION("Ray misses sphere")
	{
		const Ray r(Point(0, 2, -5), Vector(0, 0, 1));
		const std::array<Intersection, 2> xs = s.Intersect(r);
		REQUIRE(xs[0] == Intersection::NO_INTERSECTION);
		REQUIRE(xs[1] == Intersection::NO_INTERSECTION);
	}

	SECTION("Ray originates inside sphere")
	{
		const Ray r(Point(0, 0, 0), Vector(0, 0, 1));
		const std::array<Intersection, 2> xs = s.Intersect(r);
		REQUIRE_THAT(xs[0].GetT(), WithinRel(-1.0f));
		REQUIRE_THAT(xs[1].GetT(), WithinRel(1.0f));
	}

	SECTION("Sphere is behind ray")
	{
		const Ray r(Point(0, 0, 5), Vector(0, 0, 1));
		const std::array<Intersection, 2> xs = s.Intersect(r);
		REQUIRE_THAT(xs[0].GetT(), WithinRel(-6.0f));
		REQUIRE_THAT(xs[1].GetT(), WithinRel(-4.0f));
	}
}

TEST_CASE("Aggregating intersections", "[intersections]")
{
	const Sphere s;
	const Intersection i1(1, std::make_shared<Sphere>(s));
	const Intersection i2(2, std::make_shared<Sphere>(s));
	const std::vector<Intersection> xs = { i1, i2 };

	SECTION("Intersection t values are set")
	{
		REQUIRE(xs.size() == 2);
		REQUIRE(xs[0].GetT() == 1.f);
		REQUIRE(xs[1].GetT() == 2.f);
	}

	SECTION("Intersected object is set")
	{
		REQUIRE(xs[0].GetTraceable() == i1.GetTraceable());
		REQUIRE(xs[1].GetTraceable() == i2.GetTraceable());
	}
}

TEST_CASE("Hit when all intersections have positive t", "[intersections]")
{
	const Sphere s;
	const Raytracer raytracer;

	SECTION("All intersections have positive t")
	{
		const Intersection i1(1, std::make_shared<Sphere>(s));
		const Intersection i2(2, std::make_shared<Sphere>(s));
		const std::vector<Intersection> xs = { i1, i2 };
		const std::shared_ptr<Intersection> i = raytracer.Hit(xs);
		REQUIRE(i);
		REQUIRE(*i.get() == i1);
	}
	
	SECTION("Some intersections have negative t")
	{
		const Intersection i1(-1, std::make_shared<Sphere>(s));
		const Intersection i2(1, std::make_shared<Sphere>(s));
		const std::vector<Intersection> xs = { i1, i2 };
		const std::shared_ptr<Intersection> i = raytracer.Hit(xs);
		REQUIRE(i);
		REQUIRE(*i.get() == i2);
	}

	SECTION("All intersections have negative t")
	{
		const Intersection i1(-2, std::make_shared<Sphere>(s));
		const Intersection i2(-1, std::make_shared<Sphere>(s));
		const std::vector<Intersection> xs = { i1, i2 };
		const std::shared_ptr<Intersection> i = raytracer.Hit(xs);
		REQUIRE(!i);
	}

	SECTION("Intersections are sorted by t value")
	{
		const Intersection i1(5, std::make_shared<Sphere>(s));
		const Intersection i2(7, std::make_shared<Sphere>(s));
		const Intersection i3(-3, std::make_shared<Sphere>(s));
		const Intersection i4(2, std::make_shared<Sphere>(s));
		const std::vector<Intersection> xs = { i1, i2, i3, i4 };
		const std::shared_ptr<Intersection> i = raytracer.Hit(xs);
		REQUIRE(i);
		REQUIRE(*i.get() == i4);
	}
}

TEST_CASE("Intersecting scaled sphere with ray", "[intersections]")
{
	const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	const Sphere s(Matrix<4, 4>::Scaling(2, 2, 2));
	const std::array<Intersection, 2> xs = s.Intersect(r);
	REQUIRE(xs[0].GetT() == 3);
	REQUIRE(xs[1].GetT() == 7);
}

TEST_CASE("Intersecting translated sphere with ray", "[intersections]")
{
	const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	const Sphere s(Matrix<4, 4>::Translation(5, 0, 0));
	const std::array<Intersection, 2> xs = s.Intersect(r);
	REQUIRE(xs[0] == Intersection::NO_INTERSECTION);
	REQUIRE(xs[1] == Intersection::NO_INTERSECTION);
}

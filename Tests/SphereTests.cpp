#pragma once
#include <catch2/catch_all.hpp>
#include "../src/Core/Matrix.h"
#include "../src/Core/Vector.h"
#include "../src/Core/Point.h"
#include "Shapes/Sphere.h"

using namespace Catch::Matchers;


TEST_CASE("Sphere initialisation", "[spheres]")
{
	const Sphere s;
	REQUIRE(s.GetTransform() == Matrix<4, 4>::Identity());
}

TEST_CASE("Normal on a sphere at a point on the x-axis", "[spheres]")
{
	const Sphere s;
	const Vector n = s.NormalAt(Point(1, 0, 0));
	REQUIRE(n == Vector(1, 0, 0));
}

TEST_CASE("Normal on a sphere at a point on the y-axis", "[spheres]")
{
	const Sphere s;
	const Vector n = s.NormalAt(Point(0, 1, 0));
	REQUIRE(n == Vector(0, 1, 0));
}

TEST_CASE("Normal on a sphere at a point on the z-axis", "[spheres]")
{
	const Sphere s;
	const Vector n = s.NormalAt(Point(0, 0, 1));
	REQUIRE(n == Vector(0, 0, 1));
}

TEST_CASE("Normal on a sphere at a non-axial point", "[spheres]")
{
	const float value = std::sqrt(3) / 3;
	const Sphere s;
	const Vector n = s.NormalAt(Point(value, value, value));
	REQUIRE(n == Vector(value, value, value));
}

TEST_CASE("Normal is a normalized vector", "[spheres]")
{
	const float value = std::sqrt(3) / 3;
	const Sphere s;
	const Vector n = s.NormalAt(Point(value, value, value));
	REQUIRE(n == n.Normalized());
}

TEST_CASE("Computing the normal on a translated sphere", "[spheres]")
{
	const Sphere s(Matrix<4, 4>::Translation(0, 1, 0));
	const Vector n = s.NormalAt(Point(0, 1.70711f, -0.70711f));
	REQUIRE(n == Vector(0, 0.70711f, -0.70711f));
}

TEST_CASE("Computing the normal on a transformed sphere", "[spheres]")
{
	const Matrix<4, 4> scaling = Matrix<4, 4>::Scaling(1, 0.5f, 1);
	const Matrix<4, 4> rotation = Matrix<4, 4>::RotationZ(PI / 5);
	const Sphere s(scaling * rotation);

	const float val = std::sqrt(2) / 2;
	const Vector n = s.NormalAt(Point(0, val, -val));
	REQUIRE(n == Vector(0, 0.97014f, -0.24254f));
}
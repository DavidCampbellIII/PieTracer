#include <catch2/catch_all.hpp>
#include "../src/Shared/Matrix.h"
#include "../src/Shared/Tuple.h"
#include <cmath>

using namespace Catch::Matchers;

TEST_CASE("Translation", "[transformations]")
{
	SECTION("Multiplying by translation matrix")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Translation(5, -3, 2);
		const Tuple p = Tuple::Point(-3, 4, 5);
		REQUIRE(transform * p == Tuple::Point(2, 1, 7));
	}

	SECTION("Multiplying by inverse of translation matrix")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Translation(5, -3, 2);
		const Matrix<4, 4> inv = transform.Inverse();
		const Tuple p = Tuple::Point(-3, 4, 5);
		REQUIRE(inv * p == Tuple::Point(-8, 7, 3));
	}
	
	SECTION("Translation does not affect vectors")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Translation(5, -3, 2);
		const Tuple v = Tuple::Vector(-3, 4, 5);
		REQUIRE(transform * v == v);
	}
}

TEST_CASE("Scaling", "[transformations]")
{
	SECTION("Scaling a point")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Scaling(2, 3, 4);
		const Tuple p = Tuple::Point(-4, 6, 8);
		REQUIRE(transform * p == Tuple::Point(-8, 18, 32));
	}

	SECTION("Scaling a vector")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Scaling(2, 3, 4);
		const Tuple v = Tuple::Vector(-4, 6, 8);
		REQUIRE(transform * v == Tuple::Vector(-8, 18, 32));
	}

	SECTION("Multiplying by inverse of scaling matrix")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Scaling(2, 3, 4);
		const Matrix<4, 4> inv = transform.Inverse();
		const Tuple p = Tuple::Point(-4, 6, 8);
		REQUIRE(inv * p == Tuple::Point(-2, 2, 2));
	}

	SECTION("Reflection is scaling by a negative value")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Scaling(-1, 1, 1);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(-2, 3, 4));
	}
}

TEST_CASE("Rotation", "[transformations]")
{
	SECTION("Rotating a point around the x axis")
	{
		const Tuple p = Tuple::Point(0, 1, 0);
		const Matrix<4, 4> halfQuarter = Matrix<4, 4>::RotationX(PI_QUARTER);
		const Matrix<4, 4> fullQuarter = Matrix<4, 4>::RotationX(PI_HALF);
		REQUIRE(halfQuarter * p == Tuple::Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
		REQUIRE(fullQuarter * p == Tuple::Point(0, 0, 1));
	}

	SECTION("The inverse of an x-rotation rotates in the opposite direction")
	{
		const Tuple p = Tuple::Point(0, 1, 0);
		const Matrix<4, 4> halfQuarter = Matrix<4, 4>::RotationX(PI_QUARTER);
		const Matrix<4, 4> inv = halfQuarter.Inverse();
		REQUIRE(inv * p == Tuple::Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
	}

	SECTION("Rotating a point around the y axis")
	{
		const Tuple p = Tuple::Point(0, 0, 1);
		const Matrix<4, 4> halfQuarter = Matrix<4, 4>::RotationY(PI_QUARTER);
		const Matrix<4, 4> fullQuarter = Matrix<4, 4>::RotationY(PI_HALF);
		REQUIRE(halfQuarter * p == Tuple::Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
		REQUIRE(fullQuarter * p == Tuple::Point(1, 0, 0));
	}

	SECTION("Rotating a point around the z axis")
	{
		const Tuple p = Tuple::Point(0, 1, 0);
		const Matrix<4, 4> halfQuarter = Matrix<4, 4>::RotationZ(PI_QUARTER);
		const Matrix<4, 4> fullQuarter = Matrix<4, 4>::RotationZ(PI_HALF);
		REQUIRE(halfQuarter * p == Tuple::Point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
		REQUIRE(fullQuarter * p == Tuple::Point(-1, 0, 0));
	}
}

TEST_CASE("Shearing", "[transformations]")
{
	SECTION("Shearing transformation moves x in proportion to y")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Shearing(1, 0, 0, 0, 0, 0);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(5, 3, 4));
	}

	SECTION("Shearing transformation moves x in proportion to z")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Shearing(0, 1, 0, 0, 0, 0);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(6, 3, 4));
	}

	SECTION("Shearing transformation moves y in proportion to x")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Shearing(0, 0, 1, 0, 0, 0);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(2, 5, 4));
	}

	SECTION("Shearing transformation moves y in proportion to z")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Shearing(0, 0, 0, 1, 0, 0);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(2, 7, 4));
	}

	SECTION("Shearing transformation moves z in proportion to x")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Shearing(0, 0, 0, 0, 1, 0);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(2, 3, 6));
	}

	SECTION("Shearing transformation moves z in proportion to y")
	{
		const Matrix<4, 4> transform = Matrix<4, 4>::Shearing(0, 0, 0, 0, 0, 1);
		const Tuple p = Tuple::Point(2, 3, 4);
		REQUIRE(transform * p == Tuple::Point(2, 3, 7));
	}
}

TEST_CASE("Chaining transformations", "[transformations]")
{
	SECTION("Individual transformations are applied in sequence")
	{
		const Tuple p = Tuple::Point(1, 0, 1);
		const Matrix<4, 4> A = Matrix<4, 4>::RotationX(PI_HALF);
		const Matrix<4, 4> B = Matrix<4, 4>::Scaling(5, 5, 5);
		const Matrix<4, 4> C = Matrix<4, 4>::Translation(10, 5, 7);

		const Tuple p2 = A * p;
		REQUIRE(p2 == Tuple::Point(1, -1, 0));

		const Tuple p3 = B * p2;
		REQUIRE(p3 == Tuple::Point(5, -5, 0));

		const Tuple p4 = C * p3;
		REQUIRE(p4 == Tuple::Point(15, 0, 7));
	}

	SECTION("Chained transformations must be applied in reverse order")
	{
		const Tuple p = Tuple::Point(1, 0, 1);
		const Matrix<4, 4> A = Matrix<4, 4>::RotationX(PI_HALF);
		const Matrix<4, 4> B = Matrix<4, 4>::Scaling(5, 5, 5);
		const Matrix<4, 4> C = Matrix<4, 4>::Translation(10, 5, 7);

		const Matrix<4, 4> T = C * B * A;
		REQUIRE(T * p == Tuple::Point(15, 0, 7));
	}
}
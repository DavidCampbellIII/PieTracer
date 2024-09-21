#include <catch2/catch_all.hpp>
#include "../src/Shared/Point.h"
#include "../src/Shared/Vector.h"

using namespace Catch::Matchers;

TEST_CASE("Create a point", "[tuple]")
{
    const Point a = Point(4, -4, 3);
    REQUIRE(a.x == 4);
    REQUIRE(a.y == -4);
    REQUIRE(a.z == 3);
    REQUIRE(a.w == 1);
}

TEST_CASE("Create a vector", "[tuple]")
{
    const Vector a = Vector(4, -4, 3);
    REQUIRE(a.x == 4);
    REQUIRE(a.y == -4);
    REQUIRE(a.z == 3);
    REQUIRE(a.w == 0);
}

TEST_CASE("Equality", "[tuple]")
{
    const Point a = Point(4, -4, 3);
    const Point b = Point(4, -4, 3);
    const Point c = Point(0, -1, 3);
    REQUIRE(a == b);
    REQUIRE(a != c);
}

TEST_CASE("Addition", "[tuple]")
{
    const Tuple p1 = Tuple(3, -2, 5, 0);
    const Tuple p2 = Tuple(-2, 3, 1, 1);

    SECTION("Tuple and tuple")
    {
        const Tuple result = p1 + p2;
        REQUIRE(result == Tuple(1, 1, 6, 1));
    }
}

TEST_CASE("Subtraction", "[tuple]")
{
    const Point p1 = Point(3, 2, 1);
    const Point p2 = Point(5, 6, 7);

    const Vector v1 = Vector(-2, 1, 0);
    const Vector v2 = Vector(-5, 4, -1);

    SECTION("Point from point")
    {
        const Vector result = p1 - p2;
        REQUIRE(result == Vector(-2, -4, -6));
    }

    SECTION("Vector from point")
    {
        const Point result = p1 - v1;
        REQUIRE(result == Point(5, 1, 1));
    }

    SECTION("Vector from vector")
    {
        const Vector result = v1 - v2;
        REQUIRE(result == Vector(3, -3, 1));
    }
}

TEST_CASE("Negation", "[tuple]")
{
    const Tuple a = Tuple(1, -2, 3, -4);
    const Tuple b = -a;
    REQUIRE(b == Tuple(-1, 2, -3, 4));
}

TEST_CASE("Multiplication", "[tuple]")
{
    const Tuple a = Tuple(1, -2, 3, -4);

    SECTION("Tuple by scalar")
    {
        const Tuple b = a * 3.5f;
        REQUIRE(b == Tuple(3.5, -7, 10.5, -14));
    }

    SECTION("Tuple by fraction")
    {
        const Tuple b = a * 0.5f;
        REQUIRE(b == Tuple(0.5, -1, 1.5, -2));
    }

    SECTION("Tuple by tuple (component-wise)")
    {
        const Tuple b = a * Tuple(1, -2, 3, -4);
        REQUIRE(b == Tuple(1, 4, 9, 16));
    }
}

TEST_CASE("Division", "[tuple]")
{
    const Tuple a = Tuple(1, -2, 3, -4);

    const Tuple b = a / 2;
    REQUIRE(b == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Magnitude", "[tuple]")
{
    const Vector a = Vector(1, 0, 0);
    REQUIRE(a.Magnitude() == 1);

    const Vector b = Vector(0, 1, 0);
    REQUIRE(b.Magnitude() == 1);

    const Vector c = Vector(0, 0, 1);
    REQUIRE(c.Magnitude() == 1);

    const Vector d = Vector(1, 2, 3);
    REQUIRE(d.Magnitude() == sqrtf(14));

    const Vector e = Vector(-1, -2, -3);
    REQUIRE(e.Magnitude() == sqrtf(14));
}

TEST_CASE("Normalization", "[tuple]")
{
    const Vector a = Vector(4, 0, 0).Normalize();
    REQUIRE(a == Vector(1, 0, 0));

    const Vector b = Vector(1, 2, 3).Normalize();
    REQUIRE(b == Vector(1 / sqrtf(14), 2 / sqrtf(14), 3 / sqrtf(14)));
    
    SECTION("Magnitude of normalized vector is 1")
    {
        REQUIRE_THAT(a.Magnitude(), WithinRel(1.f));
        REQUIRE_THAT(b.Magnitude(), WithinRel(1.f));
    }
}

TEST_CASE("Dot product", "[tuple]")
{
    const Vector a = Vector(1, 2, 3);
    const Vector b = Vector(2, 3, 4);

    REQUIRE(a.Dot(b) == 20);
}

TEST_CASE("Cross product", "[tuple]")
{
    const Vector a = Vector(1, 2, 3);
    const Vector b = Vector(2, 3, 4);

    REQUIRE(a.Cross(b) == Vector(-1, 2, -1));
    REQUIRE(b.Cross(a) == Vector(1, -2, 1));
}
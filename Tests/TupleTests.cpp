#include <catch2/catch_all.hpp>
#include "../src/Shared/Tuple.h"

using namespace Catch::Matchers;

TEST_CASE("Create a point", "[tuple]")
{
    const Tuple a = Tuple::Point(4, -4, 3);
    REQUIRE(a.x == 4);
    REQUIRE(a.y == -4);
    REQUIRE(a.z == 3);
    REQUIRE(a.w == 1);
}

TEST_CASE("Create a vector", "[tuple]")
{
    const Tuple a = Tuple::Vector(4, -4, 3);
    REQUIRE(a.x == 4);
    REQUIRE(a.y == -4);
    REQUIRE(a.z == 3);
    REQUIRE(a.w == 0);
}

TEST_CASE("Equality", "[tuple]")
{
    const Tuple a = Tuple::Point(4, -4, 3);
    const Tuple b = Tuple::Point(4, -4, 3);
    const Tuple c = Tuple::Point(0, -1, 3);
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
    const Tuple p1 = Tuple::Point(3, 2, 1);
    const Tuple p2 = Tuple::Point(5, 6, 7);

    const Tuple v1 = Tuple::Vector(-2, 1, 0);
    const Tuple v2 = Tuple::Vector(-5, 4, -1);

    SECTION("Point from point")
    {
        const Tuple result = p1 - p2;
        REQUIRE(result == Tuple::Vector(-2, -4, -6));
    }

    SECTION("Vector from point")
    {
        const Tuple result = p1 - v1;
        REQUIRE(result == Tuple::Point(5, 1, 1));
    }

    SECTION("Vector from vector")
    {
        const Tuple result = v1 - v2;
        REQUIRE(result == Tuple::Vector(3, -3, 1));
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
    const Tuple a = Tuple::Vector(1, 0, 0);
    REQUIRE(a.Magnitude() == 1);

    const Tuple b = Tuple::Vector(0, 1, 0);
    REQUIRE(b.Magnitude() == 1);

    const Tuple c = Tuple::Vector(0, 0, 1);
    REQUIRE(c.Magnitude() == 1);

    const Tuple d = Tuple::Vector(1, 2, 3);
    REQUIRE(d.Magnitude() == sqrtf(14));

    const Tuple e = Tuple::Vector(-1, -2, -3);
    REQUIRE(e.Magnitude() == sqrtf(14));
}

TEST_CASE("Normalization", "[tuple]")
{
    const Tuple a = Tuple::Vector(4, 0, 0).Normalize();
    REQUIRE(a == Tuple::Vector(1, 0, 0));

    const Tuple b = Tuple::Vector(1, 2, 3).Normalize();
    REQUIRE(b == Tuple::Vector(1 / sqrtf(14), 2 / sqrtf(14), 3 / sqrtf(14)));
    
    SECTION("Magnitude of normalized vector is 1")
    {
        REQUIRE_THAT(a.Magnitude(), WithinRel(1.f));
        REQUIRE_THAT(b.Magnitude(), WithinRel(1.f));
    }
}

TEST_CASE("Dot product", "[tuple]")
{
    const Tuple a = Tuple::Vector(1, 2, 3);
    const Tuple b = Tuple::Vector(2, 3, 4);

    REQUIRE(a.Dot(b) == 20);
}

TEST_CASE("Cross product", "[tuple]")
{
    const Tuple a = Tuple::Vector(1, 2, 3);
    const Tuple b = Tuple::Vector(2, 3, 4);

    REQUIRE(a.Cross(b) == Tuple::Vector(-1, 2, -1));
    REQUIRE(b.Cross(a) == Tuple::Vector(1, -2, 1));
}
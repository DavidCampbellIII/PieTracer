#include <catch2/catch_all.hpp>
#include "../src/Core/Color.h"
#include <iostream>

using namespace Catch::Matchers;

TEST_CASE("Color Equality", "[colors]")
{
    const Color a = Color(0.9f, 0.6f, 0.75f);
    const Color b = Color(0.9f, 0.6f, 0.75f);
    const Color c = Color(0.7f, 0.1f, 0.2f);

    REQUIRE(a == b);
    REQUIRE(a != c);
}

TEST_CASE("Color Addition", "[colors]")
{
    const Color a = Color(0.9f, 0.6f, 0.75f);
    const Color b = Color(0.7f, 0.1f, 0.2f);

    const Color result = a + b;
    const Color expected = Color(1.6f, 0.7f, 0.95f);
    REQUIRE(result == expected);

    Color aCopy = a;
    aCopy += b;
    REQUIRE(aCopy == expected);
}

TEST_CASE("Color Subtraction", "[colors]")
{
    const Color a = Color(0.9f, 0.6f, 0.75f);
    const Color b = Color(0.7f, 0.1f, 0.2f);

    const Color result = a - b;
    REQUIRE(result == Color(0.2f, 0.5f, 0.55f));

    Color aCopy = a;
    aCopy -= b;
    REQUIRE(aCopy == Color(0.2f, 0.5f, 0.55f));
}

TEST_CASE("Color Multiplication", "[colors]")
{
    const Color a = Color(1, 0.2f, 0.4f);
    const Color b = Color(0.9f, 1, 0.1f);

    const Color result = a * b;
    REQUIRE(result == Color(0.9f, 0.2f, 0.04f));

    Color aCopy = a;
    aCopy *= b;
    REQUIRE(aCopy == Color(0.9f, 0.2f, 0.04f));
}
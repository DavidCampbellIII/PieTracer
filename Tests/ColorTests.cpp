#include "catch_amalgamated.hpp"
#include "../src/Color.h"

using namespace Catch::Matchers;

TEST_CASE("Equality", "[colors]")
{
    const Color a = Color(0.9f, 0.6f, 0.75f);
    const Color b = Color(0.9f, 0.6f, 0.75f);
    const Color c = Color(0.7f, 0.1f, 0.2f);

    REQUIRE(a == b);
    REQUIRE(a != c);
}

TEST_CASE("Addition", "[colors]")
{
    const Color a = Color(0.9f, 0.6f, 0.75f);
    const Color b = Color(0.7f, 0.1f, 0.2f);

    const Color result = a + b;
    REQUIRE(result == Color(1.6f, 0.7f, 0.95f));

    Color aCopy = a;
    aCopy += b;
    REQUIRE(aCopy == Color(1.6f, 0.7f, 0.95f));
}

TEST_CASE("Subtraction", "[colors]")
{
    const Color a = Color(0.9f, 0.6f, 0.75f);
    const Color b = Color(0.7f, 0.1f, 0.2f);

    const Color result = a - b;
    REQUIRE(result == Color(0.2f, 0.5f, 0.55f));

    Color aCopy = a;
    aCopy -= b;
    REQUIRE(aCopy == Color(0.2f, 0.5f, 0.55f));
}

TEST_CASE("Multiplication", "[colors]")
{
    const Color a = Color(1, 0.2f, 0.4f);
    const Color b = Color(0.9f, 1, 0.1f);

    const Color result = a * b;
    REQUIRE(result == Color(0.9f, 0.2f, 0.04f));

    Color aCopy = a;
    aCopy *= b;
    REQUIRE(aCopy == Color(0.9f, 0.2f, 0.04f));
}
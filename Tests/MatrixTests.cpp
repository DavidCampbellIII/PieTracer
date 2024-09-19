#include "catch_amalgamated.hpp"
#include "../src/Matrix.h"

using namespace Catch::Matchers;

TEST_CASE("Matrix Initialization", "[matrix]")
{
    SECTION("4x4")
    {
        const Matrix<4, 4> m = {
            {1, 2, 3, 4},
            {5.5, 6.5, 7.5, 8.5},
            {9, 10, 11, 12},
            {13.5, 14.5, 15.5, 16.5}
        };
        REQUIRE_THAT(m.Get(0, 0), WithinRel(1.f));
        REQUIRE_THAT(m.Get(0, 3), WithinRel(4.f));
        REQUIRE_THAT(m.Get(1, 0), WithinRel(5.5f));
        REQUIRE_THAT(m.Get(1, 2), WithinRel(7.5f));
        REQUIRE_THAT(m.Get(2, 2), WithinRel(11.f));
        REQUIRE_THAT(m.Get(3, 0), WithinRel(13.5f));
        REQUIRE_THAT(m.Get(3, 2), WithinRel(15.5f));
    }

    SECTION("3x3")
    {
        const Matrix<3, 3> m = {
            {-3, 5, 0},
            {1, -2, -7},
            {0, 1, 1}
        };
        REQUIRE_THAT(m.Get(0, 0), WithinRel(-3.f));
        REQUIRE_THAT(m.Get(1, 1), WithinRel(-2.f));
        REQUIRE_THAT(m.Get(2, 2), WithinRel(1.f));
    }

    SECTION("2x2")
    {
        const Matrix<2, 2> m = {
            {-3, 5},
            {1, -2}
        };
        REQUIRE_THAT(m.Get(0, 0), WithinRel(-3.f));
        REQUIRE_THAT(m.Get(0, 1), WithinRel(5.f));
        REQUIRE_THAT(m.Get(1, 0), WithinRel(1.f));
        REQUIRE_THAT(m.Get(1, 1), WithinRel(-2.f));
    }
    
}

TEST_CASE("Matrix Equality", "[matrix]")
{
    const Matrix<4, 4> a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    const Matrix<4, 4> b = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    const Matrix<4, 4> c = {
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };
    
    REQUIRE(a == b);
    REQUIRE(a != c);
}

TEST_CASE("Matrix Multiplication", "[matrix]")
{
    const Matrix<4, 4> a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    const Matrix<4, 4> b = {
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5}, 
        {1, 2, 7, 8}
    };
    const Matrix<4, 4> result = {
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    };
    REQUIRE(a * b == result);
}
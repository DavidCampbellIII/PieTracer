#include <catch2/catch_all.hpp>
#include "../src/Shared/Matrix.h"
#include "../src/Shared/Tuple.h"

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
    

    SECTION("Matrix * Matrix")
    {
        const Matrix<4, 4> result = {
            {20, 22, 50, 48},
            {44, 54, 114, 108},
            {40, 58, 110, 102},
            {16, 26, 46, 42}
        };
        REQUIRE(a * b == result);
    }

    SECTION("Matrix * Tuple")
    {
        const Matrix<4, 4> a = {
            {1, 2, 3, 4},
            {2, 4, 4, 2},
            {8, 6, 4, 1},
            {0, 0, 0, 1}
        };
        const Tuple t = Tuple(1, 2, 3, 1);
        const Tuple result = Tuple(18, 24, 33, 1);
        REQUIRE(a * t == result);
    }
}

TEST_CASE("Matrix Identity", "[matrix]")
{
    const Matrix<4, 4> a = {
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    };
    REQUIRE(a * Matrix<4, 4>::IDENTITY == a);

    const Matrix<4, 4> identity = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    REQUIRE(identity == Matrix<4, 4>::IDENTITY);
}

TEST_CASE("Matrix Transpose", "[matrix]")
{
	const Matrix<4, 4> a = {
		{0, 9, 3, 0},
		{9, 8, 0, 8},
		{1, 8, 5, 3},
		{0, 0, 5, 8}
	};
	const Matrix<4, 4> result = {
		{0, 9, 1, 0},
		{9, 8, 8, 0},
		{3, 0, 5, 5},
		{0, 8, 3, 8}
	};
	REQUIRE(a.Transpose() == result);
	REQUIRE(Matrix<4, 4>::IDENTITY.Transpose() == Matrix<4, 4>::IDENTITY);
}

TEST_CASE("Matrix Determinant", "[matrix]")
{
	SECTION("2x2")
	{
		const Matrix<2, 2> a = {
			{1, 5},
			{-3, 2}
		};
		REQUIRE_THAT(a.Determinant(), WithinRel(17.f));
	}
	
	SECTION("3x3")
	{
		const Matrix<3, 3> a = {
			{1, 2, 6},
			{-5, 8, -4},
			{2, 6, 4}
		};
		REQUIRE_THAT(a.Cofactor(0, 0), WithinRel(56.f));
		REQUIRE_THAT(a.Cofactor(0, 1), WithinRel(12.f));
		REQUIRE_THAT(a.Cofactor(0, 2), WithinRel(-46.f));
		REQUIRE_THAT(a.Determinant(), WithinRel(-196.f));
	}

	SECTION("4x4")
	{
		const Matrix<4, 4> a = {
			{-2, -8, 3, 5},
			{-3, 1, 7, 3},
			{1, 2, -9, 6},
			{-6, 7, 7, -9}
		};
		REQUIRE_THAT(a.Cofactor(0, 0), WithinRel(690.f));
		REQUIRE_THAT(a.Cofactor(0, 1), WithinRel(447.f));
		REQUIRE_THAT(a.Cofactor(0, 2), WithinRel(210.f));
		REQUIRE_THAT(a.Cofactor(0, 3), WithinRel(51.f));
		REQUIRE_THAT(a.Determinant(), WithinRel(-4071.f));
	}
}

TEST_CASE("Matrix Submatrix", "[matrix]")
{
	const Matrix<3, 3> a = {
		{1, 5, 0},
		{-3, 2, 7},
		{0, 6, -3}
	};
	const Matrix<2, 2> result = {
		{-3, 2},
		{0, 6}
	};
	REQUIRE(a.Submatrix(0, 2) == result);

	const Matrix<4, 4> b = {
		{-6, 1, 1, 6},
		{-8, 5, 8, 6},
		{-1, 0, 8, 2},
		{-7, 1, -1, 1}
	};
	const Matrix<3, 3> result2 = {
		{-6, 1, 6},
		{-8, 8, 6},
		{-7, -1, 1}
	};
	REQUIRE(b.Submatrix(2, 1) == result2);
}

TEST_CASE("Matrix Minor", "[matrix]")
{
	const Matrix<3, 3> a = {
		{3, 5, 0},
		{2, -1, -7},
		{6, -1, 5}
	};
	const Matrix<2, 2> b = a.Submatrix(1, 0);
	REQUIRE_THAT(b.Determinant(), WithinRel(25.f));
	REQUIRE_THAT(a.Minor(1, 0), WithinRel(25.f));
}

TEST_CASE("Matrix Cofactor", "[matrix]")
{
	const Matrix<3, 3> a = {
		{3, 5, 0},
		{2, -1, -7},
		{6, -1, 5}
	};
	REQUIRE_THAT(a.Minor(0, 0), WithinRel(-12.f));
	REQUIRE_THAT(a.Cofactor(0, 0), WithinRel(-12.f));
	REQUIRE_THAT(a.Minor(1, 0), WithinRel(25.f));
	REQUIRE_THAT(a.Cofactor(1, 0), WithinRel(-25.f));
}

TEST_CASE("Matrix Check Is Invertible", "[matrix]")
{
	const Matrix<4, 4> a = {
			{6, 4, 4, 4},
			{5, 5, 7, 6},
			{4, -9, 3, -7},
			{9, 1, 7, -6}
	};
	REQUIRE_THAT(a.Determinant(), WithinRel(-2120.f));
	REQUIRE(a.IsInvertible() == true);

	const Matrix<4, 4> b = {
			{-4, 2, -2, -3},
			{9, 6, 2, 6},
			{0, -5, 1, -5},
			{0, 0, 0, 0}
	};
	REQUIRE_THAT(b.Determinant(), WithinRel(0.f));
	REQUIRE(b.IsInvertible() == false);
}

TEST_CASE("Matrix Inverse", "[matrix]")
{
	SECTION("Inversion Test 1")
	{
        const Matrix<4, 4> a = {
			{-5, 2, 6, -8},
			{1, -5, 1, 8},
			{7, 7, -6, -7},
			{1, -3, 7, 4}
		};
		const Matrix<4, 4> b = a.Inverse();
		REQUIRE_THAT(a.Determinant(), WithinRel(532.f));
		REQUIRE_THAT(a.Cofactor(2, 3), WithinRel(-160.f));
		REQUIRE_THAT(b.Get(3, 2), WithinRel(-160.f / 532.f));
		REQUIRE_THAT(a.Cofactor(3, 2), WithinRel(105.f));
		REQUIRE_THAT(b.Get(2, 3), WithinRel(105.f / 532.f));

		const Matrix<4, 4> expected = {
			{0.21805f, 0.45113f, 0.24060f, -0.04511f},
			{-0.80827f, -1.45677f, -0.44361f, 0.52068f},
			{-0.07895f, -0.22368f, -0.05263f, 0.19737f},
			{-0.52256f, -0.81391f, -0.30075f, 0.30639f}
		};
		REQUIRE(b == expected);
	}

	SECTION("Inversion Test 2")
	{
		const Matrix<4, 4> a = {
			{8, -5, 9, 2},
			{7, 5, 6, 1},
			{-6, 0, 9, 6},
			{-3, 0, -9, -4}
		};
		const Matrix<4, 4> b = a.Inverse();

		const Matrix<4, 4> expected = {
			{-0.15385f, -0.15385f, -0.28205f, -0.53846f},
			{-0.07692f, 0.12308f, 0.02564f, 0.03077f},
			{0.35897f, 0.35897f, 0.43590f, 0.92308f},
			{-0.69231f, -0.69231f, -0.76923f, -1.92308f}
		};
		REQUIRE(b == expected);
	}

	SECTION("Inversion Test 3")
	{
		const Matrix<4, 4> a = {
			{9, 3, 0, 9},
			{-5, -2, -6, -3},
			{-4, 9, 6, 4},
			{-7, 6, 6, 2}
		};
		const Matrix<4, 4> b = a.Inverse();

		const Matrix<4, 4> expected = {
			{-0.04074f, -0.07778f, 0.14444f, -0.22222f},
			{-0.07778f, 0.03333f, 0.36667f, -0.33333f},
			{-0.02901f, -0.14630f, -0.10926f, 0.12963f},
			{0.17778f, 0.06667f, -0.26667f, 0.33333f}
		};
		REQUIRE(b == expected);
	}

	SECTION("Multiplying product by inverse to get original matrix")
	{
		const Matrix<4, 4> a = {
			{3, -9, 7, 3},
			{3, -8, 2, -9},
			{-4, 4, 4, 1},
			{-6, 5, -1, 1}
		};
		const Matrix<4, 4> b = {
			{8, 2, 2, 2},
			{3, -1, 7, 0},
			{7, 0, 5, 4},
			{6, -2, 0, 5}
		};
		const Matrix<4, 4> c = a * b;
		REQUIRE(c * b.Inverse() == a);
	}
	
}
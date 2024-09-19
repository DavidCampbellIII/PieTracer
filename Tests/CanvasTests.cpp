#include "catch_amalgamated.hpp"
#include "../src/Canvas.h"
#include "../src/Color.h"

TEST_CASE("Canvas initialization", "[canvas]")
{
    Canvas c = Canvas(10, 20);
    REQUIRE(c.Width() == 10);
    REQUIRE(c.Height() == 20);
    for(int y = 0; y < c.Height(); y++)
    {
        for(int x = 0; x < c.Width(); x++)
        {
            REQUIRE(c.PixelAt(x, y) == Color(0, 0, 0));
        }
    }
}

TEST_CASE("Write pixel to canvas", "[canvas]")
{
    Canvas c = Canvas(10, 20);
    const Color red = Color(1, 0, 0);
    c.WritePixel(2, 3, red);
    REQUIRE(c.PixelAt(2, 3) == red);
}

TEST_CASE("To PPM string", "[canvas]")
{
    Canvas c = Canvas(5, 3);
    const Color c1 = Color(1.5, 0, 0);
    const Color c2 = Color(0, 0.5, 0);
    const Color c3 = Color(-0.5, 0, 1);
    c.WritePixel(0, 0, c1);
    c.WritePixel(2, 1, c2);
    c.WritePixel(4, 2, c3);
    const std::string ppm = c.ToPPM();

    std::string expected = "P3\n5 3\n255\n";
    expected +=            "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
    expected +=            "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n";
    expected +=            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n\n";
    REQUIRE(ppm == expected);
}

TEST_CASE("Splitting long PPM lines", "[canvas]")
{
    Canvas c = Canvas(11, 1);
    const Color color = Color(1.f, 0.8f, 0.6f);
    c.Clear(color);

    const std::string ppm = c.ToPPM();
    std::string expected = "P3\n11 1\n255\n";
    expected +=            "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n";
    expected +=            "153 255 204 153 255 204 153 255 204 153 255 204 153\n\n";
    REQUIRE(ppm == expected);
}
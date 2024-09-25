#include <catch2/catch_all.hpp>

#include "Material.h"
#include "Point.h"
#include "Shapes/Sphere.h"
#include "Light.h"

using namespace Catch::Matchers;

TEST_CASE("Light initialization", "[lights]")
{
	const Light light(Point(0, 0, 0), Color(1, 1, 1));
	REQUIRE(light.position == Point(0, 0, 0));
	REQUIRE(light.color == Color(1, 1, 1));
}

TEST_CASE("Default material", "[materials]")
{
	const Material m;
	REQUIRE(m.color == Color(1, 1, 1));
	REQUIRE_THAT(m.ambient, WithinRel(0.1f));
	REQUIRE_THAT(m.diffuse, WithinRel(0.9f));
	REQUIRE_THAT(m.specular, WithinRel(0.9f));
	REQUIRE_THAT(m.shininess, WithinRel(200.f));
}

TEST_CASE("Sphere has default material", "[materials]")
{
	const Sphere s;
	const std::shared_ptr<Material> m = s.GetMaterial();
	REQUIRE(m == s.GetDefaultMaterial());
}
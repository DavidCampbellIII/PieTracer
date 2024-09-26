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

TEST_CASE("Sphere may be assigned a material", "[materials]")
{
	const Material m(Color(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.f);
	const std::shared_ptr<Material> mPtr = std::make_shared<Material>(m);
	Sphere s;
	s.SetMaterial(mPtr);
	REQUIRE(s.GetMaterial() == mPtr);
}

TEST_CASE("Lighting with eye and light and surface at various positions and angles", "[shading]")
{
	const Material material;
	const Point position(0, 0, 0);
	const Vector normal(0, 0, -1);

	SECTION("Lighting with the eye between the light and the surface")
	{
		const Vector eye(0, 0, -1);
		const Light light(Point(0, 0, -10), Color(1, 1, 1));
		const Color result = material.Lighting(light, position, eye, normal);
		REQUIRE(result == Color(1.9f, 1.9f, 1.9f));
	}

	SECTION("Lighting with the eye between the light and the surface, eye offset 45 degrees", "[shading]")
	{
		const Vector eye(0, sqrt(2) / 2, -sqrt(2) / 2);
		const Light light(Point(0, 0, -10), Color(1, 1, 1));
		const Color result = material.Lighting(light, position, eye, normal);
		REQUIRE(result == Color(1.0f, 1.0f, 1.0f));
	}

	SECTION("Lighting with eye opposite surface, light offset 45 degrees", "[shading]")
	{
		const Vector eye(0, 0, -1);
		const Light light(Point(0, 10, -10), Color(1, 1, 1));
		const Color result = material.Lighting(light, position, eye, normal);
		REQUIRE(result == Color(0.7364f, 0.7364f, 0.7364f));
	}

	SECTION("Lighting with eye in the path of the reflection vector", "[shading]")
	{
		const Vector eye(0, -sqrt(2) / 2, -sqrt(2) / 2);
		const Light light(Point(0, 10, -10), Color(1, 1, 1));
		const Color result = material.Lighting(light, position, eye, normal);
		REQUIRE(result == Color(1.6364f, 1.6364f, 1.6364f));
	}

	SECTION("Lighting with the light behind the surface", "[shading]")
	{
		const Vector eye(0, 0, -1);
		const Light light(Point(0, 0, 10), Color(1, 1, 1));
		const Color result = material.Lighting(light, position, eye, normal);
		REQUIRE(result == Color(0.1f, 0.1f, 0.1f));
	}
}

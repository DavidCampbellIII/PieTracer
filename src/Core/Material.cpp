#include "Material.h"

#include "Light.h"
#include "Vector.h"
#include "Point.h"

Color Material::Lighting(const Light& light, const Point& position, const Vector& eye, const Vector& normal) const
{
	const Color effectiveColor = color * light.color;
	const Color ambientColor = effectiveColor * ambient;

	const Vector lightVector = (light.position - position).Normalized();
	const float lightDotNormal = lightVector.Dot(normal);
	//if negative, light is behind the surface
	if (lightDotNormal < 0)
	{
		return ambientColor;
	}

	const Color diffuseColor = effectiveColor * diffuse * lightDotNormal;
	const Vector reflectVector = (-lightVector).Reflect(normal);
	const float reflectDotEye = reflectVector.Dot(eye);

	//if negative, light reflects away from the eye
	if (reflectDotEye <= 0)
	{
		return ambientColor + diffuseColor;
	}
	const float specFactor = std::pow(reflectDotEye, shininess);
	const Color specularColor = light.color * specular * specFactor;

	return ambientColor + diffuseColor + specularColor;
}
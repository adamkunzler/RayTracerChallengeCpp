#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Material::Material()
	{
		color = Color(1.0, 1.0, 1.0);
		pattern = NULL;
		ambient = 0.1;
		diffuse = 0.9;
		specular = 0.9;
		shininess = 200.0;
		reflective = 0.0;
		transparency = 0.0;
		refractiveIndex = 1.0;
	}

	// 
	// NON-MEMBER FUNCTIONS -----------------------------------------------------
	//

	Material& matte(Material& m, const Color& color)
	{
		m.color = color;
		m.ambient = 0.0;
		m.diffuse = 0.9;
		m.specular = 0.0;
		m.shininess = 0.0;
		m.reflective = 0.0;
		m.transparency = 0.0;

		return m;
	}

	Material& gloss(Material& m, const Color& color)
	{
		m.color = color;
		m.ambient = 0.1f;
		m.diffuse = 0.8f;
		m.specular = 0.7f;
		m.shininess = 100.0;
		m.reflective = 0.05f;
		m.transparency = 0.0;

		return m;
	}

	Material& glass(Material& m)
	{
		m.color = Color(0.0, 0.0, 0.0);
		m.ambient = 0.1f;
		m.diffuse = 0.1f;
		m.specular = 1.0;
		m.shininess = 300.0;
		m.reflective = 1.0;
		m.transparency = 1.0;
		m.refractiveIndex = 1.52f;

		return m;
	}

	Material& metal(Material& m)
	{
		m.color = Color(0.0, 0.0, 0.0);
		m.ambient = 0.1f;
		m.diffuse = 0.1f;
		m.specular = 0.9f;
		m.shininess = 300.0;
		m.reflective = 0.9f;
		m.transparency = 0.0;
		m.refractiveIndex = 0.0;

		return m;
	}

	Material& metallic(Material& m, const Color& color)
	{
		m.color = color;
		m.ambient = 0.3f;
		m.diffuse = 0.3f;
		m.specular = 0.65f;
		m.shininess = 5.0f;
		m.reflective = 0.05f;
		m.transparency = 0.0;
		m.refractiveIndex = 0.0;

		return m;
	}
}

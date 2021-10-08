#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Material::Material()
	{
		color = Color(1, 1, 1);
		pattern = NULL;
		ambient = 0.1f;
		diffuse = 0.9f;
		specular = 0.9f;
		shininess = 200.0f;
		reflective = 0.0f;
		transparency = 0.0f;
		refractiveIndex = 1.0f;
	}

	// 
	// NON-MEMBER FUNCTIONS -----------------------------------------------------
	//

	Material& matte(Material& m, const Color& color)
	{
		m.color = color;
		m.ambient = 0.0f;
		m.diffuse = 1.0f;
		m.specular = 0.0f;
		m.shininess = 0.0f;
		m.reflective = 0.0f;
		m.transparency = 0.0f;

		return m;
	}

	Material& gloss(Material& m, const Color& color)
	{
		m.color = color;
		m.ambient = 0.1f;
		m.diffuse = 0.8f;
		m.specular = 0.7f;
		m.shininess = 100.0f;
		m.reflective = 0.05f;
		m.transparency = 0.0f;

		return m;
	}

	Material& glass(Material& m)
	{
		m.color = Color(0.0f, 0.0f, 0.0f);
		m.ambient = 0.1f;
		m.diffuse = 0.1f;
		m.specular = 1.0f;
		m.shininess = 300.0f;
		m.reflective = 1.0f;
		m.transparency = 1.0f;
		m.refractiveIndex = 1.52f;

		return m;
	}

	Material& metal(Material& m)
	{
		m.color = Color(0.0f, 0.0f, 0.0f);
		m.ambient = 0.1f;
		m.diffuse = 0.1f;
		m.specular = 0.9f;
		m.shininess = 300.0f;
		m.reflective = 1.0f;
		m.transparency = 0.0f;
		m.refractiveIndex = 0.0f;

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
		m.transparency = 0.0f;
		m.refractiveIndex = 0.0f;

		return m;
	}
}

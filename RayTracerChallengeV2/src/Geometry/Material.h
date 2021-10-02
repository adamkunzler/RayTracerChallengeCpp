#pragma once

//#include "../DataStructs/Color.h"
//#include "../Patterns/IPattern.h"

namespace RayTracer
{		
	struct IPattern;

	struct Material
	{	
		Color color;
		IPattern* pattern;
		float ambient;		// 0-1 - light reflected from other objects in environment (phong treats as constant)
		float diffuse;		// 0-1 - light reflected from matte surface
		float specular;		// 0-1 - light source reflection
		float shininess;	// ~10-~200 - reflection of the light source itself (small # large highlight, large # small highlight)
		float reflective;	// 0 non reflective, 1 mirror
		float transparency; // 0-1 - 0=opaque, 1=transparent
		float refractiveIndex; // the degree that light will bend when entering or exiting a material

		// example refractiveIndex values
		// vacuum 1
		// air 1.00029
		// water 1.333
		// glass 1.52
		// diamond 2.417
	
		Material()
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
	};

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
		m.specular = 0.9f;
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

#pragma once

namespace RayTracer
{		
	struct Material
	{	
		Color color;
		IPattern* pattern;
		double ambient;		// 0-1 - light reflected from other objects in environment (phong treats as constant)
		double diffuse;		// 0-1 - light reflected from matte surface
		double specular;		// 0-1 - light source reflection
		double shininess;	// ~10-~200 - reflection of the light source itself (small # large highlight, large # small highlight)
		double reflective;	// 0 non reflective, 1 mirror
		double transparency; // 0-1 - 0=opaque, 1=transparent
		double refractiveIndex; // the degree that light will bend when entering or exiting a material

		// example refractiveIndex values
		// vacuum 1
		// air 1.00029
		// water 1.333
		// glass 1.52
		// diamond 2.417
	
		Material();
	};

	Material& matte(Material& m, const Color& color);

	Material& gloss(Material& m, const Color& color);

	Material& glass(Material& m);

	Material& metal(Material& m);

	Material& metallic(Material& m, const Color& color);
}


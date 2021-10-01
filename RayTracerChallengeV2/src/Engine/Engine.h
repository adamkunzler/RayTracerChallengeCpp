#pragma once

#include "../DataStructs/Color.h"
//#include "../DataStructs/Matrix4x4.h"
#include "../DataStructs/Vector4.h"

#include "Camera.h"
#include "Canvas.h"
#include "World.h"

//#include "../Geometry/Intersection.h"
#include "../Geometry/Material.h"
#include "../Geometry/PointLight.h"
#include "../Geometry/Ray.h"
//#include "../Geometry/Computation.h"

#include "../Shapes/IShape.h"
//#include "../Shapes/Sphere.h"
//#include "../Shapes/Plane.h"

#include "../Patterns/IPattern.h"

namespace RayTracer
{	
	Canvas render(const Camera& camera, const World& world)
	{
		auto start1 = std::chrono::high_resolution_clock::now();

		Canvas image((int)camera.hSize, (int)camera.vSize);

		int totalPixels = (int)(camera.vSize * camera.hSize);
		int processedPixels = 0;

		for (int y = 0; y < camera.vSize; y++)
		{
			for (int x = 0; x < camera.hSize; x++)
			{
				Ray r = camera.rayForPixel(x, y);
				Color c = world.colorAt(r, MAX_RECURSION);
				image.setPixel(x, y, c);

				processedPixels++;				
			}
			showProgressBar((float)processedPixels / (float)totalPixels);
		}
		showProgressBar(1);

		auto stop1 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
		std::cout << "\n\nrender() completed in " << duration1.count() << "ms.";

		return image;
	}

	Color phong(const PointLight& light, const Material& m, const IShape& shape, const Vector4& p, const Vector4& eye, const Vector4& normalV, bool inShadow)
	{
		Color ambient;
		Color diffuse;
		Color specular;

		Color baseColor = m.color;

		if (m.pattern)
		{
			baseColor = m.pattern->patternAt(shape, p);
		}

		// combine surface color with lights color/intensity
		Color effectiveColor = light.intensity * baseColor;

		// find the direction to the light source
		Vector4 lightV = normalize(light.position - p);

		// compute the ambient contriubtion
		ambient = effectiveColor * m.ambient;
		if (inShadow)
		{
			// skip diffuse and specular if in shadow
			return ambient;
		}

		// lightDotNormal represents the cosine of the angle betwen
		// the light vector and the normal vector. A negative number 
		// means the light is on the other side of the surface
		float lightDotNormal = dot(lightV, normalV);
		if (lightDotNormal < 0.0f)
		{
			diffuse = Color(0.0f, 0.0f, 0.0f);
			specular = Color(0.0f, 0.0f, 0.0f);
		}
		else
		{
			// compute the diffuse contribution
			diffuse = effectiveColor * m.diffuse * lightDotNormal;

			// reflectDotEye represents the cosine of the angle between the reflection
			// vector and the eye vector. A negative number means the light reflects 
			// away from the eye				
			Vector4 negLightV = -lightV;
			Vector4 reflectV = negLightV.reflect(normalV);
			float reflectDotEye = dot(reflectV, eye);
			if (reflectDotEye <= 0.0f)
			{
				specular = Color(0.0f);
			}
			else
			{
				// compute specular contribution
				float factor = std::pow(reflectDotEye, m.shininess);
				specular = light.intensity * (m.specular * factor);
			}
		}
		
		return ambient + diffuse + specular;;
	}
}
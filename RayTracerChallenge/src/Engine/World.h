#pragma once
#include <vector>
#include "..\DataStructs\Point.h"
#include "..\DataStructs\Color.h"
#include "..\DataStructs\Matrix.h"
#include "..\Geometry\IShape.h"
#include "..\Geometry\Sphere.h"
#include "..\Geometry\PointLight.h"

namespace RayTracer
{
	class IShape;
	class PointLight;

	class World
	{
	public:
		std::vector<IShape*> objects;
		std::vector<PointLight> lights;

		World()
		{			
		}

		static World defaultWorld()
		{
			World w;
			
			w.lights.push_back(PointLight(Point(-10, 10, -10), Color(1, 1, 1)));

			Sphere s1;			
			s1.material.color = Color(0.8f, 1.0f, 0.6f);
			s1.material.diffuse = 0.7f;
			s1.material.specular = 0.2f;

			Sphere s2;
			s2.transform = Matrix::get4x4ScalingMatrix(0.5f, 0.5f, 0.5f);

			w.objects.push_back(&s1);
			w.objects.push_back(&s2);

			return w;
		}
	};
}
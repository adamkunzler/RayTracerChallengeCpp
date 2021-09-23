#pragma once

#include <vector>

#include "Material.h"
#include "Intersection.h"
#include "..\DataStructs\Matrix.h"
#include "Ray.h"

namespace RayTracer
{
	class Intersection;

	class IShape
	{
	public:
		Matrix transform;
		Material material;

	public:
		IShape() 
		{
			transform = Matrix::get4x4IdentityMatrix();
		}

		virtual ~IShape() {}		

		virtual Vector normalAt(const Point& worldPoint) = 0;

		virtual std::vector<Intersection> intersectBy(const Ray& r) = 0;
	};
}
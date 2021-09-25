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
		
		//
		// INTERSECTIONS
		//

		virtual std::vector<Intersection> localIntersectBy(const Ray& localRay) const = 0;

		std::vector<Intersection> intersectBy(const Ray& r) const
		{
			// ray in world space to local space
			Matrix inverse = transform.inverse();
			Ray localRay(r);
			localRay = localRay.transform(inverse);

			// shape figures out intersections
			return localIntersectBy(localRay);
		}

		//
		// NORMALS
		//

		virtual Vector localNormalAt(const Point& localPoint) const = 0;

		Vector normalAt(const Point& worldPoint) const
		{
			// point in world space to local space
			Point localPoint = (transform.inverse() * worldPoint).toPoint();

			// shape figures out it's normal
			Vector localNormal = localNormalAt(localPoint);

			// normal from local space to world space
			Vector worldNormal = (transform.inverse().transpose() * localNormal).toVector();
			worldNormal.w = 0;
			return worldNormal.normalize();
		}
	};
}
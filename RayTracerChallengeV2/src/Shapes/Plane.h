#pragma once

//#include <vector>
//#include "Material.h"
//#include "IShape.h"
//#include "Intersection.h"

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Plane : public IShape
	{		
		Plane() { }
				
		Vector4 localNormalAt(const Vector4& localPoint) const
		{			
			return Vector4(0.0f, 1.0f, 0.0f);
		}

		std::vector<Intersection> localIntersectBy(const Ray& localRay) const
		{
			std::vector<Intersection> intersections;

			if (std::fabs(localRay.direction.y) < 0.0f) // maybe use EPSILON
			{
				// empty
				return intersections;
			}

			float t = -localRay.origin.y / localRay.direction.y;			
			intersections.push_back(Intersection(t, (IShape*)this));

			return intersections;
		}
	};
}
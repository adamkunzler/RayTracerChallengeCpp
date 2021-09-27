#pragma once

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Plane : public IShape
	{		
		Plane()
		{
			material = Material();
		}
		
		~Plane()
		{
			//std::cout << "\nplane destructor";
		}

		Vector localNormalAt(const Point& localPoint) const
		{
			Vector localNormal(0,1,0);
			return localNormal;
		}

		std::vector<Intersection> localIntersectBy(const Ray& localRay) const
		{
			std::vector<Intersection> intersections;

			if (std::fabs(localRay.direction.y) < EPSILON)
			{
				// empty
				return intersections;
			}

			float t = -localRay.origin.y / localRay.direction.y;
			
			Intersection i(t, (IShape*)this);
			intersections.push_back(i);

			return intersections;
		}
	};
}
#pragma once

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Plane : public IShape
	{		
		Plane() { }
				
		Vector4 localNormalAt(const Point4& localPoint) const
		{			
			return Vector4(0.0f, 1.0f, 0.0f);
		}

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
		{			
			if (std::fabs(localRay.direction.y) < 0.0f) // maybe use EPSILON
			{
				// empty
				return;
			}

			float t = -localRay.origin.y / localRay.direction.y;			
			intersections.push_back(Intersection(t, (IShape*)this));			
		}
	};
}
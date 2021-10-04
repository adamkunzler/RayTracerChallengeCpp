#ifndef PLANE_H
#define PLANE_H

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Plane : public IShape
	{		
		Plane() { }
				
		Vector4 localNormalAt(const Point4& localPoint) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const;
	};
}

#endif
#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{

	Vector4 Plane::localNormalAt(const Point4& localPoint) const
	{
		return Vector4(0.0, 1.0, 0.0);
	}

	void Plane::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		if (std::abs(localRay.direction.y) < 0.0) // maybe use EPSILON
		{
			// empty
			return;
		}

		double t = -localRay.origin.y / localRay.direction.y;
		intersections.push_back(Intersection(t, (IShape*)this));
	}
}
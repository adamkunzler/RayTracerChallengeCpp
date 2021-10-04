#include "../Headers.h"

namespace RayTracer
{

	Vector4 Plane::localNormalAt(const Point4& localPoint) const
	{
		return Vector4(0.0f, 1.0f, 0.0f);
	}

	void Plane::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		if (std::fabs(localRay.direction.y) < 0.0f) // maybe use EPSILON
		{
			// empty
			return;
		}

		float t = -localRay.origin.y / localRay.direction.y;
		intersections.push_back(Intersection(t, (IShape*)this));
	}
}
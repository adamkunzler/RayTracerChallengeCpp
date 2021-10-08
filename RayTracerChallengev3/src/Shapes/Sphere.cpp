#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{

	Vector4 Sphere::localNormalAt(const Point4& localPoint) const
	{
		return localPoint - origin;
	}

	void Sphere::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		Vector4 sphereToRay = localRay.origin - origin;

		float a = dot(localRay.direction, localRay.direction);
		float b = 2 * dot(localRay.direction, sphereToRay);
		float c = dot(sphereToRay, sphereToRay) - 1;

		float discriminant = (b * b) - (4 * a) * c;
		if (discriminant < 0) // MISS
			return;

		float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
		float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

		intersections.push_back(Intersection(t1, (IShape*)this));
		intersections.push_back(Intersection(t2, (IShape*)this));
	}

	//
	// NON-MEMBER FUNCTIONS --------------------------------------------------------
	//

	Sphere GlassSphere()
	{
		Sphere s;
		s.setTransform(identity4x4());
		s.material.transparency = 1.0f;
		s.material.refractiveIndex = 1.5f;
		return s;
	}
}
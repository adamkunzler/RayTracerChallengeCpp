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

		double a = dot(localRay.direction, localRay.direction);
		double b = 2 * dot(localRay.direction, sphereToRay);
		double c = dot(sphereToRay, sphereToRay) - 1;

		double discriminant = (b * b) - (4 * a) * c;
		if (discriminant < 0.0) // MISS
			return;

		double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
		double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

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
		s.material.transparency = 1.0;
		s.material.refractiveIndex = 1.5;
		return s;
	}
}
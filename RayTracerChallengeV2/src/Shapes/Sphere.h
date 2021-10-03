#pragma once

//#include "Intersection.h"

namespace RayTracer
{
	struct Sphere : public IShape
	{
		Point4 origin;
		float radius;

		Sphere() : origin(Vector4(0.0f, 0.0f, 0.0f, 1.0f)), radius(1.0f) { }
		Sphere(const Point4& lOrigin, const float lRadius) : origin(lOrigin), radius(lRadius) { }
		
		Vector4 localNormalAt(const Point4& localPoint) const
		{						
			return localPoint - origin;
		}

		std::vector<Intersection> localIntersectBy(const Ray& localRay) const
		{
			std::vector<Intersection> intersections;

			Vector4 sphereToRay = localRay.origin - origin;

			float a = dot(localRay.direction, localRay.direction);
			float b = 2 * dot(localRay.direction, sphereToRay);
			float c = dot(sphereToRay, sphereToRay) - 1;

			float discriminant = (b * b) - (4 * a) * c;
			if (discriminant < 0) // MISS
				return intersections;

			float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
			float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

			intersections.push_back(Intersection(t1, (IShape*)this));
			intersections.push_back(Intersection(t2, (IShape*)this));

			return intersections;
		}		
	};

	Sphere GlassSphere()
	{
		Sphere s;
		s.setTransform(identity4x4());
		s.material.transparency = 1.0f;
		s.material.refractiveIndex = 1.5f;
		return s;
	}
}
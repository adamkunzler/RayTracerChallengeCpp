#pragma once

#include "Point.h"
#include "Vector.h"
#include "Sphere.h"

namespace RayTracer
{
	struct Ray
	{
		Point origin;
		Vector direction;

		Ray(const Point& lOrigin, const Vector& lDirection) : origin(lOrigin), direction(lDirection)
		{
		}

		Point position(const float t) const
		{
			Point p = origin + (direction * t);
			return p;
		}

		float* intersects(const Sphere& s)
		{
			Vector sphereToRay = origin - s.origin;

			float a = direction.dot(direction);
			float b = 2 * direction.dot(sphereToRay);
			float c = sphereToRay.dot(sphereToRay) - 1;

			float discriminant = (b * b) - (4 * a) * c;
			if (discriminant < 0) // MISS
				return NULL;

			float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
			float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

			float* ts = new float[2]{ t1, t2 };
			return ts;
		}
	};
}
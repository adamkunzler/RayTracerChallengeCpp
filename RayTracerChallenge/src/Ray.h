#pragma once

#include <vector>
#include "Tuple.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Sphere.h"
#include "IShape.h"
#include "Intersection.h"

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

		std::vector<Intersection> intersects(const Sphere& s)
		{
			Matrix st = s.transform;
			Matrix inverse = st.inverse();
			Ray newRay = transform(inverse);

			std::vector<Intersection> intersections;

			Vector sphereToRay = newRay.origin - s.origin;

			float a = newRay.direction.dot(newRay.direction);
			float b = 2 * newRay.direction.dot(sphereToRay);
			float c = sphereToRay.dot(sphereToRay) - 1;

			float discriminant = (b * b) - (4 * a) * c;
			if (discriminant < 0) // MISS
				return intersections;

			float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
			float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

			intersections.push_back(Intersection(t1, (IShape *)&s));
			intersections.push_back(Intersection(t2, (IShape *)&s));
			
			return intersections;
		}

		Ray transform(Matrix& matrix)
		{
			Point newOrigin = (matrix * origin).toPoint();
			Vector newDirection = (matrix * direction).toVector();

			Ray r(newOrigin, newDirection);
			return r;
		}
	};
}
#pragma once

namespace RayTracer
{
	struct Sphere : public IShape
	{
		Point origin;
		float radius;

		Sphere() : origin(Point(0,0,0)), radius(1)
		{
			material = Material();
		}

		Sphere(const Point& lOrigin, const float lRadius) : origin(lOrigin), radius(lRadius)
		{}

		Vector normalAt(const Point& worldPoint)
		{
			Point objectPoint = (transform.inverse() * worldPoint).toPoint();
			Vector objectNormal = objectPoint - origin;
			Vector worldNormal = (transform.inverse().transpose() * objectNormal).toVector();
			worldNormal.w = 0;
			return worldNormal.normalize();
		}

		std::vector<Intersection> intersectBy(const Ray& r)
		{			
			Matrix inverse = transform.inverse();
			Ray newRay(r);
			newRay = newRay.transform(inverse);

			std::vector<Intersection> intersections;

			Vector sphereToRay = newRay.origin - origin;

			float a = newRay.direction.dot(newRay.direction);
			float b = 2 * newRay.direction.dot(sphereToRay);
			float c = sphereToRay.dot(sphereToRay) - 1;

			float discriminant = (b * b) - (4 * a) * c;
			if (discriminant < 0) // MISS
				return intersections;

			float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
			float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

			intersections.push_back(Intersection(t1, this));
			intersections.push_back(Intersection(t2, this));

			return intersections;
		};
	};
}
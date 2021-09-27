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

		~Sphere()
		{
			//std::cout << "\nsphere destructor";
		}

		Vector localNormalAt(const Point& localPoint) const
		{			
			Vector localNormal = localPoint - origin;
			return localNormal;
		}

		std::vector<Intersection> localIntersectBy(const Ray& localRay) const
		{
			std::vector<Intersection> intersections;

			Vector sphereToRay = localRay.origin - origin;

			float a = localRay.direction.dot(localRay.direction);
			float b = 2 * localRay.direction.dot(sphereToRay);
			float c = sphereToRay.dot(sphereToRay) - 1;

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
}
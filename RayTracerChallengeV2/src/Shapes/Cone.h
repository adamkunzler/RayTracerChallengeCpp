#pragma once

namespace RayTracer
{	
	struct Cone : public IShape
	{
		Cone() { }

		Vector4 localNormalAt(const Point4& localPoint) const
		{
			return Vector4(0.0f, 1.0f, 0.0f);
		}

		std::vector<Intersection> localIntersectBy(const Ray& localRay) const
		{
			std::vector<Intersection> intersections;

			if (std::fabs(localRay.direction.y) < 0.0f) // maybe use EPSILON
			{
				// empty
				return intersections;
			}

			float t = -localRay.origin.y / localRay.direction.y;
			intersections.push_back(Intersection(t, (IShape*)this));

			return intersections;
		}
	};
}
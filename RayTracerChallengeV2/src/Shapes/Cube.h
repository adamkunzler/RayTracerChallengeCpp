#pragma once

namespace RayTracer
{
	struct Cube : public IShape
	{
		Point4 origin;

		Cube() : origin(Point4(0.0f, 0.0f, 0.0f)) { }
		Cube(const Point4& lOrigin) : origin(lOrigin) { }

		Vector4 localNormalAt(const Point4& localPoint) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const;

		void checkAxis(const float& axisOrigin, const float& rayDirection, float& tmin, float& tmax) const;
	};
}
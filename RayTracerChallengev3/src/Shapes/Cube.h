#pragma once

namespace RayTracer
{
	struct Cube : public IShape
	{
		Point4 origin;

		Cube() : origin(Point4(0.0, 0.0, 0.0)) { }
		Cube(const Point4& lOrigin) : origin(lOrigin) { }

		Vector4 localNormalAt(const Point4& localPoint, const Intersection& i) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection*>& intersections) const;

		void checkAxis(const double& axisOrigin, const double& rayDirection, double& tmin, double& tmax) const;

		BoundingBox localBounds() const;
	};
}

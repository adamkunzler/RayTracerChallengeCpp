#pragma once

namespace RayTracer
{
	struct Sphere : public IShape
	{
		Point4 origin;
		float radius;

		Sphere() : origin(Vector4(0.0f, 0.0f, 0.0f, 1.0f)), radius(1.0f) { }
		Sphere(const Point4& lOrigin, const float lRadius) : origin(lOrigin), radius(lRadius) { }
		
		Vector4 localNormalAt(const Point4& localPoint) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const;
	};

	Sphere GlassSphere();
}
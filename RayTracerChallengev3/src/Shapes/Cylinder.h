#pragma once

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Cylinder : public IShape
	{
		double minimum;
		double maximum;
		bool isClosed;

		Cylinder() : minimum(-INFINITY), maximum(INFINITY), isClosed(false) { }
		Cylinder(const double& min, const double& max, const bool& lIsClosed = false) : minimum(min), maximum(max), isClosed(lIsClosed) { }

		Vector4 localNormalAt(const Point4& localPoint) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const;

		bool checkCap(const Ray& localRay, const double& t) const;

		void intersectCaps(std::vector<Intersection>& xs, const Ray& localRay) const;

		BoundingBox localBounds() const;
	};
}

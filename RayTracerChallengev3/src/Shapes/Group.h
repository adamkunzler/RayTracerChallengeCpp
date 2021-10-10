#pragma once

namespace RayTracer
{
	struct Group : public IShape
	{
		BoundingBox bounds;
		std::vector<IShape*> children;

		Group() {}

		Vector4 localNormalAt(const Point4& localPoint) const;

		void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const;

		void addChild(IShape* shape);

		BoundingBox localBounds() const;
	};
}

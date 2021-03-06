#pragma once

namespace RayTracer
{
	struct Group : public IShape
	{
		BoundingBox bounds;
		std::vector<IShape*> children{};

		Group() {}

		Vector4 localNormalAt(const Point4& localPoint, const Intersection& i) const;

		void localIntersectBy(const Ray& localRay, std::vector<std::shared_ptr<Intersection>>& intersections) const;

		void addChild(IShape* shape);

		BoundingBox localBounds() const;

		void partitionChildren(std::vector<IShape*>& left, std::vector<IShape*>& right);

		void makeSubGroup(std::vector<IShape*> shapes);

		void divide(const int& threshold);

		void setMaterial(const Material& material);
	};
}

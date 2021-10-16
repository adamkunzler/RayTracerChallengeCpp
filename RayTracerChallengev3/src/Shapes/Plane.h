#pragma once

namespace RayTracer
{
	/// <summary>
	/// Represents an XZ plane
	/// </summary>
	struct Plane : public IShape
	{		
		Plane() { }
				
		Vector4 localNormalAt(const Point4& localPoint, const Intersection& i) const;

		void localIntersectBy(const Ray& localRay, std::vector<std::shared_ptr<Intersection>>& intersections) const;

		BoundingBox localBounds() const;
	};
}

#pragma once

namespace RayTracer
{
	struct IShape;
	struct Ray;

	struct BoundingBox
	{
		Point4 min;
		Point4 max;

		BoundingBox() : min(Point4(INFINITY, INFINITY, INFINITY)), max(Point4(-INFINITY, -INFINITY, -INFINITY)) { }

		BoundingBox(Point4 lMin, Point4 lMax) : min(lMin), max(lMax) { }

		void addPoint(const Point4& point);

		void addBoundingBox(const BoundingBox& rhs);

		bool containsPoint(const Point4& point) const;

		bool containsBoundingBox(const BoundingBox& box) const;

		BoundingBox transform(const Matrix4x4& matrix) const;
		
		BoundingBox parentSpaceBoundsOf(const IShape& shape) const;

		bool intersectBy(const Ray& localRay) const;
		
		void checkAxis(const double& axisOrigin, const double& rayDirection, const double& min, const double& max, double& tmin, double& tmax) const;
	};
}
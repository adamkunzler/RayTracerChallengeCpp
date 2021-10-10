#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	void BoundingBox::addPoint(const Point4& point)
	{
		min.x = std::min(min.x, point.x);
		min.y = std::min(min.y, point.y);
		min.z = std::min(min.z, point.z);

		max.x = std::max(max.x, point.x);
		max.y = std::max(max.y, point.y);
		max.z = std::max(max.z, point.z);
	}

	void BoundingBox::addBoundingBox(const BoundingBox& rhs)
	{
		addPoint(rhs.min);
		addPoint(rhs.max);
	}

	bool BoundingBox::containsPoint(const Point4& point) const
	{
		return point.x >= min.x && point.x <= max.x
			&& point.y >= min.y && point.y <= max.y
			&& point.z >= min.z && point.z <= max.z;
	}
	
	bool BoundingBox::containsBoundingBox(const BoundingBox& box) const
	{
		return containsPoint(box.min) && containsPoint(box.max);
	}

	BoundingBox BoundingBox::transform(const Matrix4x4& matrix) const
	{
		Point4 p1(min);
		Point4 p2(min.x, min.y, max.z);
		Point4 p3(min.x, max.y, min.z);
		Point4 p4(min.x, max.y, max.z);
		Point4 p5(max.x, min.y, min.z);
		Point4 p6(max.x, min.y, max.z);
		Point4 p7(max.x, max.y, min.z);
		Point4 p8(max);

		BoundingBox bb;
		bb.addPoint(matrix * p1); bb.addPoint(matrix * p2); bb.addPoint(matrix * p3); bb.addPoint(matrix * p4);
		bb.addPoint(matrix * p5); bb.addPoint(matrix * p6); bb.addPoint(matrix * p7); bb.addPoint(matrix * p8);

		return BoundingBox(bb.min, bb.max);
	}
	
	bool BoundingBox::intersectBy(const Ray& localRay) const
	{
		double xtmin, xtmax;
		checkAxis(localRay.origin.x, localRay.direction.x, min.x, max.x, xtmin, xtmax);

		double ytmin, ytmax;
		checkAxis(localRay.origin.y, localRay.direction.y, min.y, max.y, ytmin, ytmax);

		double ztmin, ztmax;
		checkAxis(localRay.origin.z, localRay.direction.z, min.z, max.z, ztmin, ztmax);

		double tmin = std::max({ xtmin, ytmin, ztmin });
		double tmax = std::min({ xtmax, ytmax, ztmax });

		if (tmin > tmax) return false;

		return true;
	}

	void BoundingBox::checkAxis(const double& axisOrigin, const double& rayDirection, const double& min, const double& max, double& tmin, double& tmax) const
	{
		double tminNumerator = (min - axisOrigin);
		double tmaxNumerator = (max - axisOrigin);

		if (std::abs(rayDirection) >= DBL_EPSILON)
		{
			tmin = tminNumerator / rayDirection;
			tmax = tmaxNumerator / rayDirection;
		}
		else
		{
			tmin = tminNumerator * INFINITY;
			tmax = tmaxNumerator * INFINITY;
		}

		if (tmin > tmax) {
			std::swap(tmin, tmax);
		}
	}

	void BoundingBox::splitBounds(BoundingBox& left, BoundingBox& right) const
	{
		// figure out largest dimension
		double dx = max.x - min.x;
		double dy = max.y - min.y;
		double dz = max.z - min.z;

		double greatest = std::max(std::max(dx, dy), dz);

		double x0 = min.x;
		double y0 = min.y;
		double z0 = min.z;
		double x1 = max.x;
		double y1 = max.y;
		double z1 = max.z;

		// adjust points so they lie on the dividing plane
		if (greatest == dx)
		{
			x0 = x1 = x0 + dx / 2.0;
		}
		else if (greatest == dy)
		{
			y0 = y1 = y0 + dy / 2.0;
		}
		else
		{
			z0 = z1 = z0 + dz / 2.0;
		}

		Point4 midMin(x0, y0, z0);
		Point4 midMax(x1, y1, z1);

		// construct two halves of bounding box
		left.min = min;
		left.max = midMax;
		right.min = midMin;
		right.max = max;
	}
}
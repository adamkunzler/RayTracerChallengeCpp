#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Vector4 Cylinder::localNormalAt(const Point4& localPoint) const
	{
		// compute the square of the distance from the y axis
		double dist = localPoint.x * localPoint.x + localPoint.z * localPoint.z;

		if ((dist < 1.0) && (localPoint.y >= (maximum - DBL_EPSILON)))
		{
			return Vector4(0.0, 1.0, 0.0);
		}
		else if ((dist < 1.0) && (localPoint.y <= (minimum + DBL_EPSILON)))
		{
			return Vector4(0.0, -1.0, 0.0);
		}

		return Vector4(localPoint.x, 0.0, localPoint.z);
	}

	void Cylinder::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		double a = localRay.direction.x * localRay.direction.x
			+ localRay.direction.z * localRay.direction.z;
		if (a < DBL_EPSILON) return;

		double b = 2.0 * localRay.origin.x * localRay.direction.x
			+ 2.0 * localRay.origin.z * localRay.direction.z;

		double c = localRay.origin.x * localRay.origin.x
			+ localRay.origin.z * localRay.origin.z - 1.0;

		double discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0.0) return;

		double sqrtDisc = sqrt(discriminant);
		double t0 = (-b - sqrtDisc) / (2.0 * a);
		double t1 = (-b + sqrtDisc) / (2.0 * a);
		if (t0 > t1) std::swap(t0, t1);

		double y0 = localRay.origin.y + t0 * localRay.direction.y;
		if (minimum < y0 && y0 < maximum)
		{
			intersections.push_back(Intersection(t0, (IShape*)this));
		}

		double y1 = localRay.origin.y + t1 * localRay.direction.y;
		if (minimum < y1 && y1 < maximum)
		{
			intersections.push_back(Intersection(t1, (IShape*)this));
		}

		intersectCaps(intersections, localRay);
	}

	bool Cylinder::checkCap(const Ray& localRay, const double& t) const
	{
		double x = localRay.origin.x + (t * localRay.direction.x);
		double z = localRay.origin.z + (t * localRay.direction.z);
		return (x * x + z * z) <= 1.0;
	}

	void Cylinder::intersectCaps(std::vector<Intersection>& xs, const Ray& localRay) const
	{
		// caps only matter if the cylinder is closed and might possibly be intersected by the ray
		if (!isClosed || (localRay.direction.y < DBL_EPSILON && localRay.direction.y > -DBL_EPSILON)) return;

		// check for an intersection with the lower end cap by intersecting
		// the ray with the plane at y = cylinder.minimum
		double t0 = (minimum - localRay.origin.y) / localRay.direction.y;
		if (checkCap(localRay, t0))
		{
			xs.push_back(Intersection(t0, (IShape*)this));
		}

		// check for an intersection with the upper end cap by intersecting
		// the ray with the plane at y = cylinder.maximum
		double t1 = (maximum - localRay.origin.y) / localRay.direction.y;
		if (checkCap(localRay, t1))
		{
			xs.push_back(Intersection(t1, (IShape*)this));
		}
	}

	BoundingBox Cylinder::localBounds() const
	{
		Point4 min(-1, minimum, -1);
		Point4 max(1, maximum, 1);

		return BoundingBox(min, max);
	}
}
#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	Vector4 Cube::localNormalAt(const Point4& localPoint, const Intersection& i) const
	{
		double maxc = std::max({ abs(localPoint.x), abs(localPoint.y) , abs(localPoint.z) });

		if (maxc == abs(localPoint.x))
		{
			return Vector4(localPoint.x, 0.0, 0.0);
		}
		else if (maxc == abs(localPoint.y))
		{
			return Vector4(0.0, localPoint.y, 0.0);
		}

		return Vector4(0.0, 0.0, localPoint.z);
	}

	void Cube::localIntersectBy(const Ray& localRay, std::vector<std::shared_ptr<Intersection>>& intersections) const
	{
		double xtmin, xtmax;
		checkAxis(localRay.origin.x, localRay.direction.x, xtmin, xtmax);

		double ytmin, ytmax;
		checkAxis(localRay.origin.y, localRay.direction.y, ytmin, ytmax);

		double ztmin, ztmax;
		checkAxis(localRay.origin.z, localRay.direction.z, ztmin, ztmax);

		double tmin = std::max({ xtmin, ytmin, ztmin });
		double tmax = std::min({ xtmax, ytmax, ztmax });

		if (tmin > tmax) return;

		intersections.push_back(std::shared_ptr<Intersection>(new Intersection(tmin, (IShape*)this)));
		intersections.push_back(std::shared_ptr<Intersection>(new Intersection(tmax, (IShape*)this)));
	}

	void Cube::checkAxis(const double& axisOrigin, const double& rayDirection, double& tmin, double& tmax) const
	{
		double tminNumerator = (-1.0 - axisOrigin);
		double tmaxNumerator = (1.0 - axisOrigin);

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

	BoundingBox Cube::localBounds() const
	{
		Point4 min(-1.0, -1.0, -1.0);
		Point4 max(1.0, 1.0, 1.0);

		return BoundingBox(min, max);
	}
}
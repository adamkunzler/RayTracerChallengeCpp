#include <cmath>
#include <vector>

#include "../Utils.h"
#include "Cube.h"

#include "IShape.h"
#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"
#include "../Geometry/Intersection.h"
#include "../Geometry/Ray.h"

namespace RayTracer
{
	Vector4 Cube::localNormalAt(const Point4& localPoint) const
	{
		float maxc = std::max({ fabsf(localPoint.x), fabsf(localPoint.y) , fabsf(localPoint.z) });

		if (maxc == fabsf(localPoint.x))
		{
			return Vector4(localPoint.x, 0.0f, 0.0f);
		}
		else if (maxc == fabsf(localPoint.y))
		{
			return Vector4(0.0f, localPoint.y, 0.0f);
		}

		return Vector4(0.0f, 0.0f, localPoint.z);
	}

	void Cube::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		float xtmin, xtmax;
		checkAxis(localRay.origin.x, localRay.direction.x, xtmin, xtmax);

		float ytmin, ytmax;
		checkAxis(localRay.origin.y, localRay.direction.y, ytmin, ytmax);

		float ztmin, ztmax;
		checkAxis(localRay.origin.z, localRay.direction.z, ztmin, ztmax);

		float tmin = std::max({ xtmin, ytmin, ztmin });
		float tmax = std::min({ xtmax, ytmax, ztmax });

		if (tmin > tmax) return;

		intersections.push_back(Intersection(tmin, (IShape*)this));
		intersections.push_back(Intersection(tmax, (IShape*)this));
	}

	void Cube::checkAxis(const float& axisOrigin, const float& rayDirection, float& tmin, float& tmax) const
	{
		float tminNumerator = (-1.0f - axisOrigin);
		float tmaxNumerator = (1.0f - axisOrigin);

		if (std::fabsf(rayDirection) >= EPSILON)
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
}
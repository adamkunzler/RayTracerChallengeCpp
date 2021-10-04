#include <cmath>
#include <vector>

#include "../Utils.h"
#include "Plane.h"

#include "IShape.h"
#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"
#include "../DataStructs/Matrix4x4.h"
#include "../Geometry/Intersection.h"
#include "../Geometry/Ray.h"
#include "../Geometry/Material.h"

namespace RayTracer
{

	Vector4 Plane::localNormalAt(const Point4& localPoint) const
	{
		return Vector4(0.0f, 1.0f, 0.0f);
	}

	void Plane::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		if (std::fabs(localRay.direction.y) < 0.0f) // maybe use EPSILON
		{
			// empty
			return;
		}

		float t = -localRay.origin.y / localRay.direction.y;
		intersections.push_back(Intersection(t, (IShape*)this));
	}
}
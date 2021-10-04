#include <cmath>
#include <vector>

#include "../Utils.h"
#include "Sphere.h"

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

	Vector4 Sphere::localNormalAt(const Point4& localPoint) const
	{
		return localPoint - origin;
	}

	void Sphere::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		Vector4 sphereToRay = localRay.origin - origin;

		float a = dot(localRay.direction, localRay.direction);
		float b = 2 * dot(localRay.direction, sphereToRay);
		float c = dot(sphereToRay, sphereToRay) - 1;

		float discriminant = (b * b) - (4 * a) * c;
		if (discriminant < 0) // MISS
			return;

		float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
		float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);

		intersections.push_back(Intersection(t1, (IShape*)this));
		intersections.push_back(Intersection(t2, (IShape*)this));
	}

	//
	// NON-MEMBER FUNCTIONS --------------------------------------------------------
	//

	Sphere GlassSphere()
	{
		Sphere s;
		s.setTransform(identity4x4());
		s.material.transparency = 1.0f;
		s.material.refractiveIndex = 1.5f;
		return s;
	}
}
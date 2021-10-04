#include <cmath>
#include <vector>

#include "../Utils.h"
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

	IShape::IShape()
	{
		setTransform(identity4x4());
		hasShadow = true;
		parent = NULL;
	}
		
	void IShape::setTransform(const Matrix4x4& lTransform)
	{
		transform = lTransform;
		inverseTransform = inverse(transform);
	}
	
	const Matrix4x4 IShape::getTransform() const
	{
		return transform;
	}

	const Matrix4x4& IShape::getInverseTransform() const
	{
		return inverseTransform;
	}

	void IShape::intersectBy(const Ray& r, std::vector<Intersection>& intersections) const
	{
		// ray in world space to local space			
		Ray localRay(r);
		localRay = localRay.transform(inverseTransform);

		// shape figures out intersections
		this->localIntersectBy(localRay, intersections);
	}
	
	Point4 IShape::worldToObject(const Point4& worldPoint) const
	{
		Point4 p(worldPoint);

		if (parent != NULL)
		{
			p = parent->worldToObject(worldPoint);
		}

		return inverseTransform * p;
	}

	Vector4 IShape::normalToWorld(const Vector4& localNormal) const
	{
		Vector4 normal = transpose4x4(inverseTransform) * localNormal;
		normal.w = 0.0f; // just to be safe
		normal = normalize(normal);

		if (parent != NULL)
		{
			normal = parent->normalToWorld(normal);
		}

		return normal;
	}

	Vector4 IShape::normalAt(const Point4& worldPoint) const
	{
		// point in world space to local space
		Point4 localPoint = worldToObject(worldPoint);

		// shape figures out it's normal
		Vector4 localNormal = localNormalAt(localPoint); // TODO update to return reference

		// normal from local space to world space
		return normalToWorld(localNormal);
	}
}
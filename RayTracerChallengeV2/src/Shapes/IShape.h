#pragma once

#include <vector>

#include "../Geometry/Material.h"
#include "../Geometry/Ray.h"

namespace RayTracer
{		
	struct Intersection;
	struct Ray;
	struct Material;
	struct Vector4;
	struct IPattern;

	struct IShape
	{	
		Matrix4x4 transform;
		Material material;
		bool hasShadow;
	
		IShape() : transform(identity4x4()), hasShadow(true) { }
		virtual ~IShape() {}
		
		//
		// INTERSECTIONS
		//

		virtual std::vector<Intersection> localIntersectBy(const Ray& localRay) const = 0;

		std::vector<Intersection> intersectBy(const Ray& r) const
		{
			// ray in world space to local space
			Matrix4x4 inverseTransform = inverse(transform);
			Ray localRay(r); // TODO - aybe can pass r.transform(inverseTransform) to localRay?
			localRay = localRay.transform(inverseTransform);

			// shape figures out intersections
			return localIntersectBy(localRay);
		}

		//
		// NORMALS
		//

		virtual Vector4 localNormalAt(const Point4& localPoint) const = 0;

		Vector4 normalAt(const Point4& worldPoint) const
		{
			// point in world space to local space
			Point4 localPoint = worldPoint * inverse(transform);

			// shape figures out it's normal
			Vector4 localNormal = localNormalAt(localPoint); // TODO update to return reference

			// normal from local space to world space
			Vector4 worldNormal = localNormal * transpose4x4(inverse(transform));
			worldNormal.w = 0.0f;

			return normalize(worldNormal);
		}
	};
}
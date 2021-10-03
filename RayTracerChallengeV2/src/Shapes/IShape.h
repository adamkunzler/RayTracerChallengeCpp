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
	private: 
		Matrix4x4 inverseTransform;
		Matrix4x4 transform;
	
	public:		
		Material material;
		bool hasShadow;
	
		IShape()
		{ 
			setTransform(identity4x4());			
			hasShadow = true;
		}
		virtual ~IShape() {}
		
		void setTransform(const Matrix4x4& lTransform)
		{
			transform = lTransform;
			inverseTransform = inverse(transform);
		}
		const Matrix4x4 getTransform() const
		{
			return transform;
		}

		const Matrix4x4& getInverseTransform() const
		{
			return inverseTransform;
		}

		//
		// INTERSECTIONS
		//

		virtual void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const = 0;

		void intersectBy(const Ray& r, std::vector<Intersection>& intersections) const
		{
			// ray in world space to local space			
			Ray localRay(r);
			localRay = localRay.transform(inverseTransform);

			// shape figures out intersections
			localIntersectBy(localRay, intersections);
		}

		//
		// NORMALS
		//

		virtual Vector4 localNormalAt(const Point4& localPoint) const = 0;

		Vector4 normalAt(const Point4& worldPoint) const
		{
			// point in world space to local space
			Point4 localPoint = worldPoint * inverseTransform;

			// shape figures out it's normal
			Vector4 localNormal = localNormalAt(localPoint); // TODO update to return reference

			// normal from local space to world space
			Vector4 worldNormal = localNormal * transpose4x4(inverseTransform);
			worldNormal.w = 0.0f;

			return normalize(worldNormal);
		}
	};
}
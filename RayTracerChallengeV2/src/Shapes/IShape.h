#pragma once

namespace RayTracer
{			
	struct IShape
	{	
	private: 
		Matrix4x4 inverseTransform;
		Matrix4x4 transform;
	
	public:		
		Material material;
		bool hasShadow;
		IShape* parent; // should probably be Group* but fuckin' compiler...
			
		IShape();
		virtual ~IShape() {}
		
		void setTransform(const Matrix4x4& lTransform);

		const Matrix4x4 getTransform() const;

		const Matrix4x4& getInverseTransform() const;
		
		virtual void localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const = 0;

		void intersectBy(const Ray& r, std::vector<Intersection>& intersections) const;

		virtual Vector4 localNormalAt(const Point4& localPoint) const = 0;

		Point4 worldToObject(const Point4& worldPoint) const;

		Vector4 normalToWorld(const Vector4& localNormal) const;

		Vector4 normalAt(const Point4& worldPoint) const;
	};
}
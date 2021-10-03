#pragma once

//#include "../DataStructs/Matrix4x4.h"
//#include "../DataStructs/Color.h"
//#include "../Geometry/IShape.h"

namespace RayTracer
{				
	struct IShape;

	struct IPattern
	{	
	private:
		Matrix4x4 transform;
		Matrix4x4 inverseTransform;
	public:
		IPattern()
		{		
			setTransform(identity4x4());
		}

		virtual ~IPattern() {}

		void setTransform(const Matrix4x4& lTransform)
		{
			transform = lTransform;
			inverseTransform = inverse(transform);
		}

		virtual Color patternAt(const Point4& p) const = 0;

		Color patternAt(const IShape& shape, const Point4& p) const
		{			
			Point4 objectPoint = p * shape.getInverseTransform();
			return patternAt(objectPoint * inverseTransform);
		}		
	};
}
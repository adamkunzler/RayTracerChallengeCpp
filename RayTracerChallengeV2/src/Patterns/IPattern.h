#pragma once

//#include "../DataStructs/Matrix4x4.h"
//#include "../DataStructs/Color.h"
//#include "../Geometry/IShape.h"

namespace RayTracer
{				
	struct IShape;

	struct IPattern
	{	
		Matrix4x4 transform;

		IPattern()
		{		
			transform = identity4x4();
		}

		virtual ~IPattern() {}

		virtual Color patternAt(const Vector4& p) const = 0;

		Color patternAt(const IShape& shape, const Vector4& p) const
		{			
			Vector4 objectPoint = p * inverse(shape.transform);			
			return patternAt(objectPoint * inverse(transform));
		}		
	};
}
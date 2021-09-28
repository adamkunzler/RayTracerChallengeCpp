#pragma once

namespace RayTracer
{				
	class IPattern
	{		
	public:
		Matrix transform;

		IPattern()
		{		
			transform = Matrix::get4x4IdentityMatrix();
		}

		virtual ~IPattern() {}

		virtual Color patternAt(const Point& p) const = 0;

		Color patternAt(const IShape& shape, const Point& p) const
		{
			Point objectPoint = (shape.transform.inverse() * p).toPoint();
			Point patternPoint = (transform.inverse() * objectPoint).toPoint();

			return patternAt(patternPoint);			
		}		
	};
}
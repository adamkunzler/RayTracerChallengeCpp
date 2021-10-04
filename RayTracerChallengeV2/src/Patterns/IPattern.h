#pragma once

namespace RayTracer
{				
	struct IPattern
	{	
	private:
		Matrix4x4 transform;
		Matrix4x4 inverseTransform;
	
	public:
		IPattern();

		virtual ~IPattern() {}

		void setTransform(const Matrix4x4& lTransform);

		virtual Color patternAt(const Point4& p) const = 0;

		Color patternAt(const IShape& shape, const Point4& p) const;
	};
}
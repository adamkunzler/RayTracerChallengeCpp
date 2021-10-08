#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	IPattern::IPattern()
	{
		setTransform(identity4x4());
	}

	void IPattern::setTransform(const Matrix4x4& lTransform)
	{
		transform = lTransform;
		inverseTransform = inverse(transform);
	}

	Color IPattern::patternAt(const IShape& shape, const Point4& p) const
	{
		Point4 objectPoint = p * shape.getInverseTransform();
		return patternAt(objectPoint * inverseTransform);
	}
}
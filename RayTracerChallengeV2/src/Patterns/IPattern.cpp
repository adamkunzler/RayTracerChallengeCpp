#include "../Utils.h"
#include "IPattern.h"

#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"
#include "../DataStructs/Matrix4x4.h"

#include "../Shapes/IShape.h"

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
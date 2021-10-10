#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{

	Vector4 Group::localNormalAt(const Point4& localPoint) const
	{
		// groups don't have normals and this should never be called
		throw;
	}

	void Group::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		if (!localBounds().intersectBy(localRay)) return;
		
		for (std::vector<IShape*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
		{
			(*iter)->intersectBy(localRay, intersections);
		}		
	}

	void Group::addChild(IShape* shape)
	{
		shape->parent = this;
		children.push_back(shape);
	}

	// TODO cache this
	BoundingBox Group::localBounds() const
	{
		BoundingBox bb;

		for (std::vector<IShape*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
		{
			BoundingBox childBox = bb.parentSpaceBoundsOf(*(*iter));
			bb.addBoundingBox(childBox);
		}

		return BoundingBox(bb.min, bb.max);
	}
}
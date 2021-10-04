#include <cmath>
#include <vector>

#include "../Utils.h"
#include "Group.h"

#include "IShape.h"
#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "../DataStructs/Point4.h"
#include "../Geometry/Intersection.h"
#include "../Geometry/Ray.h"

namespace RayTracer
{

	Vector4 Group::localNormalAt(const Point4& localPoint) const
	{
		// groups don't have normals and this should never be called
		throw;
	}

	void Group::localIntersectBy(const Ray& localRay, std::vector<Intersection>& intersections) const
	{
		for (std::vector<IShape*>::const_iterator iter = children.begin(); iter != children.end(); iter++)
		{
			(*iter)->intersectBy(localRay, intersections);
		}
	}

	void Group::addChild(IShape& shape)
	{
		shape.parent = this;
		children.push_back(&shape);
	}
}
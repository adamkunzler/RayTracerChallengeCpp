#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	bool Intersection::isNull() { return object == NULL; }

	// equality		
	bool Intersection::operator==(const Intersection& rhs) const
	{
		return t == rhs.t && object == rhs.object;
	}

	// inequality
	bool Intersection::operator!=(const Intersection& rhs) const
	{
		return t != rhs.t || object != rhs.object;
	}

	//
	// NON-MEMBER FUNCTIONS --------------------------------------------------------------------------
	//

	bool intersectionComparer(const std::shared_ptr<Intersection> lhs, const std::shared_ptr<Intersection> rhs)
	{
		return lhs->t < rhs->t;
	}

	std::shared_ptr<Intersection> hit(std::vector<std::shared_ptr<Intersection>>& intersections)
	{
		std::sort(intersections.begin(), intersections.end(), intersectionComparer);

		for (std::vector<std::shared_ptr<Intersection>>::const_iterator iter = intersections.begin(); iter != intersections.end(); iter++)
		{
			if ((*iter)->t < 0) continue;

			// first non-negative intersection
			return *iter;
		}

		// return 'null' intersection	
		std::shared_ptr<Intersection> nullIntersection = std::shared_ptr<Intersection>(new Intersection(0, 0));
		return nullIntersection;
	}
}
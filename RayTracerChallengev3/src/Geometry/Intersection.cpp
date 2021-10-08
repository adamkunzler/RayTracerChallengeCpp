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

	bool intersectionComparer(const Intersection& lhs, const Intersection& rhs)
	{
		return lhs.t < rhs.t;
	}

	Intersection hit(std::vector<Intersection>& intersections)
	{
		std::sort(intersections.begin(), intersections.end(), intersectionComparer);

		for (std::vector<Intersection>::const_iterator iter = intersections.begin(); iter != intersections.end(); iter++)
		{
			if (iter->t < 0) continue;

			// first non-negative intersection
			return (*iter);
		}

		// return 'null' intersection		
		return Intersection(0, 0);
	}
}
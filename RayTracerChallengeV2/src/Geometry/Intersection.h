#pragma once

//#include "IShape.h"

namespace RayTracer
{	
	struct IShape;

	struct Intersection
	{		
		float t;
		IShape* object;
			
		Intersection() :t(0), object(0) {}
		Intersection(const float lT, IShape* lObject) : t(lT), object(lObject) { }				
		
		bool isNull() { return object == NULL; }

		// equality		
		bool operator==(const Intersection& rhs) const
		{
			return t == rhs.t && object == rhs.object;
		}		

		// inequality
		bool operator!=(const Intersection& rhs) const
		{
			return t != rhs.t || object != rhs.object;
		}				
	};

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
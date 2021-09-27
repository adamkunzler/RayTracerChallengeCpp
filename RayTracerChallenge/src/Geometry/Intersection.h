#pragma once

#include "IShape.h"

namespace RayTracer
{
	class IShape;

	class Intersection
	{	
	public:
		float t;
		IShape* object;
	
		/*Intersection()
		{	
			t = 0;
			object = NULL;
		}*/

		Intersection(const float lT, IShape* lObject) : t(lT), object(lObject)
		{
		}		
		
		bool isNull()
		{
			return object == NULL;
		}

		// equality
		bool operator==(const Intersection& i)
		{
			return FloatEquals(t, i.t) && (object == i.object);
		}

		// inequality
		bool operator!=(const Intersection& i)
		{
			return !(*this == i);
		}
		
		static Intersection hit(std::vector<Intersection>& intersections)
		{			
			std::sort(intersections.begin(), intersections.end(), Intersection::comparer);

			for (std::vector<Intersection>::const_iterator iter = intersections.begin(); iter != intersections.end(); iter++)
			{
				if ((*iter).t < 0) continue;

				// first non-negative intersection
				return(*iter);
			}
			
			// return 'null' intersection
			Intersection h(0, 0);
			return h;
		}

		static bool comparer(const Intersection& i1, const Intersection& i2)
		{
			return (i1.t < i2.t);
		}
	};
}
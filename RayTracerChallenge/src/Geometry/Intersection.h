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
			
		Intersection() :t(0), object(0) {}

		Intersection(const float lT, IShape* lObject) : t(lT), object(lObject)
		{
		}		
		
		/*Intersection(const Intersection& copy) : t(copy.t), object(copy.object)
		{}*/

		/*Intersection& operator=(const Intersection& other)
		{
			if (this == &other)
				return *this;

			t = other.t;
			object = other.object;

			return *this;
		}*/

		bool isNull()
		{
			return object == NULL;
		}

		static bool areEqual(const Intersection& lhs, const Intersection& rhs)
		{
			return FloatEquals(lhs.t, rhs.t) && (lhs.object == rhs.object);
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
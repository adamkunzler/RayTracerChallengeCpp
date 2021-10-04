#pragma once

namespace RayTracer
{		
	struct Intersection
	{		
		float t;
		IShape* object;
			
		Intersection() :t(0), object(0) {}
		Intersection(const float lT, IShape* lObject) : t(lT), object(lObject) { }				
		
		bool isNull();

		// equality		
		bool operator==(const Intersection& rhs) const;

		// inequality
		bool operator!=(const Intersection& rhs) const;
	};

	bool intersectionComparer(const Intersection& lhs, const Intersection& rhs);
	
	Intersection hit(std::vector<Intersection>& intersections);
}
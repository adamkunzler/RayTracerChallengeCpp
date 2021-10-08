#pragma once

namespace RayTracer
{	
	struct IShape;
	
	struct Intersection
	{		
		double t;
		IShape* object;
			
		Intersection() :t(0.0), object(0) {}
		Intersection(const double lT, IShape* lObject) : t(lT), object(lObject) { }				
		
		bool isNull();

		// equality		
		bool operator==(const Intersection& rhs) const;

		// inequality
		bool operator!=(const Intersection& rhs) const;
	};

	bool intersectionComparer(const Intersection& lhs, const Intersection& rhs);
	
	Intersection hit(std::vector<Intersection>& intersections);
}


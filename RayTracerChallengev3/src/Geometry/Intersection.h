#pragma once

namespace RayTracer
{	
	struct IShape;
	
	struct Intersection
	{		
		double t;
		IShape* object;
		double u;
		double v;
			
		Intersection() :t(0.0), object(0), u(0.0), v(0.0) {}
		Intersection(const double& lT, IShape* lObject) : t(lT), object(lObject), u(0.0), v(0.0) { }	
		Intersection(const double& lT, IShape* lObject, const double& lu, const double& lv) : t(lT), object(lObject), u(lu), v(lv) { }
		
		bool isNull();

		// equality		
		bool operator==(const Intersection& rhs) const;

		// inequality
		bool operator!=(const Intersection& rhs) const;
	};

	bool intersectionComparer(const Intersection* lhs, const Intersection* rhs);
	
	Intersection* hit(std::vector<Intersection*>& intersections);
}


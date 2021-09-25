#pragma once

namespace RayTracer
{
	namespace Tests
	{
		//
		// PLANES
		//
		
		bool Shape_Plane_NormalIsConstantEverywhere()
		{
			Plane p;
			Vector n1 = p.localNormalAt(Point(0, 0, 0));
			Vector n2 = p.localNormalAt(Point(10,0,-10));
			Vector n3 = p.localNormalAt(Point(-5, 0, 150));

			Vector expected(0, 1, 0);
			
			bool result = (n1 == expected)
				&& (n2 == expected)
				&& (n3 == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shape_Plane_NormalIsConstantEverywhere()\n";

			return result;
		}

		bool Shape_Plane_IntersectParallelRay()
		{
			Plane p;
			Ray r(Point(0, 10, 0), Vector(0, 0, 1));
			std::vector<Intersection> xs = p.localIntersectBy(r);
			
			bool result = (xs.size() == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shape_Plane_IntersectParallelRay()\n";

			return result;
		}

		bool Shape_Plane_IntersectCoplanarRay()
		{
			Plane p;
			Ray r(Point(0, 0, 0), Vector(0, 0, 1));
			std::vector<Intersection> xs = p.localIntersectBy(r);
			
			bool result = (xs.size() == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shape_Plane_IntersectCoplanarRay()\n";

			return result;
		}

		bool Shape_Plane_RayIntersectPlaneAbove()
		{
			Plane p;
			Ray r(Point(0, 1, 0), Vector(0, -1, 0));
			std::vector<Intersection> xs = p.localIntersectBy(r);

			bool result = (xs.size() == 1)
				&& (xs[0].t == 1)
				&& (xs[0].object == &p);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shape_Plane_RayIntersectPlaneAbove()\n";

			return result;
		}

		bool Shape_Plane_RayIntersectPlaneBelow()
		{
			Plane p;
			Ray r(Point(0, -1, 0), Vector(0, 1, 0));
			std::vector<Intersection> xs = p.localIntersectBy(r);

			bool result = (xs.size() == 1)
				&& (xs[0].t == 1)
				&& (xs[0].object == &p);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shape_Plane_RayIntersectPlaneBelow()\n";

			return result;
		}
	}
}
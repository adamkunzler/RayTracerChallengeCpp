#pragma once

#include <iostream>
#include <string>
#include "../src/Ray.h"
#include "../src/Sphere.h"
#include "../src/Point.h"
#include "../src/Vector.h"

namespace RayTracer
{
	namespace Tests
	{
		bool Ray_Create()
		{	
			Point p(2, 3, 4);
			Vector v(1, 0, 0);
			Ray r(p, v);

			bool result = (r.origin == p) && (r.direction == v);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Create()\n";

			return result;
		}

		bool Sphere_Create()
		{
			Sphere s;

			Point p(0, 0, 0);

			bool result = (s.origin == p) && FloatEquals(s.radius, 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Sphere_Create()\n";

			return result;
		}

		bool Ray_Position()
		{
			Point p(2, 3, 4);
			Vector v(1, 0, 0);
			Ray r(p, v);

			Point e1(2, 3, 4);
			Point e2(3, 3, 4);
			Point e3(1, 3, 4);
			Point e4(4.5f, 3, 4);

			Point p1 = r.position(0);
			Point p2 = r.position(1);
			Point p3 = r.position(-1);
			Point p4 = r.position(2.5f);

			bool result = (p1 == e1) 
				&& (p2 == e2)
				&& (p3 == e3)
				&& (p4 == e4);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Position()\n";

			return result;
		}

		bool Ray_Sphere_Intersect()
		{
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;
			
			float* xs = r.intersects(s);

			bool result = FloatEquals(xs[0], 4) && FloatEquals(xs[1], 6);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect()\n";

			delete[] xs;
			xs = 0;

			return result;
		}

		bool Ray_Sphere_Intersect_Tangent()
		{
			Ray r(Point(0, 1, -5), Vector(0, 0, 1));
			Sphere s;

			float* xs = r.intersects(s);

			bool result = FloatEquals(xs[0], 5) && FloatEquals(xs[1], 5);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Tangent()\n";

			delete[] xs;
			xs = 0;

			return result;
		}

		bool Ray_Sphere_Intersect_Misses()
		{
			Ray r(Point(0, 2, -5), Vector(0, 0, 1));
			Sphere s;

			float* xs = r.intersects(s);

			bool result = xs == NULL;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Misses()\n";

			delete[] xs;
			xs = 0;

			return result;
		}

		bool Ray_Sphere_Intersect_Inside()
		{
			Ray r(Point(0, 0, 0), Vector(0, 0, 1));
			Sphere s;

			float* xs = r.intersects(s);

			bool result = FloatEquals(xs[0], -1) && FloatEquals(xs[1], 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Inside()\n";

			delete[] xs;
			xs = 0;

			return result;
		}

		bool Ray_Sphere_Intersect_Behind()
		{
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;

			float* xs = r.intersects(s);

			bool result = FloatEquals(xs[0], 4) && FloatEquals(xs[1], 6);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Behind()\n";

			delete[] xs;
			xs = 0;

			return result;
		}
	}
}
#pragma once

namespace RayTracer
{
	namespace Tests
	{
		bool Shadows_LightWithSurfaceInShadow()
		{
			Material m;
			Point position(0, 0, 0);
			Vector eyev(0, 0, -1);
			Vector normalv(0, 0, -1);
			PointLight light(Point(0, 0, -10), Color(1, 1, 1));
			bool inShadow = true;

			Sphere s;
			Color c = light.phong(m, s, position, eyev, normalv, inShadow);

			Color expected(0.1f, 0.1f, 0.1f);

			bool result = (c == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_LightWithSurfaceInShadow()\n";

			return result;
		}

		bool Shadows_NoShadowWhenNothingColinearWithPointAndLight()
		{			
			World w = World::defaultWorld();
			Point p(0, 10, 0);

			bool isShadowed = w.isShadowed(w.lights[0], p);

			bool result = !isShadowed;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_NoShadowWhenNothingColinearWithPointAndLight()\n";

			return result;
		}

		bool Shadows_ObjectBetweenPointAndLight()
		{			
			World w = World::defaultWorld();
			Point p(10, -10, 10);

			bool isShadowed = w.isShadowed(w.lights[0], p);

			bool result = isShadowed;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_ObjectBetweenPointAndLight()\n";

			return result;
		}

		bool Shadows_ObjectBehindLight()
		{			
			World w = World::defaultWorld();
			Point p(-20, 20, -20);

			bool isShadowed = w.isShadowed(w.lights[0], p);

			bool result = !isShadowed;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_ObjectBehindLight()\n";

			return result;
		}

		bool Shadows_ObjectBehindPoint()
		{			
			World w = World::defaultWorld();
			Point p(-2, 2, -2);

			bool isShadowed = w.isShadowed(w.lights[0], p);

			bool result = !isShadowed;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_ObjectBehindPoint()\n";

			return result;
		}

		bool Shadows_ShadeHit_IntersectionInShadow()
		{			
			World w;
			w.lights.push_back(PointLight(Point(0, 0, -10), Color(1, 1, 1)));
			Sphere s1;
			w.objects.push_back(&s1);
			Sphere s2;
			s2.transform = Matrix::get4x4TranslationMatrix(0, 0, 10);
			w.objects.push_back(&s2);

			Ray r(Point(0, 0, 5), Vector(0, 0, 1));
			Intersection i(4, &s2);

			Computation comps = w.prepareComputations(i, r, std::vector<Intersection> { i });
			Color c = w.shadeHit(comps, 0);

			Color expected(0.1f, 0.1f, 0.1f);

			bool result = (c == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_ShadeHit_IntersectionInShadow()\n";

			return result;
		}

		bool Shadows_HitShouldOffsetPoint()
		{			
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;
			s.transform = Matrix::get4x4TranslationMatrix(0, 0, 1);
			Intersection i(5.0f, &s);
			
			World w;
			Computation comps = w.prepareComputations(i, r, std::vector<Intersection> { i });
			
			bool result = (comps.overPoint.z < -EPSILON/2)
				&& (comps.point.z > comps.overPoint.z);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Shadows_HitShouldOffsetPoint()\n";

			return result;
		}
	}

}
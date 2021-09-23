#pragma once

namespace RayTracer
{
	namespace Tests
	{
		bool World_Create()
		{
			World w;
			bool result = (w.lights.size() == 0) && (w.objects.size() == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Create()\n";

			return result;
		}		
		
		bool World_RayIntersect()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			std::vector<Intersection> inters = w.intersectBy(r);
			
			bool result = FloatEquals(inters[0].t, 4)
				&& FloatEquals(inters[1].t, 4.5f)
				&& FloatEquals(inters[2].t, 5.5f)
				&& FloatEquals(inters[3].t, 6);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_RayIntersect()\n";

			return result;
		}

		bool World_RayIntersect_Precompute()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;
			Intersection i(4, &s);

			Computation c = w.prepareComputations(i, r);

			Point pe(0, 0, -1);
			Vector ve1(0, 0, -1);
			Vector ve2(0, 0, -1);

			bool result = FloatEquals(c.t, 4)
				&& (c.object == ((IShape*)&s))
				&& (c.point == pe)
				&& (c.eyeV == ve1)
				&& (c.normalV == ve2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_RayIntersect_Precompute()\n";

			return result;
		}

		bool World_RayIntersect_Precompute_Outside()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;
			Intersection i(4, &s);

			Computation c = w.prepareComputations(i, r);

			bool result = !c.isInside;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_RayIntersect_Precompute_Outside()\n";

			return result;
		}

		bool World_RayIntersect_Precompute_Inside()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, 0), Vector(0, 0, 1));
			Sphere s;
			Intersection i(1, &s);

			Computation c = w.prepareComputations(i, r);
			
			Point pe(0, 0, 1);
			Vector ve1(0, 0, -1);
			Vector ve2(0, 0, -1);

			bool result = c.isInside
				&& (c.point == pe)
				&& (c.eyeV == ve1)
				&& (c.normalV == ve2);;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_RayIntersect_Precompute_Inside()\n";

			return result;
		}

		bool World_Shade_Intersection()
		{			
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));			
			Intersection i(4, w.objects[0]);
			Computation c = w.prepareComputations(i, r);
			Color color = w.shadeHit(c);
			Color ce = Color(0.38066f, 0.47583f, 0.2855f);

			bool result = (color == ce);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Shade_Intersection()\n";

			return result;
		}

		bool World_Shade_Intersection_Inside()
		{
			World w = World::defaultWorld();
			PointLight l(Point(0, 0.25f, 0), Color(1, 1, 1));
			Ray r(Point(0, 0, 0), Vector(0, 0, 1));
			Intersection i(0.5f, w.objects[1]);
			Computation c = w.prepareComputations(i, r);
			Color color = w.shadeHit(c);
			Color ce = Color(0.90498f, 0.90498f, 0.90498f);
			
			bool result = (color == ce);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Shade_Intersection_Inside()\n";

			std::cout << "\t NEED TO FIGURE OUT WHY NOT PASSING\n";

			return result;
		}

		bool World_Shade_RayMiss()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 1, 0));
			Color c = w.colorAt(r);
			
			bool result = c.isBlack();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Shade_RayMiss()\n";

			return result;
		}

		bool World_Shade_RayHit()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Color c = w.colorAt(r);

			Color ce(0.38066, 0.47583, 0.2855);

			bool result = (c == ce);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Shade_RayHit()\n";

			return result;
		}

		bool World_Shade_IntersectionBehindRay()
		{
			World w = World::defaultWorld();
			
			IShape* outer = w.objects[0];
			outer->material.ambient = 1;
			
			IShape* inner = w.objects[1];
			inner->material.ambient = 1;

			Ray r(Point(0, 0, 0.75f), Vector(0, 0, -1));
			
			Color c = w.colorAt(r);
			
			bool result = (c == inner->material.color);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Shade_IntersectionBehindRay()\n";

			return result;
		}

		bool World_ViewTransform_Default()
		{
			Point from(0, 0, 0);
			Point to(0, 0, -1);
			Vector up(0, 1, 0);

			Matrix vt = World::viewTransform(from, to, up);
			Matrix identity = Matrix::get4x4IdentityMatrix();

			bool result = (vt == identity);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_Default()\n";

			return result;
		}

		bool World_ViewTransform_PositiveZ()
		{
			Point from(0, 0, 0);
			Point to(0, 0, 1);
			Vector up(0, 1, 0);

			Matrix vt = World::viewTransform(from, to, up);

			Matrix expected = Matrix::get4x4ScalingMatrix(-1, 1, -1);

			bool result = (vt == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_PositiveZ()\n";

			return result;
		}

		bool World_ViewTransform_WorldMoves()
		{
			Point from(0, 0, 8);
			Point to(0, 0, 0);
			Vector up(0, 1, 0);

			Matrix vt = World::viewTransform(from, to, up);

			Matrix expected = Matrix::get4x4TranslationMatrix(0, 0, -8);

			bool result = (vt == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_WorldMoves()\n";

			return result;
		}

		bool World_ViewTransform_Arbitrary()
		{
			Point from(1, 3, 2);
			Point to(4, -2, 8);
			Vector up(1, 1, 0);

			Matrix vt = World::viewTransform(from, to, up);

			Matrix expected(4, 4, new float[] {
				-0.50709, 0.50709,  0.67612, -2.36643,
				 0.76772, 0.60609,  0.12122, -2.82843,
				-0.35857, 0.59761, -0.71714,  0,
				 0,       0,        0,        1
			});

			std::cout << "\nActual:\n" << vt << "\n";
			std::cout << "\nExpected:\n" << expected << "\n";

			bool result = (vt == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_Arbitrary()\n";

			return result;
		}
	}
}
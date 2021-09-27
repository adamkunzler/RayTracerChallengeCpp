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
			Color color = w.shadeHit(c, 0);
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
			Color color = w.shadeHit(c, 0);
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
			Color c = w.colorAt(r, 0);
			
			bool result = c.isBlack();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Shade_RayMiss()\n";

			return result;
		}

		bool World_Shade_RayHit()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Color c = w.colorAt(r, 0);

			Color ce(0.38066f, 0.47583f, 0.2855f);

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
			
			Color c = w.colorAt(r, 0);
			
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

			Matrix expected(4, 4, std::unique_ptr<float[]>(new float[] {
				-0.50709f, 0.50709f,  0.67612f, -2.36643f,
				 0.76772f, 0.60609f,  0.12122f, -2.82843f,
				-0.35857f, 0.59761f, -0.71714f,  0,
				 0,       0,        0,        1
			}));

			//std::cout << "\nActual:\n" << vt << "\n";
			//std::cout << "\nExpected:\n" << expected << "\n";

			bool result = (vt == expected);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_Arbitrary()\n";

			return result;
		}

		bool Camera_Create()
		{
			Camera c(160, 120, PI / 2.0f);

			Matrix i = Matrix::get4x4IdentityMatrix();

			bool result = (c.hSize == 160)
				&& (c.vSize == 120)
				&& FloatEquals(c.fov, PI / 2.0f)
				&& (c.transform == i);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Camera_Create()\n";

			return result;
		}

		bool Camera_PixelSize_Horizontal()
		{
			Camera c(200, 125, PI / 2);
			
			bool result = FloatEquals(c.pixelSize, 0.01f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Camera_PixelSize_Horizontal()\n";

			return result;
		}

		bool Camera_PixelSize_Vertical()
		{
			Camera c(125, 200, PI / 2);

			bool result = FloatEquals(c.pixelSize, 0.01f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Camera_PixelSize_Vertical()\n";

			return result;
		}

		bool Camera_CenterOfCanvas()
		{
			Camera c(201, 101, PI / 2);
			Ray r = c.rayForPixel(100, 50);

			Point pe(0, 0, 0);
			Vector ve(0, 0, -1);

			bool result = (r.origin == pe) 
				&& (r.direction == ve);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Camera_CenterOfCanvas()\n";

			return result;
		}

		bool Camera_CornerOfCanvas()
		{
			Camera c(201, 101, PI / 2);
			Ray r = c.rayForPixel(0, 0);

			Point pe(0, 0, 0);
			Vector ve(0.66519f, 0.33259f, -0.66851f);

			bool result = (r.origin == pe)
				&& (r.direction == ve);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_Arbitrary()\n";

			return result;
		}

		bool Camera_Transformed()
		{
			Camera c(201, 101, PI / 2);
			c.transform = Matrix::get4x4RotationMatrix_Y(PI / 4) * Matrix::get4x4TranslationMatrix(0, -2, 5);

			Ray r = c.rayForPixel(100, 50);

			float sqrt2over2 = std::sqrtf(2) / 2;
			Point pe(0, 2, -5);
			Vector ve(sqrt2over2, 0, -sqrt2over2);

			bool result = (r.origin == pe)
				&& (r.direction == ve);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_ViewTransform_Arbitrary()\n";

			return result;
		}

		bool RenderWorld()
		{
			World w = World::defaultWorld();
			Camera c(11, 11, PI / 2.0f);
			Point from(0, 0, -5);
			Point to(0, 0, 0);
			Vector up(0, 1, 0);
			c.transform = World::viewTransform(from, to, up);

			Canvas image = w.render(c);
			image.toPPM("images/tests_RenderWorld.ppm");
			
			Color e(0.38066f, 0.47583f, 0.2855f);
			Color a = image.pixelAt(5, 5);

			bool result = (a == e);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "RenderWorld()\n";

			return result;
		}
	}
}
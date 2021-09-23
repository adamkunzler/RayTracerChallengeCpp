#pragma once



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
			
			std::vector<Intersection> inters = s.intersects(r);

			bool result = inters.size() == 2
				&& (inters[0].object == &s)
				&& FloatEquals(inters[0].t, 4) 
				&& FloatEquals(inters[1].t, 6);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect()\n";
			
			return result;
		}

		bool Ray_Sphere_Intersect_Tangent()
		{
			Ray r(Point(0, 1, -5), Vector(0, 0, 1));
			Sphere s;

			std::vector<Intersection> inters = s.intersects(r);

			bool result = inters.size() == 2
				&& (inters[0].object == &s)
				&& FloatEquals(inters[0].t, 5)
				&& FloatEquals(inters[1].t, 5);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Tangent()\n";
			
			return result;
		}

		bool Ray_Sphere_Intersect_Misses()
		{
			Ray r(Point(0, 2, -5), Vector(0, 0, 1));
			Sphere s;

			std::vector<Intersection> inters = s.intersects(r);

			bool result = inters.size() == 0;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Misses()\n";

			return result;
		}

		bool Ray_Sphere_Intersect_Inside()
		{
			Ray r(Point(0, 0, 0), Vector(0, 0, 1));
			Sphere s;

			std::vector<Intersection> inters = s.intersects(r);

			bool result = inters.size() == 2
				&& (inters[0].object == &s)
				&& FloatEquals(inters[0].t, -1)
				&& FloatEquals(inters[1].t, 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Inside()\n";

			return result;
		}

		bool Ray_Sphere_Intersect_Behind()
		{
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;

			std::vector<Intersection> inters = s.intersects(r);

			bool result = (inters.size() == 2)
				&& (inters[0].object == &s)
				&& FloatEquals(inters[0].t, 4)
				&& FloatEquals(inters[1].t, 6);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Behind()\n";

			return result;
		}

		bool Ray_Sphere_Intersect_Intersection()
		{			
			Sphere s;
			Intersection i(3.5f, &s);
			
			bool result = FloatEquals(i.t, 3.5f) && (i.object == &s);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_Intersection()\n";

			return result;
		}

		bool Ray_Sphere_Intersection_AllPositive()
		{
			Sphere s;
			Intersection i1(1, &s);
			Intersection i2(2, &s);
			std::vector<Intersection> inters;
			inters.push_back(i2);
			inters.push_back(i1);

			Intersection i = Intersection::hit(inters);
			
			bool result = (i == i1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersection_AllPositive()\n";

			return result;
		}

		bool Ray_Sphere_Intersection_SomeNegative()
		{
			Sphere s;
			Intersection i1(-1, &s);
			Intersection i2(1, &s);
			std::vector<Intersection> inters;
			inters.push_back(i2);
			inters.push_back(i1);

			Intersection i = Intersection::hit(inters);

			bool result = (i == i2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersection_SomeNegative()\n";

			return result;
		}

		bool Ray_Sphere_Intersection_AllNegative()
		{
			Sphere s;
			Intersection i1(-2, &s);
			Intersection i2(-1, &s);
			std::vector<Intersection> inters;
			inters.push_back(i2);
			inters.push_back(i1);

			Intersection i = Intersection::hit(inters);

			bool result = i.isNull();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersection_AllNegative()\n";

			return result;
		}

		bool Ray_Sphere_Intersection_LowestNonNegative()
		{
			Sphere s;
			Intersection i1(5, &s);
			Intersection i2(7, &s);
			Intersection i3(-3, &s);
			Intersection i4(2, &s);
			
			std::vector<Intersection> inters;
			inters.push_back(i1);
			inters.push_back(i2);
			inters.push_back(i3);
			inters.push_back(i4);

			Intersection i = Intersection::hit(inters);

			bool result = (i == i4);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersection_LowestNonNegative()\n";

			return result;
		}

		bool Ray_Sphere_TranslateRay()
		{
			Ray r(Point(1, 2, 3), Vector(0, 1, 0));
			Matrix m = Matrix::get4x4TranslationMatrix(3, 4, 5);
			Ray r2 = r.transform(m);
			
			Point pe(4, 6, 8);
			Vector ve(0, 1, 0);

			bool result = (r2.origin == pe) 
				&& (r2.direction == ve);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_TranslateRay()\n";

			return result;
		}

		bool Ray_Sphere_ScaleRay()
		{
			Ray r(Point(1, 2, 3), Vector(0, 1, 0));
			Matrix m = Matrix::get4x4ScalingMatrix(2, 3, 4);
			Ray r2 = r.transform(m);

			Point pe(2, 6, 12);
			Vector ve(0, 3, 0);

			bool result = (r2.origin == pe)
				&& (r2.direction == ve);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_ScaleRay()\n";

			return result;
		}

		bool Ray_Sphere_DefaultSphereTransform()
		{
			Sphere s;
			Matrix m = Matrix::get4x4IdentityMatrix();

			bool result = (s.transform == m);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_DefaultSphereTransform()\n";

			return result;
		}

		bool Ray_Sphere_ChangeSphereTransform()
		{
			Sphere s;
			Matrix t = Matrix::get4x4TranslationMatrix(2, 3, 4);
			s.transform = t;

			bool result = (s.transform == t);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_ChangeSphereTransform()\n";

			return result;
		}

		bool Ray_Sphere_Intersect_ScaledSphere()
		{
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;
			s.transform = Matrix::get4x4ScalingMatrix(2, 2, 2);

			std::vector<Intersection> inters = s.intersects(r);
			
			bool result = (inters.size() == 2)
				&& FloatEquals(inters[0].t, 3)
				&& FloatEquals(inters[1].t, 7);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_ScaledSphere()\n";

			return result;
		}

		bool Ray_Sphere_Intersect_TranslatedSphere()
		{
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s;
			s.transform = Matrix::get4x4TranslationMatrix(5, 0, 0);

			std::vector<Intersection> inters = s.intersects(r);

			bool result = (inters.size() == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Ray_Sphere_Intersect_TranslatedSphere()\n";

			return result;
		}
	}
}
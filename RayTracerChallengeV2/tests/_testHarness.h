#pragma once

namespace RayTracer
{
	namespace Tests
	{
		World* defaultWorld()
		{			
			World* w = new World();
			w->lights.push_back(PointLight(Point4(-10, 10, -10), Color(1, 1, 1)));

			Sphere* s1 = new Sphere();
			s1->material.color = Color(0.8f, 1.0f, 0.6f);
			s1->material.diffuse = 0.7f;
			s1->material.specular = 0.2f;

			Sphere* s2 = new Sphere();
			s2->setTransform(scaling(0.5f, 0.5f, 0.5f));

			w->objects.push_back(s1);
			w->objects.push_back(s2);

			return w;
		}

		Sphere* GlassSphere()
		{
			Sphere* s = new Sphere();
			s->setTransform(identity4x4());
			s->material.transparency = 1.0f;
			s->material.refractiveIndex = 1.5f;
			return s;
		}

		struct TestPattern : public IPattern
		{
			TestPattern() {}
			~TestPattern() {}
			Color patternAt(const Point4& p) const { return Color(p.x, p.y, p.z); }
		};

		struct TestResults
		{
			TestResults() : numPassed(0)
			{}

			int numPassed;
			std::vector<std::string> failedTests;
		};

		TestResults _tests();

		void RunTests()
		{
			std::cout << "Running tests...\n";

			auto start = std::chrono::high_resolution_clock::now();

			TestResults results = _tests();

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			int totalTests = results.numPassed + (int)results.failedTests.size();

			std::cout << "\n\n-------------------------------------------------------------------";
			std::cout << "\n\n" << totalTests << " tests Completed in " << duration.count() << "ms.\n";
			std::cout << "\nPassing Tests: " << results.numPassed;
			std::cout << "\nFailing Tests: " << results.failedTests.size() << std::endl;

			// write out the failed tests
			for (std::vector<std::string>::const_iterator iter = results.failedTests.begin(); iter != results.failedTests.end(); ++iter)
			{
				std::cout << "\t" << *iter << std::endl;
			}

			std::cout << "\n-------------------------------------------------------------------\n\n";
		}

		TestResults _tests()
		{
			int numPassed(0);
			std::vector<std::string> failedTests;

			//
			// Chapter 3 - Matrices
			//

			if(true) 
			{
				{
					std::string scenario = "Chapter 3 - Matrix equality with identical matrices";

					Matrix4x4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
					Matrix4x4 b(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);

					bool result = a == b;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Matrix equality with different matrices";

					Matrix4x4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
					Matrix4x4 b(2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1);

					bool result = a != b;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Multiplying two matrices";

					Matrix4x4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2);
					Matrix4x4 b(-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8);
					Matrix4x4 e(20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42);

					bool result = e == (a * b);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Matrix multiplied by a tuple *** vector";

					Matrix4x4 a(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1);
					Vector4 b(1, 2, 3, 1);
					Vector4 e(18, 24, 33, 1);

					bool result = e == a * b;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Multiplying a matrix by the identity matrix";

					Matrix4x4 a(0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32);

					bool result = a * identity4x4() == a;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Multiplying the identity matrix by a tuple ***";

					Vector4 a(1, 2, 3, 4);

					bool result = identity4x4() * a == a;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Transposing a matrix";

					Matrix4x4 a(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8);
					Matrix4x4 ta(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8);

					bool result = transpose4x4(a) == ta;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Transposing the identity matrix";

					Matrix4x4 a = transpose4x4(identity4x4());

					bool result = a == identity4x4();

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Calculating the inverse of a matrix";

					Matrix4x4 a(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);
					Matrix4x4 b(
						0.21805f, 0.45113f, 0.24060f, -0.04511f,
						-0.80827f, -1.45677f, -0.44361f, 0.52068f,
						-0.07895f, -0.22368f, -0.05263f, 0.19737f,
						-0.52256f, -0.81391f, -0.30075f, 0.30639f
					);
					
					bool result = inverse(a).equals(b);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Calculating the inverse of another matrix";

					RayTracer::Matrix4x4 m(
						8.0f, -5.0f, 9.0f, 2.0f,
						7.0f, 5.0f, 6.0f, 1.0f,
						-6.0f, 0.0f, 9.0f, 6.0f,
						-3.0f, 0.0f, -9.0f, -4.0f);

					RayTracer::Matrix4x4 expected(
						-0.15385f, -0.15385f, -0.28205f, -0.53846f,
						-0.07692f, 0.12308f, 0.02564f, 0.03077f,
						0.35897f, 0.35897f, 0.43590f, 0.92308f,
						-0.69231f, -0.69231f, -0.76923f, -1.92308f);
					
					bool result = inverse(m).equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Calculating the inverse of a third matrix";

					RayTracer::Matrix4x4 m(
						9.0f, 3.0f, 0.0f, 9.0f,
						-5.0f, -2.0f, -6.0f, -3.0f,
						-4.0f, 9.0f, 6.0f, 4.0f,
						-7.0f, 6.0f, 6.0f, 2.0f);

					RayTracer::Matrix4x4 expected(
						-0.04074f, -0.07778f, 0.14444f, -0.22222f,
						-0.07778f, 0.03333f, 0.36667f, -0.33333f,
						-0.02901f, -0.14630f, -0.10926f, 0.12963f,
						0.17778f, 0.06667f, -0.26667f, 0.33333f);
					
					bool result = inverse(m).equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 3 - Multiplying a product by its inverse";

					Matrix4x4 a(3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1);
					Matrix4x4 b(8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5);
					Matrix4x4 c = a * b;
					
					bool result = (c * inverse(b)).equals(a);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}
			}

			//
			// Chapter 4 - Matrix Transformation
			//

			if(true)
			{

				{
					std::string scenario = "Chapter 4 - Multiplying by a translation matrix";

					Matrix4x4 t = translation(5, -3, 2);
					Point4 p(-3, 4, 5);
					Vector4 e(2, 1, 7);

					bool result = (t * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Multiplying by the inverse of a translation matrix";
					
					Matrix4x4 t = translation(5, -3, 2);
					Matrix4x4 inv = inverse(t);
					Point4 p(-3, 4, 5);
					Vector4 e(-8, 7, 3);

					bool result = (inv * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Translation does not affect vectors";

					Matrix4x4 t = translation(5, -3, 2);
					Vector4 v(-3, 4, 5);

					bool result = (t * v).equals(v);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - A scaling matrix applied to a point";

					Matrix4x4 t = scaling(2, 3, 4);
					Point4 p(-4, 6, 8);
					Point4 e(-8, 18, 32);

					bool result = (t * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - A scaling matrix applied to a vector";

					Matrix4x4 t = scaling(2, 3, 4);
					Vector4 p(-4, 6, 8);
					Vector4 e(-8, 18, 32);

					bool result = (t * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Multiplying by the inverse of a scaling matrix";
					
					Matrix4x4 t = scaling(2, 3, 4);
					Matrix4x4 inv = inverse(t);
					Vector4 p(-4, 6, 8);
					Vector4 e(-2, 2, 2);

					bool result = (inv * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Reflection is a scaling by a negative value";

					Matrix4x4 t = scaling(-1, 1, 1);
					Point4 p(2, 3, 4);
					Point4 e(-2, 3, 4);

					bool result = (t * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Rotating a point around the x-axis";

					Point4 p(0, 1, 0);
					Matrix4x4 halfQuarter = xRotation4x4(PI / 4.0f);
					Matrix4x4 fullQuarter = xRotation4x4(PI / 2.0f);

					Point4 e1(0, sqrt2over2, sqrt2over2);
					Point4 e2(0, 0, 1);

					bool result = (halfQuarter * p).equals(e1)
						&& (fullQuarter * p).equals(e2);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - The inverse of an x-rotation rotates in the opposite direction";
					
					Point4 p(0, 1, 0);
					Matrix4x4 halfQuarter = xRotation4x4(PI / 4.0f);
					Matrix4x4 inv = inverse(halfQuarter);
					Point4 e1(0, sqrt2over2, -sqrt2over2);

					bool result = (inv * p).equals(e1);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Rotating a point around the y-axis";

					Point4 p(0, 0, 1);
					Matrix4x4 halfQuarter = yRotation4x4(PI / 4.0f);
					Matrix4x4 fullQuarter = yRotation4x4(PI / 2.0f);

					Point4 e1(sqrt2over2, 0, sqrt2over2);
					Point4 e2(1, 0, 0);

					bool result = (halfQuarter * p).equals(e1)
						&& (fullQuarter * p).equals(e2);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Rotating a point around the z-axis";

					Point4 p(0, 1, 0);
					Matrix4x4 halfQuarter = zRotation4x4(PI / 4.0f);
					Matrix4x4 fullQuarter = zRotation4x4(PI / 2.0f);

					Point4 e1(-sqrt2over2, sqrt2over2, 0);
					Point4 e2(-1, 0, 0);

					bool result = (halfQuarter * p).equals(e1)
						&& (fullQuarter * p).equals(e2);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Individual transformations are applied in sequence";

					Point4 p(1, 0, 1);
					Matrix4x4 A = xRotation4x4(PI / 2.0f);
					Matrix4x4 B = scaling(5, 5, 5);
					Matrix4x4 C = translation(10, 5, 7);

					Point4 p2 = A * p;
					Point4 e2(1, -1, 0);

					Point4 p3 = B * p2;
					Point4 e3(5, -5, 0);

					Point4 p4 = C * p3;
					Point4 e4(15, 0, 7);

					bool result = p2.equals(e2) && p3.equals(e3) && p4.equals(e4);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 4 - Chained transformations must be applied in reverse order";

					Point4 p(1, 0, 1);
					Matrix4x4 A = xRotation4x4(PI / 2.0f);
					Matrix4x4 B = scaling(5, 5, 5);
					Matrix4x4 C = translation(10, 5, 7);

					Matrix4x4 T = C * B * A;
					Point4 e(15, 0, 7);

					bool result = (T * p).equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}
			}


			//
			// Chapter 12 - Cubes
			//

			if(true)
			{
				{
					std::string scenario = "Chapter 12 - A ray intersects a cube";

					Cube c;

					Ray r1(Point4(5, 0.5, 0), Vector4(-1, 0, 0));
					std::vector<Intersection> xs1;
					c.localIntersectBy(r1, xs1);

					Ray r2(Point4(-5, 0.5, 0), Vector4(1, 0, 0));
					std::vector<Intersection> xs2;
					c.localIntersectBy(r2, xs2);

					Ray r3(Point4(0.5, 5, 0), Vector4(0, -1, 0));
					std::vector<Intersection> xs3;
					c.localIntersectBy(r3, xs3);

					Ray r4(Point4(0.5, -5, 0), Vector4(0, 1, 0));
					std::vector<Intersection> xs4;
					c.localIntersectBy(r4, xs4);

					Ray r5(Point4(0.5, 0, 5), Vector4(0, 0, -1));
					std::vector<Intersection> xs5;
					c.localIntersectBy(r5, xs5);

					Ray r6(Point4(0.5, 0, -5), Vector4(0, 0, 1));
					std::vector<Intersection> xs6;
					c.localIntersectBy(r6, xs6);

					Ray r7(Point4(0, 0.5f, 0), Vector4(0, 0, 1));
					std::vector<Intersection> xs7;
					c.localIntersectBy(r7, xs7);

					bool result =
						(feq(xs1[0].t, 4) && feq(xs1[1].t, 6))
						&& (feq(xs2[0].t, 4) && feq(xs2[1].t, 6))
						&& (feq(xs3[0].t, 4) && feq(xs3[1].t, 6))
						&& (feq(xs4[0].t, 4) && feq(xs4[1].t, 6))
						&& (feq(xs5[0].t, 4) && feq(xs5[1].t, 6))
						&& (feq(xs6[0].t, 4) && feq(xs6[1].t, 6))
						&& (feq(xs7[0].t, -1) && feq(xs7[1].t, 1));

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 12 - A ray misses a cube";

					Cube c;
					Ray r1(Point4(-2, 0, 0), Vector4(0.2673f, 0.5345f, 0.8018f));
					Ray r2(Point4(0, -2, 0), Vector4(0.8018f, 0.2673f, 0.5345f));
					Ray r3(Point4(0, 0, -2), Vector4(0.5345f, 0.8018f, 0.2673f));
					Ray r4(Point4(2, 0, 2), Vector4(0, 0, -1));
					Ray r5(Point4(0, 2, 2), Vector4(0, -1, 0));
					Ray r6(Point4(2, 2, 0), Vector4(-1, 0, 0));

					std::vector<Intersection> xs1;
					c.localIntersectBy(r1, xs1);
					std::vector<Intersection> xs2;
					c.localIntersectBy(r2, xs2);
					std::vector<Intersection> xs3;
					c.localIntersectBy(r3, xs3);
					std::vector<Intersection> xs4;
					c.localIntersectBy(r4, xs4);
					std::vector<Intersection> xs5;
					c.localIntersectBy(r5, xs5);
					std::vector<Intersection> xs6;
					c.localIntersectBy(r6, xs6);

					bool result = xs1.size() == 0
						&& xs2.size() == 0
						&& xs3.size() == 0
						&& xs4.size() == 0
						&& xs5.size() == 0
						&& xs6.size() == 0;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 12 - The normal on the surface of a cube";

					Cube c;
					Point4 p1(1, 0.5f, -0.8f);
					Point4 p2(-1, -0.2f, 0.9f);
					Point4 p3(-0.4f, 1, -0.1f);
					Point4 p4(0.3f, -1, -0.7f);
					Point4 p5(-0.6f, 0.3f, 1);
					Point4 p6(0.4f, 0.4f, -1);
					Point4 p7(1, 1, 1);
					Point4 p8(-1, -1, -1);

					Vector4 n1 = c.localNormalAt(p1);
					Vector4 n2 = c.localNormalAt(p2);
					Vector4 n3 = c.localNormalAt(p3);
					Vector4 n4 = c.localNormalAt(p4);
					Vector4 n5 = c.localNormalAt(p5);
					Vector4 n6 = c.localNormalAt(p6);
					Vector4 n7 = c.localNormalAt(p7);
					Vector4 n8 = c.localNormalAt(p8);

					Vector4 e1(1, 0, 0);
					Vector4 e2(-1, 0, 0);
					Vector4 e3(0, 1, 0);
					Vector4 e4(0, -1, 0);
					Vector4 e5(0, 0, 1);
					Vector4 e6(0, 0, -1);
					Vector4 e7(1, 0, 0);
					Vector4 e8(-1, 0, 0);

					bool result = n1.equals(e1)
						&& n2.equals(e2)
						&& n3.equals(e3)
						&& n4.equals(e4)
						&& n5.equals(e5)
						&& n6.equals(e6)
						&& n7.equals(e7)
						&& n8.equals(e8);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}				
			}

			//
			// Chapter 11 - Reflection and Refraction
			//

			if (true)
			{
				{
					std::string scenario = "Chapter 11 - Reflectivity for the default material";

					Material m;
					bool result = feq(m.reflective, 0.0f);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - Precomputing the reflection vector";
					
					World w;
					Plane p;
					Ray r(Point4(0, 1, -1), Vector4(0, -sqrt2over2, sqrt2over2));
					Intersection i(sqrt2, &p);
					Computation comps = w.prepareComputations(i, r, std::vector<Intersection> { i });

					Vector4 expected(0, sqrt2over2, sqrt2over2);

					bool result = comps.reflectV.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The reflected color for a nonreflective material";

					World* w = defaultWorld();
					Ray r(Point4(0, 0, 0), Vector4(0, 0, 1));
					Sphere* s = (Sphere*)w->objects[1];
					s->material.ambient = 1;
					Intersection i(1, s);
					Computation comps = w->prepareComputations(i, r, std::vector<Intersection> { i });
					Color c = w->reflectedColor(comps, 0);

					Color expected(0, 0, 0);

					bool result = c.equals(expected);

					delete w;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The reflected color for a reflective material";

					World* w = defaultWorld();
					Plane shape;
					shape.material.reflective = 0.5f;
					shape.setTransform(translation(0, -1, 0));
					w->objects.push_back(&shape);
					Ray r(Point4(0, 0, -3), Vector4(0, -sqrt2over2, sqrt2over2));
					Intersection i(sqrt2, &shape);
					Computation comps = w->prepareComputations(i, r, std::vector<Intersection> { i });
					Color c = w->reflectedColor(comps, MAX_RECURSION);

					Color expected(0.19032f, 0.2379f, 0.14274f);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - shadeHit() with a reflective material";

					World* w = defaultWorld();
					Plane shape;
					shape.material.reflective = 0.5f;
					shape.setTransform(translation(0, -1, 0));
					w->objects.push_back(&shape);
					Ray r(Point4(0, 0, -3), Vector4(0, -sqrt2over2, sqrt2over2));					
					std::vector<Intersection> xs{
						Intersection(sqrt2, &shape)
					};
					Computation comps = w->prepareComputations(xs[0], r, xs);
					Color c = w->shadeHit(comps, MAX_RECURSION, xs);

					Color expected(0.87677f, 0.92436f, 0.82918f);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - colorAt() with mutually reflective surfaces";

					World w;
					PointLight light(Point4(0, 0, 0), Color(1, 1, 1));
					w.lights.push_back(light);

					Plane lower;
					lower.material.reflective = 1;
					lower.setTransform(translation(0, -1, 0));
					w.objects.push_back(&lower);

					Plane upper;
					upper.material.reflective = 1;
					upper.setTransform(translation(0, 1, 0));
					w.objects.push_back(&upper);

					Ray r(Point4(0, 0, 0), Vector4(0, 1, 0));

					std::vector<Intersection> intersections;
					Color c = w.colorAt(r, 0, intersections);

					// isn't recursive???
					bool result = true;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The reflected color at the maximum recursive depth";

					World* w = defaultWorld();
					Plane shape;
					shape.material.reflective = 0.5f;
					shape.setTransform(translation(0, -1, 0));
					w->objects.push_back(&shape);

					Ray r(Point4(0, 0, -3), Vector4(0, -sqrt2over2, sqrt2over2));
					Intersection i(sqrt2, &shape);
					Computation comps = w->prepareComputations(i, r, std::vector<Intersection> { i });
					Color c = w->reflectedColor(comps, 0);

					Color expected(0, 0, 0);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - Transparency anf Refractive index for the default material";

					Material m;

					bool result = feq(m.transparency, 0)
						&& feq(m.refractiveIndex, 1);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - A helper for producing a sphere with a glassy material";

					Sphere s = *GlassSphere();

					bool result = feq(s.material.transparency, 1)
						&& feq(s.material.refractiveIndex, 1.5);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - Finding n1 and n2 at various intersections";

					Sphere a = *GlassSphere();
					a.setTransform(scaling(2, 2, 2));
					a.material.refractiveIndex = 1.5f;

					Sphere b = *GlassSphere();
					b.setTransform(translation(0, 0, -0.25));
					b.material.refractiveIndex = 2.0f;

					Sphere c = *GlassSphere();
					c.setTransform(translation(0, 0, 0.25f));
					c.material.refractiveIndex = 2.5f;

					Ray r(Point4(0, 0, -4), Vector4(0, 0, 1));

					std::vector<Intersection> intersections;
					intersections.push_back(Intersection(2, &a));
					intersections.push_back(Intersection(2.75f, &b));
					intersections.push_back(Intersection(3.25f, &c));
					intersections.push_back(Intersection(4.75f, &b));
					intersections.push_back(Intersection(5.25f, &c));
					intersections.push_back(Intersection(6, &a));

					World w;
					Computation c0 = w.prepareComputations(intersections[0], r, intersections);
					Computation c1 = w.prepareComputations(intersections[1], r, intersections);
					Computation c2 = w.prepareComputations(intersections[2], r, intersections);
					Computation c3 = w.prepareComputations(intersections[3], r, intersections);
					Computation c4 = w.prepareComputations(intersections[4], r, intersections);
					Computation c5 = w.prepareComputations(intersections[5], r, intersections);

					bool result = feq(c0.n1, 1.0f) && feq(c0.n2, 1.5f)
						&& feq(c1.n1, 1.5f) && feq(c1.n2, 2.0f)
						&& feq(c2.n1, 2.0f) && feq(c2.n2, 2.5f)
						&& feq(c3.n1, 2.5f) && feq(c3.n2, 2.5f)
						&& feq(c4.n1, 2.5f) && feq(c4.n2, 1.5f)
						&& feq(c5.n1, 1.5f) && feq(c5.n2, 1.0f);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The under point is offset below the surface";

					Ray r(Point4(0, 0, -5), Vector4(0, 0, 1));
					Sphere s = *GlassSphere();
					s.setTransform(translation(0, 0, 1));
					Intersection i(5, &s);
					std::vector<Intersection> xs = { i };
					World w;
					Computation comps = w.prepareComputations(i, r, xs);

					bool result = (comps.underPoint.z > EPSILON / 2)
						&& (comps.point.z < comps.underPoint.z);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The refracted color with an opaque surface";

					World* w = defaultWorld();
					Ray r(Point4(0, 0, -5), Vector4(0, 0, 1));
					std::vector<Intersection> xs = {
						Intersection(4, w->objects[0]),
						Intersection(6, w->objects[0])
					};
					Computation comps = w->prepareComputations(xs[0], r, xs);
					Color c = w->refractedColor(comps, 5);

					Color expected(0, 0, 0);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The refracted color at the maximum recursive depth";

					World w = *defaultWorld();
					w.objects[0]->material.transparency = 1.0f;
					w.objects[0]->material.refractiveIndex = 1.5f;
					Ray r(Point4(0, 0, -5), Vector4(0, 0, 1));
					std::vector<Intersection> xs = {
						Intersection(4, w.objects[0]),
						Intersection(6, w.objects[0])
					};
					Computation comps = w.prepareComputations(xs[0], r, xs);
					Color c = w.refractedColor(comps, 0);

					Color expected(0, 0, 0);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The refracted color under total internal reflection";

					World w = *defaultWorld();
					w.objects[0]->material.transparency = 1.0f;
					w.objects[0]->material.refractiveIndex = 1.5f;
					Ray r(Point4(0, 0, sqrt2over2), Vector4(0, 1, 0));
					std::vector<Intersection> xs = {
						Intersection(-sqrt2over2, w.objects[0]),
						Intersection(sqrt2over2, w.objects[0])
					};
					Computation comps = w.prepareComputations(xs[1], r, xs);
					Color c = w.refractedColor(comps, 5);

					Color expected(0, 0, 0);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The refracted color with a refracted ray";

					World w = *defaultWorld();
					IShape* a = w.objects[0];
					a->material.ambient = 1.0f;
					TestPattern pattern;
					a->material.pattern = &pattern;
					IShape* b = w.objects[1];
					b->material.transparency = 1.0f;
					b->material.refractiveIndex = 1.5f;
					Ray r(Point4(0, 0, 0.1f), Vector4(0, 1, 0));
					std::vector<Intersection> xs = {
						Intersection(-0.9899f, a),
						Intersection(-0.4899f, b),
						Intersection(0.4899f, b),
						Intersection(0.9899f, a)
					};
					Computation comps = w.prepareComputations(xs[2], r, xs);
					Color c = w.refractedColor(comps, 5);					
					Color expected(0, 0.99888f, 0.04725f);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - shadeHit() with a transparent material";

					World w = *defaultWorld();
					Plane floor;
					floor.setTransform(translation(0, -1, 0));
					floor.material.transparency = 0.5f;
					floor.material.refractiveIndex = 1.5f;
					w.objects.push_back(&floor);
					Sphere ball;
					ball.setTransform(translation(0, -3.5f, -0.5f));
					ball.material.color = Color(1, 0, 0);
					ball.material.ambient = 0.5f;
					w.objects.push_back(&ball);

					Ray r(Point4(0, 0, -3), Vector4(0, -sqrt2over2, sqrt2over2));
					std::vector<Intersection> xs{
						Intersection(sqrt2, &floor)
					};
					Computation comps = w.prepareComputations(xs[0], r, xs);
					Color c = w.shadeHit(comps, 5, xs);

					Color expected(0.93642f, 0.68642f, 0.68642f);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The Schlick approximation under total internal reflection";

					World w;
					Sphere s = *GlassSphere();
					Ray r(Point4(0, 0, sqrt2over2), Vector4(0, 1, 0));
					std::vector<Intersection> xs = {
						Intersection(-sqrt2over2, &s),
						Intersection(sqrt2over2, &s)
					};
					Computation comps = w.prepareComputations(xs[1], r, xs);
					float reflectance = w.schlick(comps);

					bool result = feq(reflectance, 1.0f);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The Schlick approximation with a perpendicular viewing angle";

					Sphere s = *GlassSphere();
					Ray r(Point4(0, 0, 0), Vector4(0, 1, 0));
					std::vector<Intersection> xs = {
						Intersection(-1, &s),
						Intersection(1, &s)
					};
					World w;
					Computation comps = w.prepareComputations(xs[1], r, xs);
					float reflectance = w.schlick(comps);

					bool result = feq(reflectance, 0.04f);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - The schlick approximation with small angle and n2 > n1";

					World w;
					Sphere s = *GlassSphere();
					Ray r(Point4(0, 0.99f, -2), Vector4(0, 0, 1));
					std::vector<Intersection> xs = {
						Intersection(1.8589f, &s)
					};
					Computation comps = w.prepareComputations(xs[0], r, xs);
					float reflectance = w.schlick(comps);

					bool result = feq(reflectance, 0.48873f);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 11 - shadeHit() with a reflective, transparent material";

					World w = *defaultWorld();
					Ray r(Point4(0, 0, -3), Vector4(0, -sqrt2over2, sqrt2over2));

					Plane floor;
					floor.setTransform(translation(0, -1, 0));
					floor.material.reflective = 0.5f;
					floor.material.transparency = 0.5f;
					floor.material.refractiveIndex = 1.5f;
					w.objects.push_back(&floor);

					Sphere ball;
					ball.setTransform(translation(0, -3.5f, -0.5f));
					ball.material.color = Color(1, 0, 0);
					ball.material.ambient = 0.5f;
					w.objects.push_back(&ball);

					std::vector<Intersection> xs{
						Intersection(sqrt2, &floor)
					};
					Computation comps = w.prepareComputations(xs[0], r, xs);
					Color c = w.shadeHit(comps, 5, xs);

					Color expected(0.93391f, 0.69643f, 0.69243f);

					bool result = c.equals(expected);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

			} // end chapter 11


			//
			// Chapter 14 - Groups
			//

			if (true)
			{

				{
					std::string scenario = "Chapter 14 - Intersecting a ray with an empty group";										

					Group g;
					Ray r(Point4(0, 0, 0), Vector4(0, 0, 1));
					std::vector<Intersection> xs;
					g.localIntersectBy(r, xs);

					bool result = xs.size() == 0;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 14 - Intersecting a ray with a nonempty group";

					Group g;
					Sphere s1;
					Sphere s2;
					s2.setTransform(translation(0, 0, -3));
					Sphere s3;
					s3.setTransform(translation(5, 0, 0));
					g.addChild(s1);
					g.addChild(s2);
					g.addChild(s3);
					Ray r(Point4(0, 0, -5), Vector4(0, 0, 1));
					std::vector<Intersection> xs;
					g.localIntersectBy(r, xs);
										
					std::sort(xs.begin(), xs.end(), intersectionComparer);

					bool result = xs.size() == 4
						&& xs[0].object == &s2
						&& xs[1].object == &s2
						&& xs[2].object == &s1
						&& xs[3].object == &s1;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}
				
				{
					std::string scenario = "Chapter 14 - Intersecting a transformed group";

					Group g;
					g.setTransform(scaling(2, 2, 2));
					Sphere s;
					s.setTransform(translation(5, 0, 0));
					g.addChild(s);
					Ray r(Point4(10, 0, -10), Vector4(0, 0, 1));
					std::vector<Intersection> xs;
					g.intersectBy(r, xs);

					bool result = xs.size() == 2;

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 14 - Converting a point from world to object space";
					
					Group g1;
					g1.setTransform(yRotation4x4(PI / 2.0f));
					Group g2;
					g2.setTransform(scaling(2, 2, 2));
					g1.addChild(g2);
					Sphere s;
					s.setTransform(translation(5, 0, 0));
					g2.addChild(s);

					Point4 p = s.worldToObject(Point4(-2, 0, -10));
					Point4 e(0, 0, -1);

					bool result = p.equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 14 - Converting a normal from object to world space";

					Group g1;
					g1.setTransform(yRotation4x4(PI / 2.0f));
					Group g2;
					g2.setTransform(scaling(1, 2, 3));
					g1.addChild(g2);
					Sphere s;
					s.setTransform(translation(5, 0, 0));
					g2.addChild(s);

					float sqrt3over3 = sqrtf(3) / 3;
					Vector4 n = s.normalToWorld(Vector4(sqrt3over3, sqrt3over3, sqrt3over3));
					Vector4 e(0.2857f, 0.4286f, -0.8571f);
					
					bool result = n.equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}

				{
					std::string scenario = "Chapter 14 - Finding the normal on a child object";

					Group g1;
					g1.setTransform(yRotation4x4(PI / 2.0f));
					Group g2;
					g2.setTransform(scaling(1, 2, 3));
					g1.addChild(g2);
					Sphere s;
					s.setTransform(translation(5, 0, 0));
					g2.addChild(s);

					Vector4 n = s.normalAt(Point4(1.7321f, 1.1547f, -5.5774f));
					Vector4 e(0.2857f, 0.4286f, -0.8571f);

					bool result = n.equals(e);

					std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
					if (result) { numPassed++; }
					else { failedTests.push_back(scenario); }
				}
			} // end chapter 14

			//
			// The End
			//
			TestResults results;
			results.failedTests = failedTests;
			results.numPassed = numPassed;
			return results;
		} // end _tests
	} // end namespace tests
} // end namespace raytracer
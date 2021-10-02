#pragma once

namespace RayTracer
{
	namespace Tests
	{
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
						0.21805, 0.45113, 0.24060, -0.04511,
						-0.80827, -1.45677, -0.44361, 0.52068,
						-0.07895, -0.22368, -0.05263, 0.19737,
						-0.52256, -0.81391, -0.30075, 0.30639
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
					Vector4 e(-8,7,3);

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
			
			{
				{
					std::string scenario = "Chapter 12 - A ray intersects a cube";

					Cube c;

					Ray r1(Point4(5, 0.5, 0), Vector4(-1, 0, 0));
					std::vector<Intersection> xs1 = c.localIntersectBy(r1);

					Ray r2(Point4(-5, 0.5, 0), Vector4(1, 0, 0));
					std::vector<Intersection> xs2 = c.localIntersectBy(r2);

					Ray r3(Point4(0.5, 5, 0), Vector4(0, -1, 0));
					std::vector<Intersection> xs3 = c.localIntersectBy(r3);

					Ray r4(Point4(0.5, -5, 0), Vector4(0, 1, 0));
					std::vector<Intersection> xs4 = c.localIntersectBy(r4);

					Ray r5(Point4(0.5, 0, 5), Vector4(0, 0, -1));
					std::vector<Intersection> xs5 = c.localIntersectBy(r5);

					Ray r6(Point4(0.5, 0, -5), Vector4(0, 0, 1));
					std::vector<Intersection> xs6 = c.localIntersectBy(r6);

					Ray r7(Point4(0, 0.5f, 0), Vector4(0, 0, 1));
					std::vector<Intersection> xs7 = c.localIntersectBy(r7);

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
					Ray r1(Point4(-2, 0, 0), Vector4(0.2673, 0.5345, 0.8018));
					Ray r2(Point4(0, -2, 0), Vector4(0.8018, 0.2673, 0.5345));
					Ray r3(Point4(0, 0, -2), Vector4(0.5345, 0.8018, 0.2673));
					Ray r4(Point4(2, 0, 2), Vector4(0, 0, -1));
					Ray r5(Point4(0, 2, 2), Vector4(0, -1, 0));
					Ray r6(Point4(2, 2, 0), Vector4(-1, 0, 0));

					std::vector<Intersection> xs1 = c.localIntersectBy(r1);
					std::vector<Intersection> xs2 = c.localIntersectBy(r2);
					std::vector<Intersection> xs3 = c.localIntersectBy(r3);
					std::vector<Intersection> xs4 = c.localIntersectBy(r4);
					std::vector<Intersection> xs5 = c.localIntersectBy(r5);
					std::vector<Intersection> xs6 = c.localIntersectBy(r6);

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
					Point4 p1(1, 0.5, -0.8);
					Point4 p2(-1, -0.2, 0.9);
					Point4 p3(-0.4, 1, -0.1);
					Point4 p4(0.3, -1, -0.7);
					Point4 p5(-0.6, 0.3, 1);
					Point4 p6(0.4, 0.4, -1);
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

			/*{
				std::string scenario = "Chapter 12 - ";
				
				bool result = false;

				std::cout << std::endl << (result ? "PASS" : "FAIL") << "\t" << scenario;
				if (result) { numPassed++; }
				else { failedTests.push_back(scenario); }
			}*/




			TestResults results;
			results.failedTests = failedTests;
			results.numPassed = numPassed;
			return results;
		}
	}
}
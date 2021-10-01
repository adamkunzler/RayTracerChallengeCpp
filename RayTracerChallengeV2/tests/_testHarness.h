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
			// Chapter 3
			//

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

				bool result = e ==  a * b;

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
			/*{
				std::string scenario = "Chapter 3 - Multiplying two matrices";
				
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
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
		
		bool RunTests()
		{
			int numPassed(0);
			std::vector<std::string> failedTests;

			std::cout << "Running tests...";

			auto start = std::chrono::high_resolution_clock::now();

			TestResults results = _tests();

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			int totalTests = numPassed + (int)failedTests.size();

			std::cout << "\n\n-------------------------------------------------------------------";
			std::cout << "\n\n" << totalTests << " tests Completed in " << duration.count() << "ms.\n";
			std::cout << "\nPassing Tests: " << numPassed;
			std::cout << "\nFailing Tests: " << failedTests.size() << std::endl;
			
			// write out the failed tests
			for (std::vector<std::string>::const_iterator iter = failedTests.begin(); iter != failedTests.end(); ++iter)
			{
				std::cout << "\t" << *iter << std::endl;
			}

			std::cout << "\n-------------------------------------------------------------------\n\n";

			return failedTests.size() == 0;
		}

		TestResults _tests()
		{
			int numPassed(0);
			std::vector<std::string> failedTests;

			//
			// Chapter 1
			//

			TestResults results;
			results.failedTests = failedTests;
			results.numPassed = numPassed;
			return results;
			
		}
	}
}
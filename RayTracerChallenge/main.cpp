#include <iostream>
#include <vector>

#include "src\Tuple.h"
#include "tests\tupleTests.h"
#include "tests\pointTests.h"
#include "tests\vectorTests.h"
#include "tests\utilsTests.h"

bool RunTests();
void RunRayTracer();

int main()
{
	std::cout << "\nThe Ray Tracer Challenge\n\n\n";
	
	bool result = RunTests();	
	if(result)
	{ 
		RunRayTracer();
	}

	std::cout << "\n\n\n";
	return 0;
}

bool RunTests()
{	
	int numPassed(0);
	std::vector<std::string> failedTests;

	std::cout << "Running tests...\n\n";

	if (RayTracer::Tests::TupleIsPoint()) { numPassed++; } 
	else { failedTests.push_back("TupleIsPoint()"); }

	if (RayTracer::Tests::TupleIsVector()) { numPassed++; }
	else { failedTests.push_back("TupleIsVector()"); }

	if (RayTracer::Tests::CreatePoint()) { numPassed++; }
	else { failedTests.push_back("CreatePoint()"); }

	if (RayTracer::Tests::CreateVector()) { numPassed++; }
	else { failedTests.push_back("CreateVector()"); }
	
	if (RayTracer::Tests::Util_FloatEquals(0.555551, 0.555551)) { numPassed++; }
	else { failedTests.push_back("Util_FloatEquals(0.555551, 0.555551)"); }
	
	if (RayTracer::Tests::Util_FloatEquals(0.555551, 0.555552)) { numPassed++; }
	else { failedTests.push_back("Util_FloatNotEquals(0.555551, 0.555552)"); }

	if (RayTracer::Tests::Util_FloatNotEquals(0.55551, 0.55552)) { numPassed++; }
	else { failedTests.push_back("Util_FloatNotEquals(0.55551, 0.55552)"); }

	RayTracer::Tuple t1(1, 2, 3, 0);
	RayTracer::Tuple t2(1, 2, 3, 0);
	if (RayTracer::Tests::TuplesAreEqual(t1, t2)) { numPassed++; }
	else { failedTests.push_back("TuplesAreEqual()"); }

	RayTracer::Tuple t3(5, 2, 3, 0);
	RayTracer::Tuple t4(1, 2, 3, 0);
	if (RayTracer::Tests::TuplesAreNotEqual(t3,t4)) { numPassed++; }
	else { failedTests.push_back("TuplesAreNotEqual()"); }

	if (RayTracer::Tests::TuplesAreNotEqual(t1, t2)) { numPassed++; }
	else { failedTests.push_back("TuplesAreNotEqual()"); }

	std::cout << "\nTests Completed.\n";
	std::cout << "\nPassing Tests: " << numPassed;
	std::cout << "\nFailing Tests: " << failedTests.size();
	
	return failedTests.size() == 0;
}

void RunRayTracer()
{
	std::cout << "\n\nRunning Ray Tracer...\n\n";

	std::cout << "NOT IMPLEMENTED\n\n";

	return;
}
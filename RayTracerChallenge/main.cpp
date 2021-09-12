#include <iostream>
#include <vector>

#include "src\Tuple.h"
#include "tests\tupleTests.h"
#include "tests\utilsTests.h"

bool RunTests();
void RunRayTracer();

int main()
{
	std::cout << "\nThe Ray Tracer Challenge\n\n\n";
	
	/*RayTracer::Tuple t(1, 2, 3, 0);
	RayTracer::Tuple t2(2, 2, 2, 0);
	RayTracer::Tuple p = RayTracer::Tuple::CreatePoint(1, 2, 3);
	RayTracer::Tuple v = RayTracer::Tuple::CreateVector(1, 2, 3);*/
			
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

	//
	// TUPLE, POINT, VECTOR TESTS
	//
	{
		std::cout << "\nBEGIN Tuple, Vector, Point Tests...\n";

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
		
		if (RayTracer::Tests::TuplesAreEqual()) { numPassed++; }
		else { failedTests.push_back("TuplesAreEqual()"); }
		
		if (RayTracer::Tests::TuplesAreNotEqual()) { numPassed++; }
		else { failedTests.push_back("TuplesAreNotEqual()"); }

		if (RayTracer::Tests::TupleAddition()) { numPassed++; }
		else { failedTests.push_back("TupleAddition()"); }

		if (RayTracer::Tests::PointPlusPoint()) { numPassed++; }
		else { failedTests.push_back("PointPlusPoint()"); }

		if (RayTracer::Tests::VectorPlusVector()) { numPassed++; }
		else { failedTests.push_back("VectorPlusVector()"); }

		if (RayTracer::Tests::VectorPlusPoint()) { numPassed++; }
		else { failedTests.push_back("VectorPlusPoint()"); }

		if (RayTracer::Tests::TupleSubtraction()) { numPassed++; }
		else { failedTests.push_back("TupleSubtraction()"); }

		if (RayTracer::Tests::PointSubtractPoint()) { numPassed++; }
		else { failedTests.push_back("PointSubtractPoint()"); }

		if (RayTracer::Tests::VectorSubtractVector()) { numPassed++; }
		else { failedTests.push_back("VectorSubtractVector()"); }

		if (RayTracer::Tests::PointSubtractVector()) { numPassed++; }
		else { failedTests.push_back("PointSubtractVector()"); }

		if (RayTracer::Tests::VectorSubtractPoint()) { numPassed++; }
		else { failedTests.push_back("VectorSubtractPoint()"); }

		if (RayTracer::Tests::NegatePoint()) { numPassed++; }
		else { failedTests.push_back("NegatePoint()"); }

		if (RayTracer::Tests::NegateVector()) { numPassed++; }
		else { failedTests.push_back("NegateVector()"); }
		

		std::cout << "END Tuple, Vector, Point Tests\n";
	}

	std::cout << "\nTests Completed.\n";
	std::cout << "\nPassing Tests: " << numPassed;
	std::cout << "\nFailing Tests: " << failedTests.size() << std::endl;

	for (std::vector<std::string>::const_iterator iter = failedTests.begin(); iter != failedTests.end(); ++iter)
	{
		std::cout << "\t" << *iter << std::endl;
	}
	
	return failedTests.size() == 0;
}

void RunRayTracer()
{
	std::cout << "\n\nRunning Ray Tracer...\n\n";

	std::cout << "NOT IMPLEMENTED\n\n";

	return;
}
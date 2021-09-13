#include <iostream>
#include <vector>

#include "src\Tuple.h"
#include "tests\tupleTests.h"
#include "tests\utilsTests.h"
#include "tests\colorTests.h"

#include "Exercises\Chapter1\VirtualCannon.h"

bool RunTests();
void RunRayTracer();

int main()
{
	std::cout << "\nThe Ray Tracer Challenge\n\n\n";
	
	//Exercises::Chapter1::FireCannon();

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
	bool runTupleTests = true;
	bool runColorTests = true;

	int numPassed(0);
	std::vector<std::string> failedTests;

	std::cout << "Running tests...\n\n";

	//
	// TUPLE, POINT, VECTOR TESTS
	//	
	if(runTupleTests) 
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

		if (RayTracer::Tests::NegateTuple()) { numPassed++; }
		else { failedTests.push_back("NegateTuple()"); }

		if (RayTracer::Tests::NegateVector()) { numPassed++; }
		else { failedTests.push_back("NegateVector()"); }

		if (RayTracer::Tests::MultiplyTupleByScalar1()) { numPassed++; }
		else { failedTests.push_back("MultiplyTupleByScalar1()"); }

		if (RayTracer::Tests::MultiplyTupleByScalar2()) { numPassed++; }
		else { failedTests.push_back("MultiplyTupleByScalar2()"); }

		if (RayTracer::Tests::MultiplyTupleByFraction1()) { numPassed++; }
		else { failedTests.push_back("MultiplyTupleByFraction1()"); }

		if (RayTracer::Tests::MultiplyTupleByFraction2()) { numPassed++; }
		else { failedTests.push_back("MultiplyTupleByFraction2()"); }
		
		if (RayTracer::Tests::DivideTupleByScalar1()) { numPassed++; }
		else { failedTests.push_back("DivideTupleByScalar1()"); }

		if (RayTracer::Tests::DivideTupleByScalar2()) { numPassed++; }
		else { failedTests.push_back("DivideTupleByScalar2()"); }

		if (RayTracer::Tests::MagnitudeOfVector1()) { numPassed++; }
		else { failedTests.push_back("MagnitudeOfVector1()"); }

		if (RayTracer::Tests::MagnitudeOfVector2()) { numPassed++; }
		else { failedTests.push_back("MagnitudeOfVector2()"); }

		if (RayTracer::Tests::MagnitudeOfVector3()) { numPassed++; }
		else { failedTests.push_back("MagnitudeOfVector3()"); }

		if (RayTracer::Tests::MagnitudeOfVector4()) { numPassed++; }
		else { failedTests.push_back("MagnitudeOfVector4()"); }

		if (RayTracer::Tests::MagnitudeOfVector5()) { numPassed++; }
		else { failedTests.push_back("MagnitudeOfVector5()"); }

		if (RayTracer::Tests::NormalizeVector1()) { numPassed++; }
		else { failedTests.push_back("NormalizeVector1()"); }

		if (RayTracer::Tests::NormalizeVector2()) { numPassed++; }
		else { failedTests.push_back("NormalizeVector2()"); }

		if (RayTracer::Tests::VectorDotProduct()) { numPassed++; }
		else { failedTests.push_back("VectorDotProduct()"); }

		if (RayTracer::Tests::VectorCrossProduct()) { numPassed++; }
		else { failedTests.push_back("VectorCrossProduct()"); }

		std::cout << "END Tuple, Vector, Point Tests\n";
	}
	
	//
	// COLOR TESTS
	//
	if(runColorTests)
	{
		std::cout << "\n\n\nBEGIN Color Tests...\n";

		if (RayTracer::Tests::ColorsAreTuples()) { numPassed++; }
		else { failedTests.push_back("ColorsAreTuples()"); }

		if (RayTracer::Tests::AddColors1()) { numPassed++; }
		else { failedTests.push_back("AddColors1()"); }

		if (RayTracer::Tests::AddColors2()) { numPassed++; }
		else { failedTests.push_back("AddColors2()"); }

		if (RayTracer::Tests::SubtractColors1()) { numPassed++; }
		else { failedTests.push_back("SubtractColors1()"); }

		if (RayTracer::Tests::SubtractColors2()) { numPassed++; }
		else { failedTests.push_back("SubtractColors2()"); }

		if (RayTracer::Tests::ColorMultipliedByScalar1()) { numPassed++; }
		else { failedTests.push_back("ColorMultipliedByScalar1()"); }

		if (RayTracer::Tests::ColorMultipliedByScalar2()) { numPassed++; }
		else { failedTests.push_back("ColorMultipliedByScalar2()"); }

		if (RayTracer::Tests::MultiplyingColors1()) { numPassed++; }
		else { failedTests.push_back("MultiplyingColors1()"); }

		if (RayTracer::Tests::MultiplyingColors2()) { numPassed++; }
		else { failedTests.push_back("MultiplyingColors2()"); }

		std::cout << "END Color Tests\n";
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
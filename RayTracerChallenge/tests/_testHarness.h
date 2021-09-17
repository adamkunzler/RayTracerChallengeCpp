#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../src/Tuple.h"
#include "../src/Point.h"
#include "../src/Vector.h"

#include "tests\tupleTests.h"
#include "tests\vectorTests.h"
#include "tests\pointTests.h"
#include "tests\utilsTests.h"
#include "tests\colorTests.h"
#include "tests\canvasTests.h"
#include "tests\matrixTests.h"

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

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunTupleTests();
		TestResults RunVectorTests();
		TestResults RunPointTests();
		TestResults RunColorTests();
		TestResults RunCanvasTests();
		TestResults RunMatrixTests();

		//------------------------------------------------------------------------------------------------------------------------------------

		bool RunTests()
		{
			//bool runTupleTests = false;
			bool runTupleTests = true;
			//bool runVectorTests = false;
			bool runVectorTests = true;
			//bool runPointTests = false;
			bool runPointTests = true;
			//bool runColorTests = false;
			bool runColorTests = true;
			//bool runCanvasTests = false;
			bool runCanvasTests = true;
			//bool runMatrixTests = false;
			bool runMatrixTests = true;

			int numPassed(0);
			std::vector<std::string> failedTests;

			std::cout << "Running tests...\n\n";

			auto start = std::chrono::high_resolution_clock::now();

			if (runTupleTests)
			{
				RayTracer::Tests::TestResults testResults = RayTracer::Tests::RunTupleTests();
				numPassed += testResults.numPassed;
				failedTests.insert(failedTests.end(), testResults.failedTests.begin(), testResults.failedTests.end());
			}

			if (runVectorTests)
			{
				RayTracer::Tests::TestResults testResults = RayTracer::Tests::RunVectorTests();
				numPassed += testResults.numPassed;
				failedTests.insert(failedTests.end(), testResults.failedTests.begin(), testResults.failedTests.end());
			}

			if (runPointTests)
			{
				RayTracer::Tests::TestResults testResults = RayTracer::Tests::RunPointTests();
				numPassed += testResults.numPassed;
				failedTests.insert(failedTests.end(), testResults.failedTests.begin(), testResults.failedTests.end());
			}

			if (runColorTests)
			{
				RayTracer::Tests::TestResults testResults = RayTracer::Tests::RunColorTests();
				numPassed += testResults.numPassed;
				failedTests.insert(failedTests.end(), testResults.failedTests.begin(), testResults.failedTests.end());
			}

			if (runCanvasTests)
			{
				RayTracer::Tests::TestResults testResults = RayTracer::Tests::RunCanvasTests();
				numPassed += testResults.numPassed;
				failedTests.insert(failedTests.end(), testResults.failedTests.begin(), testResults.failedTests.end());
			}

			if (runMatrixTests)
			{
				RayTracer::Tests::TestResults testResults = RayTracer::Tests::RunMatrixTests();
				numPassed += testResults.numPassed;
				failedTests.insert(failedTests.end(), testResults.failedTests.begin(), testResults.failedTests.end());
			}

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			int totalTests = numPassed + failedTests.size();

			std::cout << "\n\n-------------------------------------------------------------------";
			std::cout << "\n\n" << totalTests << " tests Completed in " << duration.count() << "ms.\n";
			std::cout << "\nPassing Tests: " << numPassed;
			std::cout << "\nFailing Tests: " << failedTests.size() << std::endl;

			// write out the failed tests
			for (std::vector<std::string>::const_iterator iter = failedTests.begin(); iter != failedTests.end(); ++iter)
			{
				std::cout << "\t" << *iter << std::endl;
			}

			return failedTests.size() == 0;
		}

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunTupleTests()
		{			
			std::cout << "\nBEGIN Tuple Tests...\n";

			int numPassed(0);
			std::vector<std::string> failedTests;

			auto start = std::chrono::high_resolution_clock::now();
			
			if (RayTracer::Tests::TupleConstructor_Default()) { numPassed++; }
			else { failedTests.push_back("TupleConstructor_Default"); }

			if (RayTracer::Tests::TupleConstructor_Values()) { numPassed++; }
			else { failedTests.push_back("TupleConstructor_Values"); }

			if (RayTracer::Tests::TupleConstructor_Copy()) { numPassed++; }
			else { failedTests.push_back("TupleConstructor_Copy"); }

			if (RayTracer::Tests::TupleOperator_Assignment_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Assignment_Tuple"); }

			if (RayTracer::Tests::TupleOperator_Assignment_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Assignment_Vector"); }

			if (RayTracer::Tests::TupleOperator_Assignment_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Assignment_Point"); }

			if (RayTracer::Tests::TupleOperator_Equality_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Equality_Tuple"); }

			if (RayTracer::Tests::TupleOperator_Equality_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Equality_Vector"); }

			if (RayTracer::Tests::TupleOperator_Equality_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Equality_Point"); }

			if (RayTracer::Tests::TupleOperator_Inequality_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Inequality_Tuple"); }

			if (RayTracer::Tests::TupleOperator_Inequality_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Inequality_Vector"); }

			if (RayTracer::Tests::TupleOperator_Inequality_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Inequality_Point"); }

			if (RayTracer::Tests::TupleOperator_PlusEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_PlusEquals_Tuple"); }

			if (RayTracer::Tests::TupleOperator_PlusEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_PlusEquals_Vector"); }

			if (RayTracer::Tests::TupleOperator_PlusEquals_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_PlusEquals_Point"); }

			if (RayTracer::Tests::TupleOperator_Plus_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Plus_Tuple"); }

			if (RayTracer::Tests::TupleOperator_Plus_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Plus_Vector"); }

			if (RayTracer::Tests::TupleOperator_Plus_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Plus_Point"); }

			if (RayTracer::Tests::TupleOperator_MinusEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_MinusEquals_Tuple"); }

			if (RayTracer::Tests::TupleOperator_MinusEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_MinusEquals_Vector"); }

			if (RayTracer::Tests::TupleOperator_MinusEquals_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_MinusEquals_Point"); }

			if (RayTracer::Tests::TupleOperator_Minus_Tuple()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Minus_Tuple"); }

			if (RayTracer::Tests::TupleOperator_Minus_Vector()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Minus_Vector"); }

			if (RayTracer::Tests::TupleOperator_Minus_Point()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Minus_Point"); }

			if (RayTracer::Tests::TupleOperator_Negate()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_Negate"); }

			if (RayTracer::Tests::TupleOperator_MultiplyByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_MultiplyByEquals_Scalar"); }

			if (RayTracer::Tests::TupleOperator_MultiplyBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_MultiplyBy_Scalar"); }

			if (RayTracer::Tests::TupleOperator_DividedByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_DividedByEquals_Scalar"); }

			if (RayTracer::Tests::TupleOperator_DividedBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("TupleOperator_DividedBy_Scalar"); }

			if (RayTracer::Tests::TupleIsPoint()) { numPassed++; }
			else { failedTests.push_back("TupleIsPoint"); }

			if (RayTracer::Tests::TupleIsVector()) { numPassed++; }
			else { failedTests.push_back("TupleIsVector"); }

			if (RayTracer::Tests::TupleMagnitude()) { numPassed++; }
			else { failedTests.push_back("TupleMagnitude"); }

			if (RayTracer::Tests::TupleMagnitudeStatic()) { numPassed++; }
			else { failedTests.push_back("TupleMagnitudeStatic"); }

			if (RayTracer::Tests::TupleNormalize()) { numPassed++; }
			else { failedTests.push_back("TupleNormalize"); }

			if (RayTracer::Tests::TupleNormalizeStatic()) { numPassed++; }
			else { failedTests.push_back("TupleNormalizeStatic"); }

			if (RayTracer::Tests::TupleDot()) { numPassed++; }
			else { failedTests.push_back("TupleDot"); }

			if (RayTracer::Tests::TupleDotStatic()) { numPassed++; }
			else { failedTests.push_back("TupleDotStatic"); }

			if (RayTracer::Tests::TupleCross()) { numPassed++; }
			else { failedTests.push_back("TupleCross"); }

			if (RayTracer::Tests::TupleCrossStatic()) { numPassed++; }
			else { failedTests.push_back("TupleCrossStatic"); }

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "END Tuple Tests (" << (failedTests.size() + numPassed) << " tests in " << duration.count() << "ms)";

			TestResults result;
			result.failedTests = failedTests;
			result.numPassed = numPassed;
			return result;
		}

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunVectorTests()
		{
			std::cout << "\n\nBEGIN Vector Tests...\n";

			int numPassed(0);
			std::vector<std::string> failedTests;

			auto start = std::chrono::high_resolution_clock::now();

			if (RayTracer::Tests::VectorConstructor_Default()) { numPassed++; }
			else { failedTests.push_back("VectorConstructor_Default"); }

			if (RayTracer::Tests::VectorConstructor_Values()) { numPassed++; }
			else { failedTests.push_back("VectorConstructor_Values"); }

			if (RayTracer::Tests::VectorConstructor_Copy()) { numPassed++; }
			else { failedTests.push_back("VectorConstructor_Copy"); }

			if (RayTracer::Tests::VectorOperator_Assignment_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Assignment_Tuple"); }

			if (RayTracer::Tests::VectorOperator_Assignment_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Assignment_Vector"); }
			
			if (RayTracer::Tests::VectorOperator_Equality_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Equality_Tuple"); }

			if (RayTracer::Tests::VectorOperator_Equality_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Equality_Vector"); }

			if (RayTracer::Tests::VectorOperator_Inequality_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Inequality_Tuple"); }

			if (RayTracer::Tests::VectorOperator_Inequality_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Inequality_Vector"); }

			if (RayTracer::Tests::VectorOperator_PlusEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_PlusEquals_Tuple"); }

			if (RayTracer::Tests::VectorOperator_PlusEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_PlusEquals_Vector"); }

			if (RayTracer::Tests::VectorOperator_PlusEquals_Point()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_PlusEquals_Point"); }

			if (RayTracer::Tests::VectorOperator_Plus_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Plus_Tuple"); }

			if (RayTracer::Tests::VectorOperator_Plus_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Plus_Vector"); }

			if (RayTracer::Tests::VectorOperator_Plus_Point()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Plus_Point"); }

			if (RayTracer::Tests::VectorOperator_MinusEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_MinusEquals_Tuple"); }

			if (RayTracer::Tests::VectorOperator_MinusEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_MinusEquals_Vector"); }

			if (RayTracer::Tests::VectorOperator_MinusEquals_Point()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_MinusEquals_Point"); }

			if (RayTracer::Tests::VectorOperator_Minus_Tuple()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Minus_Tuple"); }

			if (RayTracer::Tests::VectorOperator_Minus_Vector()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Minus_Vector"); }

			if (RayTracer::Tests::VectorOperator_Minus_Point()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Minus_Point"); }

			if (RayTracer::Tests::VectorOperator_Negate()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_Negate"); }

			if (RayTracer::Tests::VectorOperator_MultiplyByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_MultiplyByEquals_Scalar"); }

			if (RayTracer::Tests::VectorOperator_MultiplyBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_MultiplyBy_Scalar"); }

			if (RayTracer::Tests::VectorOperator_DividedByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_DividedByEquals_Scalar"); }

			if (RayTracer::Tests::VectorOperator_DividedBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("VectorOperator_DividedBy_Scalar"); }			

			if (RayTracer::Tests::VectorMagnitude()) { numPassed++; }
			else { failedTests.push_back("VectorMagnitude"); }

			if (RayTracer::Tests::VectorMagnitudeStatic()) { numPassed++; }
			else { failedTests.push_back("VectorMagnitudeStatic"); }

			if (RayTracer::Tests::VectorNormalize()) { numPassed++; }
			else { failedTests.push_back("VectorNormalize"); }

			if (RayTracer::Tests::VectorNormalizeStatic()) { numPassed++; }
			else { failedTests.push_back("VectorNormalizeStatic"); }

			if (RayTracer::Tests::VectorDot()) { numPassed++; }
			else { failedTests.push_back("VectorDot"); }

			if (RayTracer::Tests::VectorDotStatic()) { numPassed++; }
			else { failedTests.push_back("VectorDotStatic"); }

			if (RayTracer::Tests::VectorCross()) { numPassed++; }
			else { failedTests.push_back("VectorCross"); }

			if (RayTracer::Tests::VectorCrossStatic()) { numPassed++; }
			else { failedTests.push_back("VectorCrossStatic"); }

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "END Vector Tests (" << (failedTests.size() + numPassed) << " tests in " << duration.count() << "ms)";

			TestResults result;
			result.failedTests = failedTests;
			result.numPassed = numPassed;
			return result;
		}

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunPointTests()
		{
			std::cout << "\n\nBEGIN Point Tests...\n";

			int numPassed(0);
			std::vector<std::string> failedTests;

			auto start = std::chrono::high_resolution_clock::now();

			if (RayTracer::Tests::PointConstructor_Default()) { numPassed++; }
			else { failedTests.push_back("PointConstructor_Default"); }

			if (RayTracer::Tests::PointConstructor_Values()) { numPassed++; }
			else { failedTests.push_back("PointConstructor_Values"); }

			if (RayTracer::Tests::PointConstructor_Copy()) { numPassed++; }
			else { failedTests.push_back("PointConstructor_Copy"); }

			if (RayTracer::Tests::PointOperator_Assignment_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Assignment_Tuple"); }			

			if (RayTracer::Tests::PointOperator_Assignment_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Assignment_Point"); }

			if (RayTracer::Tests::PointOperator_Equality_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Equality_Tuple"); }

			if (RayTracer::Tests::PointOperator_Equality_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Equality_Point"); }

			if (RayTracer::Tests::PointOperator_Inequality_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Inequality_Tuple"); }

			if (RayTracer::Tests::PointOperator_Inequality_Vector()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Inequality_Vector"); }

			if (RayTracer::Tests::PointOperator_Inequality_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Inequality_Point"); }

			if (RayTracer::Tests::PointOperator_PlusEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_PlusEquals_Tuple"); }

			if (RayTracer::Tests::PointOperator_PlusEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("PointOperator_PlusEquals_Vector"); }

			if (RayTracer::Tests::PointOperator_PlusEquals_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_PlusEquals_Point"); }

			if (RayTracer::Tests::PointOperator_Plus_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Plus_Tuple"); }

			if (RayTracer::Tests::PointOperator_Plus_Vector()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Plus_Vector"); }

			if (RayTracer::Tests::PointOperator_Plus_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Plus_Point"); }

			if (RayTracer::Tests::PointOperator_MinusEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_MinusEquals_Tuple"); }

			if (RayTracer::Tests::PointOperator_MinusEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("PointOperator_MinusEquals_Vector"); }

			if (RayTracer::Tests::PointOperator_MinusEquals_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_MinusEquals_Point"); }

			if (RayTracer::Tests::PointOperator_Minus_Tuple()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Minus_Tuple"); }

			if (RayTracer::Tests::PointOperator_Minus_Vector()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Minus_Vector"); }

			if (RayTracer::Tests::PointOperator_Minus_Point()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Minus_Point"); }

			if (RayTracer::Tests::PointOperator_Negate()) { numPassed++; }
			else { failedTests.push_back("PointOperator_Negate"); }

			if (RayTracer::Tests::PointOperator_MultiplyByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("PointOperator_MultiplyByEquals_Scalar"); }

			if (RayTracer::Tests::PointOperator_MultiplyBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("PointOperator_MultiplyBy_Scalar"); }

			if (RayTracer::Tests::PointOperator_DividedByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("PointOperator_DividedByEquals_Scalar"); }

			if (RayTracer::Tests::PointOperator_DividedBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("PointOperator_DividedBy_Scalar"); }
			
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "END Point Tests (" << (failedTests.size() + numPassed) << " tests in " << duration.count() << "ms)";

			TestResults result;
			result.failedTests = failedTests;
			result.numPassed = numPassed;
			return result;
		}

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunCanvasTests()
		{
			std::cout << "\n\nBEGIN Canvas Tests...\n";

			int numPassed(0);
			std::vector<std::string> failedTests;

			auto start = std::chrono::high_resolution_clock::now();

			if (RayTracer::Tests::CreateACanvas_Dimensions()) { numPassed++; }
			else { failedTests.push_back("CreateACanvas_Dimensions()"); }

			if (RayTracer::Tests::CreateACanvas_AllBlack()) { numPassed++; }
			else { failedTests.push_back("CreateACanvas_AllBlack()"); }

			if (RayTracer::Tests::CreateACanvas_Big()) { numPassed++; }
			else { failedTests.push_back("CreateACanvas_Big()"); }

			if (RayTracer::Tests::CanvasSetPixelByXY()) { numPassed++; }
			else { failedTests.push_back("CanvasSetPixelByXY()"); }

			if (RayTracer::Tests::CanvasSetPixelByIndex()) { numPassed++; }
			else { failedTests.push_back("CanvasSetPixelByIndex()"); }

			if (RayTracer::Tests::CanvasToPPM_Header()) { numPassed++; }
			else { failedTests.push_back("CanvasToPPM_Header()"); }

			if (RayTracer::Tests::CanvasToPPM_PixelData()) { numPassed++; }
			else { failedTests.push_back("CanvasToPPM_PixelData()"); }

			if (RayTracer::Tests::CanvasToPPM_LongLines()) { numPassed++; }
			else { failedTests.push_back("CanvasToPPM_LongLines()"); }

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "END Canvas Tests (" << (failedTests.size() + numPassed) << " tests in " << duration.count() << "ms)";

			TestResults result;
			result.failedTests = failedTests;
			result.numPassed = numPassed;
			return result;
		}

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunColorTests()
		{
			std::cout << "\n\nBEGIN Color Tests...\n";

			int numPassed(0);
			std::vector<std::string> failedTests;

			auto start = std::chrono::high_resolution_clock::now();

			if (RayTracer::Tests::ColorConstructor_Default()) { numPassed++; }
			else { failedTests.push_back("ColorConstructor_Default"); }

			if (RayTracer::Tests::ColorConstructor_Values()) { numPassed++; }
			else { failedTests.push_back("ColorConstructor_Values"); }

			if (RayTracer::Tests::ColorConstructor_Copy()) { numPassed++; }
			else { failedTests.push_back("ColorConstructor_Copy"); }

			if (RayTracer::Tests::ColorOperator_Assignment()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_Assignment"); }

			if (RayTracer::Tests::ColorOperator_Equality()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_Equality"); }

			if (RayTracer::Tests::ColorOperator_Inequality()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_Inequality"); }

			if (RayTracer::Tests::ColorOperator_PlusEquals()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_PlusEquals"); }

			if (RayTracer::Tests::ColorOperator_Plus()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_Plus"); }

			if (RayTracer::Tests::ColorOperator_MinusEquals()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_MinusEquals"); }

			if (RayTracer::Tests::ColorOperator_Minus()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_Minus"); }
			
			if (RayTracer::Tests::ColorOperator_MultiplyByEquals_Color()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_MultiplyByEquals_Color"); }

			if (RayTracer::Tests::ColorOperator_MultiplyBy_Color()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_MultiplyBy_Color"); }

			if (RayTracer::Tests::ColorOperator_MultiplyByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_MultiplyByEquals_Scalar"); }

			if (RayTracer::Tests::ColorOperator_MultiplyBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_MultiplyBy_Scalar"); }

			if (RayTracer::Tests::ColorOperator_DividedByEquals_Scalar()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_DividedByEquals_Scalar"); }

			if (RayTracer::Tests::ColorOperator_DividedBy_Scalar()) { numPassed++; }
			else { failedTests.push_back("ColorOperator_DividedBy_Scalar"); }

			if (RayTracer::Tests::ColorIsBlack()) { numPassed++; }
			else { failedTests.push_back("ColorIsBlack"); }

			if (RayTracer::Tests::ColorIsWhite()) { numPassed++; }
			else { failedTests.push_back("ColorIsWhite"); }

			if (RayTracer::Tests::ColorFromRGB()) { numPassed++; }
			else { failedTests.push_back("ColorFromRGB"); }

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "END Color Tests (" << (failedTests.size() + numPassed) << " tests in " << duration.count() << "ms)";

			TestResults result;
			result.failedTests = failedTests;
			result.numPassed = numPassed;
			return result;
		}

		//------------------------------------------------------------------------------------------------------------------------------------

		TestResults RunMatrixTests()
		{
			std::cout << "\n\nBEGIN Matrix4x4 Tests...\n";

			int numPassed(0);
			std::vector<std::string> failedTests;

			auto start = std::chrono::high_resolution_clock::now();

			if (RayTracer::Tests::MatrixConstructor_Default()) { numPassed++; }
			else { failedTests.push_back("Matrix4x4Constructor_Default"); }

			if (RayTracer::Tests::MatrixConstructor_Tuple()) { numPassed++; }
			else { failedTests.push_back("MatrixConstructor_Tuple"); }

			if (RayTracer::Tests::MatrixConstructor_Vector()) { numPassed++; }
			else { failedTests.push_back("MatrixConstructor_Vector"); }
			
			if (RayTracer::Tests::MatrixConstructor_ParametersNoValues()) { numPassed++; }
			else { failedTests.push_back("MatrixConstructor_ParametersNoValues"); }

			if (RayTracer::Tests::MatrixConstructor_ParametersWithValues()) { numPassed++; }
			else { failedTests.push_back("MatrixConstructor_ParametersWithValues"); }

			if (RayTracer::Tests::MatrixConstructor_Copy()) { numPassed++; }
			else { failedTests.push_back("Matrix4x4Constructor_Copy"); }

			if (RayTracer::Tests::MatrixOperator_Assignment()) { numPassed++; }
			else { failedTests.push_back("Matrix4x4Operator_Assignment"); }			
			
			if (RayTracer::Tests::MatrixOperator_Equality()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_Equality"); }

			if (RayTracer::Tests::MatrixOperator_Inequality()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_Inequality"); }

			if (RayTracer::Tests::MatrixOperator_InequalityDifferentDimensions()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_InequalityDifferentDimensions"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyByEquals_4x4()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyByEquals_4x4"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyBy_4x4()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyBy_4x4"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyByEquals_3x3()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyByEquals_3x3"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyBy_3x3()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyBy_3x3"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyByIdentity_4x4()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyByIdentity_4x4"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyBy_Tuple()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyBy_Tuple"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyByEquals_Tuple()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyByEquals_Tuple"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyBy_Vector()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyBy_Vector"); }

			if (RayTracer::Tests::MatrixOperator_MultiplyByEquals_Vector()) { numPassed++; }
			else { failedTests.push_back("MatrixOperator_MultiplyByEquals_Vector"); }

			if (RayTracer::Tests::Matrix_Transpose_4x4()) { numPassed++; }
			else { failedTests.push_back("Matrix_Transpose_4x4"); }

			if (RayTracer::Tests::Matrix_Transpose_Identity()) { numPassed++; }
			else { failedTests.push_back("Matrix_Transpose_Identity"); }

			if (RayTracer::Tests::Matrix_Determinant_2x2()) { numPassed++; }
			else { failedTests.push_back("Matrix_Determinant_2x2"); }

			if (RayTracer::Tests::Matrix_Submatrix_3x3()) { numPassed++; }
			else { failedTests.push_back("Matrix_Submatrix_3x3"); }

			if (RayTracer::Tests::Matrix_Submatrix_4x4()) { numPassed++; }
			else { failedTests.push_back("Matrix_Submatrix_4x4"); }

			if (RayTracer::Tests::Matrix_Minor_3x3()) { numPassed++; }
			else { failedTests.push_back("Matrix_Minor_3x3"); }

			if (RayTracer::Tests::Matrix_Cofactor_3x3_1()) { numPassed++; }
			else { failedTests.push_back("Matrix_Cofactor_3x3_1"); }

			if (RayTracer::Tests::Matrix_Cofactor_3x3_2()) { numPassed++; }
			else { failedTests.push_back("Matrix_Cofactor_3x3_2"); }

			if (RayTracer::Tests::Matrix_Determinant_3x3()) { numPassed++; }
			else { failedTests.push_back("Matrix_Determinant_3x3"); }

			if (RayTracer::Tests::Matrix_Determinant_4x4()) { numPassed++; }
			else { failedTests.push_back("Matrix_Determinant_4x4"); }

			if (RayTracer::Tests::Matrix_IsInvertible()) { numPassed++; }
			else { failedTests.push_back("Matrix_IsInvertible"); }

			if (RayTracer::Tests::Matrix_IsNotInvertible()) { numPassed++; }
			else { failedTests.push_back("Matrix_IsNotInvertible"); }
			
			if (RayTracer::Tests::Matrix_Inverse_1()) { numPassed++; }
			else { failedTests.push_back("Matrix_Inverse_1"); }

			if (RayTracer::Tests::Matrix_Inverse_2()) { numPassed++; }
			else { failedTests.push_back("Matrix_Inverse_2"); }

			if (RayTracer::Tests::Matrix_Inverse_3()) { numPassed++; }
			else { failedTests.push_back("Matrix_Inverse_3"); }

			if (RayTracer::Tests::Matrix_Inverse_Proof()) { numPassed++; }
			else { failedTests.push_back("Matrix_Inverse_Proof"); }

			if (RayTracer::Tests::Matrix_Inverse_Test()) { numPassed++; }
			else { failedTests.push_back("Matrix_Inverse_Test"); }

			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "END Matrix4x4 Tests (" << (failedTests.size() + numPassed) << " tests in " << duration.count() << "ms)";

			TestResults result;
			result.failedTests = failedTests;
			result.numPassed = numPassed;
			return result;
		}

		//------------------------------------------------------------------------------------------------------------------------------------



		//------------------------------------------------------------------------------------------------------------------------------------



		//------------------------------------------------------------------------------------------------------------------------------------



		//------------------------------------------------------------------------------------------------------------------------------------



		//------------------------------------------------------------------------------------------------------------------------------------



		//------------------------------------------------------------------------------------------------------------------------------------
	}
}
#pragma once

#include <iostream>
#include <string>
#include "../src/Tuple.h"
#include "../src/Point.h"
#include "../src/Vector.h"

namespace RayTracer
{
	namespace Tests
	{
		bool VectorConstructor_Default()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorConstructor_De\n";

			return result;
		}

		bool VectorConstructor_Values()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorConstructor_Va\n";

			return result;
		}

		bool VectorConstructor_Copy()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorConstructor_Co\n";

			return result;
		}

		bool VectorOperator_Assignment_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Assig\n";

			return result;
		}

		bool VectorOperator_Assignment_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Assig\n";

			return result;
		}

		bool VectorOperator_Assignment_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Assig\n";

			return result;
		}

		bool VectorOperator_Equality_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Equal\n";

			return result;
		}

		bool VectorOperator_Equality_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Equal\n";

			return result;
		}

		bool VectorOperator_Equality_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Equal\n";

			return result;
		}

		bool VectorOperator_Inequality_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Inequ\n";

			return result;
		}

		bool VectorOperator_Inequality_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Inequ\n";

			return result;
		}

		bool VectorOperator_Inequality_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Inequ\n";

			return result;
		}

		bool VectorOperator_PlusEquals_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_PlusE\n";

			return result;
		}

		bool VectorOperator_PlusEquals_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_PlusE\n";

			return result;
		}

		bool VectorOperator_PlusEquals_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_PlusE\n";

			return result;
		}

		bool VectorOperator_Plus_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Plus_\n";

			return result;
		}

		bool VectorOperator_Plus_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Plus_\n";

			return result;
		}

		bool VectorOperator_Plus_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Plus_\n";

			return result;
		}

		bool VectorOperator_MinusEquals_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus\n";

			return result;
		}

		bool VectorOperator_MinusEquals_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus\n";

			return result;
		}

		bool VectorOperator_MinusEquals_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus\n";

			return result;
		}

		bool VectorOperator_Minus_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus\n";

			return result;
		}

		bool VectorOperator_Minus_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus\n";

			return result;
		}

		bool VectorOperator_Minus_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus\n";

			return result;
		}

		bool VectorOperator_Negate()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Negat\n";

			return result;
		}

		bool VectorOperator_MultiplyByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Multi\n";

			return result;
		}

		bool VectorOperator_MultiplyBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Multi\n";

			return result;
		}

		bool VectorOperator_DividedByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Divid\n";

			return result;
		}

		bool VectorOperator_DividedBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Divid\n";

			return result;
		}

		bool VectorIsPoint()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorIsPoint\n";

			return result;
		}

		bool VectorIsVector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorIsVector\n";

			return result;
		}

		bool VectorMagnitude()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorMagnitude\n";

			return result;
		}

		bool VectorMagnitudeStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorMagnitudeStati\n";

			return result;
		}

		bool VectorNormalize()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorNormalize\n";

			return result;
		}

		bool VectorNormalizeStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorNormalizeStati\n";

			return result;
		}

		bool VectorDot()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorDot\n";

			return result;
		}

		bool VectorDotStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorDotStatic\n";

			return result;
		}

		bool VectorCross()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorCross\n";

			return result;
		}

		bool VectorCrossStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorCrossStatic\n";

			return result;
		}


	}
}
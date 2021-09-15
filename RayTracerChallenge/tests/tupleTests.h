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
		bool TupleConstructor_Default()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleConstructor_Default\n";

			return result;
		}

		bool TupleConstructor_Values()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleConstructor_Values\n";

			return result;
		}

		bool TupleConstructor_Copy()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleConstructor_Copy\n";

			return result;
		}

		bool TupleOperator_Assignment_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Assignment_Tuple\n";

			return result;
		}

		bool TupleOperator_Assignment_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Assignment_Vector\n";

			return result;
		}

		bool TupleOperator_Assignment_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Assignment_Point\n";

			return result;
		}

		bool TupleOperator_Equality_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Equality_Tuple\n";

			return result;
		}

		bool TupleOperator_Equality_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Equality_Vector\n";

			return result;
		}

		bool TupleOperator_Equality_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Equality_Point\n";

			return result;
		}

		bool TupleOperator_Inequality_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Inequality_Tuple\n";

			return result;
		}

		bool TupleOperator_Inequality_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Inequality_Vector\n";

			return result;
		}

		bool TupleOperator_Inequality_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Inequality_Point\n";

			return result;
		}

		bool TupleOperator_PlusEquals_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_PlusEquals_Tuple\n";

			return result;
		}

		bool TupleOperator_PlusEquals_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_PlusEquals_Vector\n";

			return result;
		}

		bool TupleOperator_PlusEquals_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_PlusEquals_Point\n";

			return result;
		}

		bool TupleOperator_Plus_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Plus_Tuple\n";

			return result;
		}

		bool TupleOperator_Plus_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Plus_Vector\n";

			return result;
		}

		bool TupleOperator_Plus_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Plus_Point\n";

			return result;
		}

		bool TupleOperator_MinusEquals_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MinusEquals_Tuple\n";

			return result;
		}

		bool TupleOperator_MinusEquals_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MinusEquals_Vector\n";

			return result;
		}

		bool TupleOperator_MinusEquals_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MinusEquals_Point\n";

			return result;
		}

		bool TupleOperator_Minus_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Minus_Tuple\n";

			return result;
		}

		bool TupleOperator_Minus_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Minus_Vector\n";

			return result;
		}

		bool TupleOperator_Minus_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Minus_Point\n";

			return result;
		}

		bool TupleOperator_Negate()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Negate\n";

			return result;
		}

		bool TupleOperator_MultiplyByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MultiplyByEquals_Scalar\n";

			return result;
		}

		bool TupleOperator_MultiplyBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MultiplyBy_Scalar\n";

			return result;
		}

		bool TupleOperator_DividedByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_DividedByEquals_Scalar\n";

			return result;
		}

		bool TupleOperator_DividedBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_DividedBy_Scalar\n";

			return result;
		}

		bool TupleIsPoint()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleIsPoint\n";

			return result;
		}

		bool TupleIsVector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleIsVector\n";

			return result;
		}

		bool TupleMagnitude()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleMagnitude\n";

			return result;
		}

		bool TupleMagnitudeStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleMagnitudeStatic\n";

			return result;
		}

		bool TupleNormalize()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleNormalize\n";

			return result;
		}

		bool TupleNormalizeStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleNormalizeStatic\n";

			return result;
		}

		bool TupleDot()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleDot\n";

			return result;
		}

		bool TupleDotStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleDotStatic\n";

			return result;
		}

		bool TupleCross()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleCross\n";

			return result;
		}

		bool TupleCrossStatic()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleCrossStatic\n";

			return result;
		}


	}

}
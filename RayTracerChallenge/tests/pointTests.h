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
		bool PointConstructor_Default()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointConstructor_Default\n";

			return result;
		}

		bool PointConstructor_Values()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointConstructor_Values\n";

			return result;
		}

		bool PointConstructor_Copy()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointConstructor_Copy\n";

			return result;
		}

		bool PointOperator_Assignment_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Assignment_Tuple\n";

			return result;
		}

		bool PointOperator_Assignment_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Assignment_Vector\n";

			return result;
		}

		bool PointOperator_Assignment_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Assignment_Point\n";

			return result;
		}

		bool PointOperator_Equality_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Equality_Tuple\n";

			return result;
		}

		bool PointOperator_Equality_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Equality_Vector\n";

			return result;
		}

		bool PointOperator_Equality_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Equality_Point\n";

			return result;
		}

		bool PointOperator_Inequality_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Inequality_Tuple\n";

			return result;
		}

		bool PointOperator_Inequality_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Inequality_Vector\n";

			return result;
		}

		bool PointOperator_Inequality_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Inequality_Point\n";

			return result;
		}

		bool PointOperator_PlusEquals_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_PlusEquals_Tuple\n";

			return result;
		}

		bool PointOperator_PlusEquals_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_PlusEquals_Vector\n";

			return result;
		}

		bool PointOperator_PlusEquals_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_PlusEquals_Point\n";

			return result;
		}

		bool PointOperator_Plus_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Plus_Tuple\n";

			return result;
		}

		bool PointOperator_Plus_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Plus_Vector\n";

			return result;
		}

		bool PointOperator_Plus_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Plus_Point\n";

			return result;
		}

		bool PointOperator_MinusEquals_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_MinusEquals_Tuple\n";

			return result;
		}

		bool PointOperator_MinusEquals_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_MinusEquals_Vector\n";

			return result;
		}

		bool PointOperator_MinusEquals_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_MinusEquals_Point\n";

			return result;
		}

		bool PointOperator_Minus_Tuple()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Minus_Tuple\n";

			return result;
		}

		bool PointOperator_Minus_Vector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Minus_Vector\n";

			return result;
		}

		bool PointOperator_Minus_Point()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Minus_Point\n";

			return result;
		}

		bool PointOperator_Negate()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Negate\n";

			return result;
		}

		bool PointOperator_MultiplyByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_MultiplyByEquals_Scalar\n";

			return result;
		}

		bool PointOperator_MultiplyBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_MultiplyBy_Scalar\n";

			return result;
		}

		bool PointOperator_DividedByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_DividedByEquals_Scalar\n";

			return result;
		}

		bool PointOperator_DividedBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_DividedBy_Scalar\n";

			return result;
		}

		bool PointIsPoint()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointIsPoint\n";

			return result;
		}

		bool PointIsVector()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointIsVector\n";

			return result;
		}


	}
}
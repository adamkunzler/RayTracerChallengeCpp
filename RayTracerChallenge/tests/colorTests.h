#pragma once

#include <iostream>
#include <string>
#include "../src/Tuple.h"
#include "../src/Color.h"
#include "../src/Utils.h"

namespace RayTracer
{
	namespace Tests
	{
		bool ColorConstructor_Default()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorConstructor_Default\n";

			return result;
		}

		bool ColorConstructor_Values()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorConstructor_Values\n";

			return result;
		}

		bool ColorConstructor_Copy()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorConstructor_Copy\n";

			return result;
		}

		bool ColorOperator_Assignment()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Assignment\n";

			return result;
		}

		bool ColorOperator_Equality()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Equality\n";

			return result;
		}

		bool ColorOperator_Inequality()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Inequality\n";

			return result;
		}

		bool ColorOperator_PlusEquals()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_PlusEquals\n";

			return result;
		}

		bool ColorOperator_Plus()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Plus\n";

			return result;
		}

		bool ColorOperator_MinusEquals()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MinusEquals\n";

			return result;
		}

		bool ColorOperator_Minus()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Minus\n";

			return result;
		}

		bool ColorOperator_Negate()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Negate\n";

			return result;
		}

		bool ColorOperator_MultiplyByEquals_Color()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyByEquals_Color\n";

			return result;
		}

		bool ColorOperator_MultiplyBy_Color()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyBy_Color\n";

			return result;
		}

		bool ColorOperator_MultiplyByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyByEquals_Scalar\n";

			return result;
		}

		bool ColorOperator_MultiplyBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyBy_Scalar\n";

			return result;
		}

		bool ColorOperator_DividedByEquals_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_DividedByEquals_Scalar\n";

			return result;
		}

		bool ColorOperator_DividedBy_Scalar()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_DividedBy_Scalar\n";

			return result;
		}

		bool ColorIsBlack()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorIsBlack\n";

			return result;
		}

		bool ColorIsWhite()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorIsWhite\n";

			return result;
		}

		bool ColorFromRGB()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorFromRGB\n";

			return result;
		}


	}
}
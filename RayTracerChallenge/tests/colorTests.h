#pragma once


namespace RayTracer
{
	namespace Tests
	{
		bool ColorConstructor_Default()
		{
			Color c;

			bool result = FloatEquals(c.r, 0.0f) && FloatEquals(c.g, 0.0f) && FloatEquals(c.b, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorConstructor_Default\n";

			return result;
		}

		bool ColorConstructor_Values()
		{
			Color c(0.1f, 0.2f, 0.3f);

			bool result = FloatEquals(c.r, 0.1f) && FloatEquals(c.g, 0.2f) && FloatEquals(c.b, 0.3f);
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorConstructor_Values\n";

			return result;
		}

		bool ColorConstructor_Copy()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c(c1);

			bool result = FloatEquals(c.r, 0.1f) && FloatEquals(c.g, 0.2f) && FloatEquals(c.b, 0.3f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorConstructor_Copy\n";

			return result;
		}

		bool ColorOperator_Assignment()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c = c1;

			bool result = FloatEquals(c.r, 0.1f) && FloatEquals(c.g, 0.2f) && FloatEquals(c.b, 0.3f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Assignment\n";

			return result;
		}

		bool ColorOperator_Equality()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c2(0.1f, 0.2f, 0.3f);

			bool result = c1 == c2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Equality\n";

			return result;
		}

		bool ColorOperator_Inequality()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c2(0.4f, 0.5f, 0.6f);

			bool result = c1 != c2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Inequality\n";

			return result;
		}

		bool ColorOperator_PlusEquals()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c2(0.4f, 0.5f, 0.6f);

			c1 += c2;

			bool result = FloatEquals(c1.r, 0.5f) && FloatEquals(c1.g, 0.7f) && FloatEquals(c1.b, 0.9f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_PlusEquals\n";

			return result;
		}

		bool ColorOperator_Plus()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c2(0.4f, 0.5f, 0.6f);
			
			Color c3 = c1 + c2;

			bool result = FloatEquals(c3.r, 0.5f) && FloatEquals(c3.g, 0.7f) && FloatEquals(c3.b, 0.9f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Plus\n";

			return result;
		}

		bool ColorOperator_MinusEquals()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c2(0.4f, 0.5f, 0.6f);

			c2 -= c1;

			bool result = FloatEquals(c2.r, 0.3f) && FloatEquals(c2.g, 0.3f) && FloatEquals(c2.b, 0.3f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MinusEquals\n";

			return result;
		}

		bool ColorOperator_Minus()
		{
			Color c1(0.1f, 0.2f, 0.3f);
			Color c2(0.4f, 0.5f, 0.6f);

			Color c3 = c2 - c1;

			bool result = FloatEquals(c3.r, 0.3f) && FloatEquals(c3.g, 0.3f) && FloatEquals(c3.b, 0.3f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_Minus\n";

			return result;
		}
		
		bool ColorOperator_MultiplyByEquals_Color()
		{
			Color c1(1.0f, 0.2f, 0.4f);
			Color c2(0.9f, 1.0f, 0.1f);
			
			c1 *= c2;

			bool result = FloatEquals(c1.r, 0.9f) && FloatEquals(c1.g, 0.2f) && FloatEquals(c1.b, 0.04f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyByEquals_Color\n";

			return result;
		}

		bool ColorOperator_MultiplyBy_Color()
		{
			Color c2(1.0f, 0.2f, 0.4f);
			Color c3(0.9f, 1.0f, 0.1f);

			Color c1 = c2 * c3;

			bool result = FloatEquals(c1.r, 0.9f) && FloatEquals(c1.g, 0.2f) && FloatEquals(c1.b, 0.04f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyBy_Color\n";

			return result;
		}

		bool ColorOperator_MultiplyByEquals_Scalar()
		{
			Color c1(0.2f, 0.4f, 0.6f);
			float s = 2;

			c1 *= s;

			bool result = FloatEquals(c1.r, 0.4f) && FloatEquals(c1.g, 0.8f) && FloatEquals(c1.b, 1.2f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyByEquals_Scalar\n";

			return result;
		}

		bool ColorOperator_MultiplyBy_Scalar()
		{
			Color c(0.2f, 0.4f, 0.6f);
			float s = 2;

			Color c1 = c * s;

			bool result = FloatEquals(c1.r, 0.4f) && FloatEquals(c1.g, 0.8f) && FloatEquals(c1.b, 1.2f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_MultiplyBy_Scalar\n";

			return result;
		}

		bool ColorOperator_DividedByEquals_Scalar()
		{
			Color c1(0.2f, 0.4f, 0.6f);
			float s = 2;

			c1 /= s;

			bool result = FloatEquals(c1.r, 0.1f) && FloatEquals(c1.g, 0.2f) && FloatEquals(c1.b, 0.3f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_DividedByEquals_Scalar\n";

			return result;
		}

		bool ColorOperator_DividedBy_Scalar()
		{
			Color c(0.2f, 0.4f, 0.6f);
			float s = 2;

			Color c1 = c / s;

			bool result = FloatEquals(c1.r, 0.1f) && FloatEquals(c1.g, 0.2f) && FloatEquals(c1.b, 0.3f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorOperator_DividedBy_Scalar\n";

			return result;
		}

		bool ColorIsBlack()
		{
			Color c(0.0f);

			bool result = c.isBlack();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorIsBlack\n";

			return result;
		}

		bool ColorIsWhite()
		{
			Color c(1.0f);
			bool result = c.isWhite();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorIsWhite\n";

			return result;
		}

		bool ColorFromRGB()
		{
			Color c = Color::fromRGB(128, 64, 192);

			bool result = FloatEquals(c.r, 0.5f) && FloatEquals(c.g, 0.25f) && FloatEquals(c.b, 0.75f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t ColorFromRGB\n";

			return result;
		}


	}
}
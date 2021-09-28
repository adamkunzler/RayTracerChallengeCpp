#pragma once


namespace RayTracer
{
	namespace Tests
	{
		bool PointConstructor_Default()
		{
			Point t;

			bool result = FloatEquals(t.x, 0.0f) && FloatEquals(t.y, 0.0f) && FloatEquals(t.z, 0.0f) && t.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointConstructor_Default\n";

			return result;
		}

		bool PointConstructor_Values()
		{
			Point t(1.0f, 2.0f, 3.0f);

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isPoint();


			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointConstructor_Values\n";

			return result;
		}

		bool PointConstructor_Copy()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Point t(t1);

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointConstructor_Copy\n";

			return result;
		}

		bool PointOperator_Assignment_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t = t1;

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Assignment_Tuple\n";

			return result;
		}		

		bool PointOperator_Assignment_Point()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Point t = t1;

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Assignment_Point\n";

			return result;
		}

		bool PointOperator_Equality_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Equality_Tuple\n";

			return result;
		}
		
		bool PointOperator_Equality_Point()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Equality_Point\n";

			return result;
		}

		bool PointOperator_Inequality_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t2(4.0f, 5.0f, 6.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Inequality_Tuple\n";

			return result;
		}

		bool PointOperator_Inequality_Vector()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Point t2(4.0f, 5.0f, 6.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Inequality_Vector\n";

			return result;
		}

		bool PointOperator_Inequality_Point()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Point t2(4.0f, 5.0f, 6.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Inequality_Point\n";

			return result;
		}
				
		bool PointOperator_Plus_Tuple()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Tuple t2(2.0f, 3.0f, 4.0f, 1.0f);

			Point t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Plus_Tuple\n";

			return result;
		}

		bool PointOperator_Plus_Vector()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Vector t2(2.0f, 3.0f, 4.0f);

			Point t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Plus_Vector\n";

			return result;
		}

		bool PointOperator_Plus_Point()
		{
			Point t1(1.0f, 2.0f, 3.0f);
			Point t2(2.0f, 3.0f, 4.0f);

			Point t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Plus_Point\n";

			return result;
		}
		
		bool PointOperator_Minus_Tuple()
		{
			Point t1(2.0f, 3.0f, 4.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 0.0f);

			Point t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Minus_Tuple\n";

			return result;
		}

		bool PointOperator_Minus_Vector()
		{
			Point t1(2.0f, 3.0f, 4.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			Point t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Minus_Vector\n";

			return result;
		}

		bool PointOperator_Minus_Point()
		{
			Point t1(2.0f, 3.0f, 4.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			Point t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Minus_Point\n";

			return result;
		}

		bool PointOperator_Negate()
		{
			Point t1(2.0f, 3.0f, 4.0f);
			Point t2 = -t1;

			bool result = FloatEquals(t2.x, -2.0f)
				&& FloatEquals(t2.y, -3.0f)
				&& FloatEquals(t2.z, -4.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_Negate\n";

			return result;
		}
		
		bool PointOperator_MultiplyBy_Scalar()
		{
			Point t1(2.0f, 3.0f, 4.0f);
			float s = 2.0f;

			Point t2 = t1 * s;

			bool result = FloatEquals(t2.x, 4.0f)
				&& FloatEquals(t2.y, 6.0f)
				&& FloatEquals(t2.z, 8.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_MultiplyBy_Scalar\n";

			return result;
		}
		
		bool PointOperator_DividedBy_Scalar()
		{
			Point t1(2.0f, 3.0f, 4.0f);
			float s = 2.0f;

			Point t2 = t1 / s;

			bool result = FloatEquals(t2.x, 1.0f)
				&& FloatEquals(t2.y, 1.5f)
				&& FloatEquals(t2.z, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t PointOperator_DividedBy_Scalar\n";

			return result;
		}		
	}
}
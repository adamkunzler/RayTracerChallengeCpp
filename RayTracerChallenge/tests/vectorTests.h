#pragma once

namespace RayTracer
{
	namespace Tests
	{

		bool VectorConstructor_Default()
		{
			Vector t;

			bool result = FloatEquals(t.x, 0.0f) && FloatEquals(t.y, 0.0f) && FloatEquals(t.z, 0.0f) && t.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorConstructor_Default\n";

			return result;
		}

		bool VectorConstructor_Values()
		{
			Vector t(1.0f, 2.0f, 3.0f);

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorConstructor_Values\n";

			return result;
		}

		bool VectorConstructor_Copy()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Vector t(t1);

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isVector();


			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorConstructor_Copy\n";

			return result;
		}

		bool VectorOperator_Assignment_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 0.0f);
			Vector t = t1;

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) &&t.isVector();


			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Assignment_Tuple\n";

			return result;
		}

		bool VectorOperator_Assignment_Vector()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Vector t = t1;

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && t.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Assignment_Vector\n";

			return result;
		}
		
		bool VectorOperator_Equality_Tuple()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 0.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Equality_Tuple\n";

			return result;
		}

		bool VectorOperator_Equality_Vector()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Equality_Vector\n";

			return result;
		}		

		bool VectorOperator_Inequality_Tuple()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Tuple t2(3.0f, 4.0f, 5.0f, 0.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Inequality_Tuple\n";

			return result;
		}

		bool VectorOperator_Inequality_Vector()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Vector t2(3.0f, 4.0f, 5.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Inequality_Vector\n";

			return result;
		}
		
		bool VectorOperator_PlusEquals_Tuple()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Tuple t2(2.0f, 3.0f, 4.0f, 0.0f);

			t1 += t2;

			bool result = FloatEquals(t1.x, 3.0f)
				&& FloatEquals(t1.y, 5.0f)
				&& FloatEquals(t1.z, 7.0f)
				&& t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_PlusEquals_Tuple\n";

			return result;
		}

		bool VectorOperator_PlusEquals_Vector()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Vector t2(2.0f, 3.0f, 4.0f);

			t1 += t2;

			bool result = FloatEquals(t1.x, 3.0f)
				&& FloatEquals(t1.y, 5.0f)
				&& FloatEquals(t1.z, 7.0f)
				&& t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_PlusEquals_Vector\n";

			return result;
		}

		bool VectorOperator_PlusEquals_Point()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Point t2(2.0f, 3.0f, 4.0f);

			t1 += t2;

			bool result = FloatEquals(t1.x, 3.0f)
				&& FloatEquals(t1.y, 5.0f)
				&& FloatEquals(t1.z, 7.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_PlusEquals_Point\n";

			return result;
		}

		bool VectorOperator_Plus_Tuple()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Tuple t2(2.0f, 3.0f, 4.0f, 0.0f);

			Vector t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f)
				&& t3.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Plus_Tuple\n";

			return result;
		}

		bool VectorOperator_Plus_Vector()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Vector t2(2.0f, 3.0f, 4.0f);

			Vector t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f)
				&& t3.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Plus_Vector\n";

			return result;
		}

		bool VectorOperator_Plus_Point()
		{
			Vector t1(1.0f, 2.0f, 3.0f);
			Point t2(2.0f, 3.0f, 4.0f);

			Vector t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Plus_Point\n";

			return result;
		}

		bool VectorOperator_MinusEquals_Tuple()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 0.0f);

			t1 -= t2;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.0f)
				&& FloatEquals(t1.z, 1.0f)
				&& t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_MinusEquals_Tuple\n";

			return result;
		}

		bool VectorOperator_MinusEquals_Vector()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			t1 -= t2;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.0f)
				&& FloatEquals(t1.z, 1.0f)
				&& t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_MinusEquals_Vector\n";

			return result;
		}

		bool VectorOperator_MinusEquals_Point()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			t1 -= t2;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.0f)
				&& FloatEquals(t1.z, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_MinusEquals_Point\n";

			return result;
		}

		bool VectorOperator_Minus_Tuple()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 0.0f);

			Vector t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f)
				&& t3.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus_Tuple\n";

			return result;
		}

		bool VectorOperator_Minus_Vector()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			Vector t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f)
				&& t3.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus_Vector\n";

			return result;
		}

		bool VectorOperator_Minus_Point()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			Vector t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Minus_Point\n";

			return result;
		}

		bool VectorOperator_Negate()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			Vector t2 = -t1;

			bool result = FloatEquals(t2.x, -2.0f)
				&& FloatEquals(t2.y, -3.0f)
				&& FloatEquals(t2.z, -4.0f)
				&& t2.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_Negate\n";

			return result;
		}

		bool VectorOperator_MultiplyByEquals_Scalar()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			float s = 2.0f;

			t1 *= s;

			bool result = FloatEquals(t1.x, 4.0f)
				&& FloatEquals(t1.y, 6.0f)
				&& FloatEquals(t1.z, 8.0f)
				&& t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_MultiplyByEquals_Scalar\n";

			return result;
		}

		bool VectorOperator_MultiplyBy_Scalar()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			float s = 2.0f;

			Vector t2 = t1 * s;

			bool result = FloatEquals(t2.x, 4.0f)
				&& FloatEquals(t2.y, 6.0f)
				&& FloatEquals(t2.z, 8.0f)
				&& t2.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_MultiplyBy_Scalar\n";

			return result;
		}

		bool VectorOperator_DividedByEquals_Scalar()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			float s = 2.0f;

			t1 /= s;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.5f)
				&& FloatEquals(t1.z, 2.0f)
				&& t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_DividedByEquals_Scalar\n";

			return result;
		}

		bool VectorOperator_DividedBy_Scalar()
		{
			Vector t1(2.0f, 3.0f, 4.0f);
			float s = 2.0f;

			Vector t2 = t1 / s;

			bool result = FloatEquals(t2.x, 1.0f)
				&& FloatEquals(t2.y, 1.5f)
				&& FloatEquals(t2.z, 2.0f)
				&& t2.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorOperator_DividedBy_Scalar\n";

			return result;
		}
		
		bool VectorMagnitude()
		{
			Vector t(1.0f, 2.0f, 3.0f);

			bool result = FloatEquals(t.magnitude(), std::sqrt(14.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorMagnitude\n";

			return result;
		}

		bool VectorMagnitudeStatic()
		{
			Vector t(-1.0f, -2.0f, -3.0f);

			bool result = FloatEquals(Tuple::magnitude(t), std::sqrt(14.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorMagnitudeStatic\n";

			return result;
		}

		bool VectorNormalize()
		{
			Vector p(4.0f, 0.0f, 0.0f);
			p = p.normalize();
			float m = p.magnitude();

			bool result = FloatEquals(p.x, 1.0f)
				&& FloatEquals(p.y, 0.0f)
				&& FloatEquals(p.z, 0.0f)
				&& FloatEquals(p.w, 0.0f)
				&& p.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorNormalize\n";

			return result;
		}

		bool VectorNormalizeStatic()
		{
			Vector p(1.0f, 2.0f, 3.0f);
			p = Vector::normalize(p);
			float m = p.magnitude();

			bool result = FloatEquals(p.x, 0.26726f)
				&& FloatEquals(p.y, 0.53452f)
				&& FloatEquals(p.z, 0.80178f)
				&& p.isVector()
				&& FloatEquals(m, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorNormalizeStatic\n";

			return result;
		}

		bool VectorDot()
		{
			Vector a(1.0f, 2.0f, 3.0f);
			Vector b(2.0f, 3.0f, 4.0f);

			float dot = a.dot(b);

			bool result = FloatEquals(dot, 20.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorDot\n";

			return result;
		}

		bool VectorDotStatic()
		{
			Vector a(1.0f, 2.0f, 3.0f);
			Vector b(2.0f, 3.0f, 4.0f);

			float dot = Tuple::dot(a, b);

			bool result = FloatEquals(dot, 20.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorDotStatic\n";

			return result;
		}

		bool VectorCross()
		{
			Vector a(1.0f, 2.0f, 3.0f);
			Vector b(2.0f, 3.0f, 4.0f);

			Vector c = a.cross(b);
			Vector d = b.cross(a);

			Vector cp1(-1.0f, 2.0f, -1.0f);
			Vector cp2(1.0f, -2.0f, 1.0f);

			bool result = (c == cp1 && d == cp2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorCross\n";

			return result;
		}

		bool VectorCrossStatic()
		{
			Vector a(1.0f, 2.0f, 3.0f);
			Vector b(2.0f, 3.0f, 4.0f);

			Vector c = Vector::cross(a, b);
			Vector d = Vector::cross(b, a);

			Vector cp1(-1.0f, 2.0f, -1.0f);
			Vector cp2(1.0f, -2.0f, 1.0f);

			bool result = (c == cp1 && d == cp2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t VectorCrossStatic\n";

			return result;
		}
	}
}
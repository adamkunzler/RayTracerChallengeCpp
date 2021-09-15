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
			Tuple t;

			bool result = FloatEquals(t.x, 0.0f) && FloatEquals(t.y, 0.0f) && FloatEquals(t.z, 0.0f) && FloatEquals(t.w, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleConstructor_Default\n";

			return result;
		}

		bool TupleConstructor_Values()
		{
			Tuple t(1.0f, 2.0f, 3.0f, 1.0f);

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && FloatEquals(t.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleConstructor_Values\n";

			return result;
		}

		bool TupleConstructor_Copy()
		{			
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple t(t1);

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && FloatEquals(t.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleConstructor_Copy\n";

			return result;
		}

		bool TupleOperator_Assignment_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple t = t1;

			bool result = FloatEquals(t.x, 1.0f) && FloatEquals(t.y, 2.0f) && FloatEquals(t.z, 3.0f) && FloatEquals(t.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Assignment_Tuple\n";

			return result;
		}

		bool TupleOperator_Assignment_Vector()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Vector v = t1;

			bool result = FloatEquals(v.x, 1.0f) 
					   && FloatEquals(v.y, 2.0f) 
				       && FloatEquals(v.z, 3.0f) 
				       && FloatEquals(v.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Assignment_Vector\n";

			return result;
		}

		bool TupleOperator_Assignment_Point()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point v = t1;

			bool result = FloatEquals(v.x, 1.0f)
				&& FloatEquals(v.y, 2.0f)
				&& FloatEquals(v.z, 3.0f)
				&& FloatEquals(v.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Assignment_Point\n";

			return result;
		}

		bool TupleOperator_Equality_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 1.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Equality_Tuple\n";

			return result;
		}

		bool TupleOperator_Equality_Vector()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 0.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Equality_Vector\n";

			return result;
		}

		bool TupleOperator_Equality_Point()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			bool result = t1 == t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Equality_Point\n";

			return result;
		}

		bool TupleOperator_Inequality_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple t2(4.0f, 5.0f, 6.0f, 0.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Inequality_Tuple\n";

			return result;
		}

		bool TupleOperator_Inequality_Vector()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Vector t2(4.0f, 5.0f, 6.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Inequality_Vector\n";

			return result;
		}

		bool TupleOperator_Inequality_Point()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t2(4.0f, 5.0f, 6.0f);

			bool result = t1 != t2;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Inequality_Point\n";

			return result;
		}

		bool TupleOperator_PlusEquals_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple t2(2.0f, 3.0f, 4.0f, 1.0f);

			t1 += t2;

			bool result = FloatEquals(t1.x, 3.0f) 
					   && FloatEquals(t1.y, 5.0f) 
					   && FloatEquals(t1.z, 7.0f) 
					   && FloatEquals(t1.w, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_PlusEquals_Tuple\n";

			return result;
		}

		bool TupleOperator_PlusEquals_Vector()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Vector t2(2.0f, 3.0f, 4.0f);

			t1 += t2;

			bool result = FloatEquals(t1.x, 3.0f)
				&& FloatEquals(t1.y, 5.0f)
				&& FloatEquals(t1.z, 7.0f)
				&& FloatEquals(t1.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_PlusEquals_Vector\n";

			return result;
		}

		bool TupleOperator_PlusEquals_Point()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t2(2.0f, 3.0f, 4.0f);

			t1 += t2;

			bool result = FloatEquals(t1.x, 3.0f)
				&& FloatEquals(t1.y, 5.0f)
				&& FloatEquals(t1.z, 7.0f)
				&& FloatEquals(t1.w, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_PlusEquals_Point\n";

			return result;
		}

		bool TupleOperator_Plus_Tuple()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple t2(2.0f, 3.0f, 4.0f, 1.0f);

			Tuple t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f)
				&& FloatEquals(t3.w, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Plus_Tuple\n";

			return result;
		}

		bool TupleOperator_Plus_Vector()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Vector t2(2.0f, 3.0f, 4.0f);

			Tuple t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f)
				&& FloatEquals(t3.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Plus_Vector\n";

			return result;
		}

		bool TupleOperator_Plus_Point()
		{
			Tuple t1(1.0f, 2.0f, 3.0f, 1.0f);
			Point t2(2.0f, 3.0f, 4.0f);

			Tuple t3 = t1 + t2;

			bool result = FloatEquals(t3.x, 3.0f)
				&& FloatEquals(t3.y, 5.0f)
				&& FloatEquals(t3.z, 7.0f)
				&& FloatEquals(t3.w, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Plus_Point\n";

			return result;
		}

		bool TupleOperator_MinusEquals_Tuple()
		{			
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 1.0f);

			t1 -= t2;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.0f)
				&& FloatEquals(t1.z, 1.0f)
				&& FloatEquals(t1.w, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MinusEquals_Tuple\n";

			return result;
		}

		bool TupleOperator_MinusEquals_Vector()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			t1 -= t2;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.0f)
				&& FloatEquals(t1.z, 1.0f)
				&& FloatEquals(t1.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MinusEquals_Vector\n";

			return result;
		}

		bool TupleOperator_MinusEquals_Point()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			t1 -= t2;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.0f)
				&& FloatEquals(t1.z, 1.0f)
				&& FloatEquals(t1.w, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MinusEquals_Point\n";

			return result;
		}

		bool TupleOperator_Minus_Tuple()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Tuple t2(1.0f, 2.0f, 3.0f, 1.0f);

			Tuple t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f)
				&& FloatEquals(t3.w, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Minus_Tuple\n";

			return result;
		}

		bool TupleOperator_Minus_Vector()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Vector t2(1.0f, 2.0f, 3.0f);

			Tuple t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f)
				&& FloatEquals(t3.w, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Minus_Vector\n";

			return result;
		}

		bool TupleOperator_Minus_Point()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Point t2(1.0f, 2.0f, 3.0f);

			Tuple t3 = t1 - t2;

			bool result = FloatEquals(t3.x, 1.0f)
				&& FloatEquals(t3.y, 1.0f)
				&& FloatEquals(t3.z, 1.0f)
				&& FloatEquals(t3.w, 0.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Minus_Point\n";

			return result;
		}

		bool TupleOperator_Negate()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			Tuple t2 = -t1;

			bool result = FloatEquals(t2.x, -2.0f)
				&& FloatEquals(t2.y, -3.0f)
				&& FloatEquals(t2.z, -4.0f)
				&& FloatEquals(t2.w, -1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_Negate\n";

			return result;
		}

		bool TupleOperator_MultiplyByEquals_Scalar()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			float s = 2.0f;

			t1 *= s;

			bool result = FloatEquals(t1.x, 4.0f)
				&& FloatEquals(t1.y, 6.0f)
				&& FloatEquals(t1.z, 8.0f)
				&& FloatEquals(t1.w, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MultiplyByEquals_Scalar\n";

			return result;
		}

		bool TupleOperator_MultiplyBy_Scalar()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			float s = 2.0f;

			Tuple t2 = t1 * s;

			bool result = FloatEquals(t2.x, 4.0f)
				&& FloatEquals(t2.y, 6.0f)
				&& FloatEquals(t2.z, 8.0f)
				&& FloatEquals(t2.w, 2.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_MultiplyBy_Scalar\n";

			return result;
		}

		bool TupleOperator_DividedByEquals_Scalar()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			float s = 2.0f;

			t1 /= s;

			bool result = FloatEquals(t1.x, 1.0f)
				&& FloatEquals(t1.y, 1.5f)
				&& FloatEquals(t1.z, 2.0f)
				&& FloatEquals(t1.w, 0.5f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_DividedByEquals_Scalar\n";

			return result;
		}

		bool TupleOperator_DividedBy_Scalar()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			float s = 2.0f;

			Tuple t2  = t1 / s;

			bool result = FloatEquals(t2.x, 1.0f)
				&& FloatEquals(t2.y, 1.5f)
				&& FloatEquals(t2.z, 2.0f)
				&& FloatEquals(t2.w, 0.5f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleOperator_DividedBy_Scalar\n";

			return result;
		}

		bool TupleIsPoint()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 1.0f);
			bool result = t1.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleIsPoint\n";

			return result;
		}

		bool TupleIsVector()
		{
			Tuple t1(2.0f, 3.0f, 4.0f, 0.0f);
			
			bool result = t1.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleIsVector\n";

			return result;
		}

		bool TupleMagnitude()
		{
			Tuple t(1.0f, 2.0f, 3.0f, 0.0f);

			bool result = FloatEquals(t.magnitude(), std::sqrt(14.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleMagnitude\n";

			return result;
		}

		bool TupleMagnitudeStatic()
		{
			Tuple t(-1.0f, -2.0f, -3.0f, 0.0f);

			bool result = FloatEquals(Tuple::magnitude(t), std::sqrt(14.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleMagnitudeStatic\n";

			return result;
		}

		bool TupleNormalize()
		{
			Tuple p(4.0f, 0.0f, 0.0f, 0.0f);
			p = p.normalize();
			float m = p.magnitude();

			bool result = FloatEquals(p.x, 1.0f)
						&& FloatEquals(p.y, 0.0f)
						&& FloatEquals(p.z, 0.0f)
						&& FloatEquals(p.w, 0.0f)
						&& FloatEquals(m, 1.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleNormalize\n";

			return result;
		}

		bool TupleNormalizeStatic()
		{
			Tuple p(1.0f, 2.0f, 3.0f, 0.0f);
			p = Tuple::normalize(p);
			float m = p.magnitude();

			bool result = FloatEquals(p.x, 0.26726f)
				&& FloatEquals(p.y, 0.53452f)
				&& FloatEquals(p.z, 0.80178f)
				&& FloatEquals(p.w, 0.0f)
				&& FloatEquals(m, 1.0f);;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleNormalizeStatic\n";

			return result;
		}

		bool TupleDot()
		{
			Tuple a(1.0f, 2.0f, 3.0f, 0.0f);
			Tuple b(2.0f, 3.0f, 4.0f, 0.0f);

			float dot = a.dot(b);

			bool result = FloatEquals(dot, 20.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleDot\n";

			return result;
		}

		bool TupleDotStatic()
		{
			Tuple a(1.0f, 2.0f, 3.0f, 0.0f);
			Tuple b(2.0f, 3.0f, 4.0f, 0.0f);

			float dot = Tuple::dot(a, b);

			bool result = FloatEquals(dot, 20.0f);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleDotStatic\n";

			return result;
		}

		bool TupleCross()
		{
			Tuple a(1.0f, 2.0f, 3.0f, 0.0f);
			Tuple b(2.0f, 3.0f, 4.0f, 0.0f);

			Tuple c = a.cross(b);
			Tuple d = b.cross(a);

			Tuple cp1(-1.0f, 2.0f, -1.0f, 0.0f);
			Tuple cp2(1.0f, -2.0f, 1.0f, 0.0f);

			bool result = (c == cp1 && d == cp2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleCross\n";

			return result;
		}

		bool TupleCrossStatic()
		{
			Tuple a(1.0f, 2.0f, 3.0f, 0.0f);
			Tuple b(2.0f, 3.0f, 4.0f, 0.0f);

			Tuple c = Tuple::cross(a, b);
			Tuple d = Tuple::cross(b, a);

			Tuple cp1(-1.0f, 2.0f, -1.0f, 0.0f);
			Tuple cp2(1.0f, -2.0f, 1.0f, 0.0f);

			bool result = (c == cp1 && d == cp2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t TupleCrossStatic\n";

			return result;
		}


	}

}
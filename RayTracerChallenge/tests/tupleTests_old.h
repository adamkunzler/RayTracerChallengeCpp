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
		bool TupleIsPoint()
		{
			Tuple t(4.3f, -4.2f, 3.1f, 1.0f);
			bool result = t.isPoint();
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTupleIsPoint()\n";			

			return result;
		}

		bool TupleIsVector()
		{
			Tuple t(4.3f, -4.2f, 3.1f, 0.0f);
			bool result = t.isVector();
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTupleIsVector()\n";

			return result;
		}

		bool CreatePoint()
		{
			Point p(4.0f, -4.0f, 3.0f);
			bool result = p.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreatePoint()\n";

			return result;
		}
		
		bool CreateVector()
		{
			Vector v(4.0f, -4.0f, 3.0f);
			bool result = v.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tCreateVector()\n";

			return result;
		}

		bool TuplesAreEqual()
		{					
			Tuple a(1.0f, 2.0f, 3.0f, 0.0f);
			Tuple b(1.0f, 2.0f, 3.0f, 0.0f);

			bool result = (a == b);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTuplesAreEqual()\n";

			return result;

		}

		bool TuplesAreNotEqual()
		{
			Tuple a(5, 2, 3, 0);
			Tuple b(1, 2, 3, 0);

			bool result = (a != b);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "TuplesAreNotEqual()\n";

			return result;

		}

		bool TupleAddition()
		{
			Tuple a(1, 1, 1, 0);
			Tuple b(1, 2, 3, 0);

			Tuple c = a + b;
			
			bool result = (c.x == 2 && c.y == 3 && c.z == 4 && c.w == 0);
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "TupleAddition()\n";

			return result;
		}

		bool PointPlusPoint()
		{
			Point a(1, 1, 1);
			Point b(1, 2, 3);

			Tuple c = a + b;

			bool result = ((c.x == 2) && (c.y == 3) && (c.z == 4)) && !c.isPoint() && !c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointPlusPoint()\n";

			return result;
		}

		bool VectorPlusVector()
		{
			Vector a(1, 1, 1);
			Vector b(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) && c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorPlusVector()\n";

			return result;
		}

		bool VectorPlusPoint()
		{
			Vector a(1, 1, 1);
			Point b(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) && c.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorPlusPoint()\n";

			return result;
		}

		bool TupleSubtraction()
		{
			Tuple a(1, 2, 3, 0);
			Tuple b(1, 1, 1, 0);			

			Tuple c = a - b;

			bool result = (c.x == 0 && c.y == 1 && c.z == 2 && c.w == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "TupleSubtraction()\n";

			return result;
		}

		bool PointSubtractPoint()
		{
			Point p1(3, 2, 1);
			Point p2(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 0) && c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointSubtractPoint()\n";

			return result;
		}

		bool VectorSubtractVector()
		{
			Vector p1(3, 2, 1);
			Vector p2(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 0) && c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorSubtractVector()\n";

			return result;
		}

		bool PointSubtractVector()
		{
			Point p1(3, 2, 1);
			Vector p2(5, 6, 7);

			Tuple c = p1 - p2;
			
			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 1) && c.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointSubtractVector()\n";

			return result;
		}

		bool VectorSubtractPoint()
		{
			Vector p1(3, 2, 1);
			Point p2(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6) && !c.isVector() && !c.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorSubtractPoint()\n";

			return result;
		}

		bool NegateTuple()
		{
			Tuple p(3, -2, 1, 1);
			p = -p;
						
			bool result = (p.x == -3 && p.y == 2 && p.z == -1 && p.w == -1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NegatePoint()\n";

			return result;
		}

		bool NegateVector()
		{
			Vector p(3, -2, 1);
			p = -p;

			bool result = (p.x == -3 && p.y == 2 && p.z == -1) && p.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NegateVector()\n";

			return result;
		}

		bool MultiplyTupleByScalar1()
		{
			Tuple p(1, -2, 3, -4);
			p = p * 3.5;

			bool result = (p.x == 3.5 && p.y == -7 && p.z == 10.5 && p.w == -14);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MultiplyTupleByScalar1()\n";

			return result;
		}

		bool MultiplyTupleByScalar2()
		{
			Tuple p(1, -2, 3, -4);
			p *= 3.5;

			bool result = (p.x == 3.5 && p.y == -7 && p.z == 10.5 && p.w == -14);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MultiplyTupleByScalar2()\n";

			return result;
		}

		bool MultiplyTupleByFraction1()
		{
			Tuple p(1, -2, 3, -4);
			p =  p * 0.5;

			bool result = (p.x == 0.5 && p.y == -1 && p.z == 1.5 && p.w == -2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MultiplyTupleByFraction1()\n";

			return result;
		}

		bool MultiplyTupleByFraction2()
		{
			Tuple p(1, -2, 3, -4);
			p *= 0.5;

			bool result = (p.x == 0.5 && p.y == -1 && p.z == 1.5 && p.w == -2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MultiplyTupleByFraction2()\n";

			return result;
		}

		bool DivideTupleByScalar1()
		{
			Tuple p(1, -2, 3, -4);
			p = p / 2;

			bool result = (p.x == 0.5 && p.y == -1 && p.z == 1.5 && p.w == -2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "DivideTupleByScalar1()\n";

			return result;
		}

		bool DivideTupleByScalar2()
		{
			Tuple p(1, -2, 3, -4);
			p /= 2;

			bool result = (p.x == 0.5 && p.y == -1 && p.z == 1.5 && p.w == -2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "DivideTupleByScalar2()\n";

			return result;
		}

		bool MagnitudeOfVector1()
		{
			Vector v(1, 0, 0);
			
			bool result = (v.magnitude() == 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector1" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector2()
		{
			Vector v(0, 1, 0);

			bool result = (v.magnitude() == 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector2" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector3()
		{
			Vector v(0.0f, 0.0f, 1.0f);

			bool result = (v.magnitude() == 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector3" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector4()
		{
			Vector v(1, 2, 3);

			bool result = FloatEquals(v.magnitude(), std::sqrt(14.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector4" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector5()
		{
			Vector v(-1, -2, -3);

			bool result = FloatEquals(v.magnitude(), std::sqrt(14.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector5" << v << "\n";

			return result;
		}

		bool NormalizeVector1()
		{
			Vector p(4, 0, 0);
			p = p.normalize();

			bool result = (p.x == 1 && p.y == 0 && p.z == 0 && p.w == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NormalizeVector1()\n";

			return result;
		}

		bool NormalizeVector2()
		{
			Vector p(1, 2, 3);
			p = p.normalize();			
			float m = p.magnitude();
			
			bool result = (FloatEquals(p.x, 0.26726f) && FloatEquals(p.y, 0.53452f) && FloatEquals(p.z, 0.80178f) && FloatEquals(m, 1.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NormalizeVector2()\n";

			return result;
		}

		bool VectorDotProduct()
		{
			Vector a(1, 2, 3);
			Vector b(2, 3, 4);
						
			float dot = a.dot(b);

			bool result = (FloatEquals(dot, 20.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorDotProduct()\n";

			return result;
		}

		bool VectorCrossProduct()
		{
			Vector a(1, 2, 3);
			Vector b(2, 3, 4);

			Tuple c = a.cross(b);
			Tuple d = b.cross(a);

			Vector cp1(-1, 2, -1);
			Vector cp2(1, -2, 1);

			bool result = (c == cp1 && d == cp2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorCrossProduct()\n";

			return result;
		}
	}

}
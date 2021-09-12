#pragma once

#include <iostream>
#include <string>
#include "../src/Tuple.h"

namespace RayTracer
{
	namespace Tests
	{
		bool TupleIsPoint()
		{
			Tuple t(4.3, -4.2, 3.1, 1.0);
			bool result = t.isPoint();
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTupleIsPoint()\n";			

			return result;
		}

		bool TupleIsVector()
		{
			Tuple t(4.3, -4.2, 3.1, 0.0);
			bool result = t.isVector();
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTupleIsVector()\n";

			return result;
		}

		bool CreatePoint()
		{
			Tuple p = Tuple::createPoint(4, -4, 3);
			bool result = p.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreatePoint()\n";

			return result;
		}
		
		bool CreateVector()
		{
			Tuple v = Tuple::createVector(4, -4, 3);
			bool result = v.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tCreateVector()\n";

			return result;
		}

		bool TuplesAreEqual()
		{					
			Tuple a(1, 2, 3, 0);
			Tuple b(1, 2, 3, 0);

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
			Tuple a = Tuple::createPoint(1, 1, 1);
			Tuple b = Tuple::createPoint(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) & !c.isPoint() && !c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointPlusPoint()\n";

			return result;
		}

		bool VectorPlusVector()
		{
			Tuple a = Tuple::createVector(1, 1, 1);
			Tuple b = Tuple::createVector(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) && c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorPlusVector()\n";

			return result;
		}

		bool VectorPlusPoint()
		{
			Tuple a = Tuple::createVector(1, 1, 1);
			Tuple b = Tuple::createPoint(1, 2, 3);

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
			Tuple p1 = Tuple::createPoint(3, 2, 1);
			Tuple p2 = Tuple::createPoint(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 0) && c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointSubtractPoint()\n";

			return result;
		}

		bool VectorSubtractVector()
		{
			Tuple p1 = Tuple::createVector(3, 2, 1);
			Tuple p2 = Tuple::createVector(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 0) && c.isVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorSubtractVector()\n";

			return result;
		}

		bool PointSubtractVector()
		{
			Tuple p1 = Tuple::createPoint(3, 2, 1);
			Tuple p2 = Tuple::createVector(5, 6, 7);

			Tuple c = p1 - p2;
			
			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 1) && c.isPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointSubtractVector()\n";

			return result;
		}

		bool VectorSubtractPoint()
		{
			Tuple p1 = Tuple::createVector(3, 2, 1);
			Tuple p2 = Tuple::createPoint(5, 6, 7);

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
			Tuple p = Tuple::createVector(3, -2, 1);
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
			Tuple v = Tuple::createVector(1, 0, 0);
			
			bool result = (v.magnitude() == 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector1" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector2()
		{
			Tuple v = Tuple::createVector(0, 1, 0);

			bool result = (v.magnitude() == 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector2" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector3()
		{
			Tuple v = Tuple::createVector(0, 0, 1);

			bool result = (v.magnitude() == 1);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector3" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector4()
		{
			Tuple v = Tuple::createVector(1, 2, 3);

			bool result = FloatEquals(v.magnitude(), std::sqrt(14));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector4" << v << "\n";

			return result;
		}

		bool MagnitudeOfVector5()
		{
			Tuple v = Tuple::createVector(-1, -2, -3);

			bool result = FloatEquals(v.magnitude(), std::sqrt(14));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MagnitudeOfVector5" << v << "\n";

			return result;
		}

		bool NormalizeVector1()
		{
			Tuple p = Tuple::createVector(4, 0, 0);
			p = p.normalize();

			bool result = (p.x == 1 && p.y == 0 && p.z == 0 && p.w == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NormalizeVector1()\n";

			return result;
		}

		bool NormalizeVector2()
		{
			Tuple p = Tuple::createVector(1, 2, 3);
			p = p.normalize();			
			float m = p.magnitude();
			
			bool result = (FloatEquals(p.x, 0.26726) && FloatEquals(p.y, 0.53452) && FloatEquals(p.z, 0.80178) && FloatEquals(m, 1.0));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NormalizeVector2()\n";

			return result;
		}

		bool VectorDotProduct()
		{
			Tuple a = Tuple::createVector(1, 2, 3);
			Tuple b = Tuple::createVector(2, 3, 4);
						
			float dot = a.dot(b);

			bool result = (FloatEquals(dot, 20.0f));

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorDotProduct()\n";

			return result;
		}

		bool VectorCrossProduct()
		{
			Tuple a = Tuple::createVector(1, 2, 3);
			Tuple b = Tuple::createVector(2, 3, 4);

			Tuple c = a.cross(b);
			Tuple d = b.cross(a);

			Tuple cp1 = Tuple::createVector(-1, 2, -1);
			Tuple cp2 = Tuple::createVector(1, -2, 1);

			bool result = (c == cp1 && d == cp2);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorCrossProduct()\n";

			return result;
		}
	}

}
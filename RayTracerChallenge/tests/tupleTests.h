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
			bool result = t.IsPoint();
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTupleIsPoint()\n";			

			return result;
		}

		bool TupleIsVector()
		{
			Tuple t(4.3, -4.2, 3.1, 0.0);
			bool result = t.IsVector();
			
			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTupleIsVector()\n";

			return result;
		}

		bool CreatePoint()
		{
			Tuple p = Tuple::CreatePoint(4, -4, 3);
			bool result = p.IsPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreatePoint()\n";

			return result;
		}
		
		bool CreateVector()
		{
			Tuple v = Tuple::CreateVector(4, -4, 3);
			bool result = v.IsVector();

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
			Tuple a = Tuple::CreatePoint(1, 1, 1);
			Tuple b = Tuple::CreatePoint(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) & !c.IsPoint() && !c.IsVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointPlusPoint()\n";

			return result;
		}

		bool VectorPlusVector()
		{
			Tuple a = Tuple::CreateVector(1, 1, 1);
			Tuple b = Tuple::CreateVector(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) && c.IsVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorPlusVector()\n";

			return result;
		}

		bool VectorPlusPoint()
		{
			Tuple a = Tuple::CreateVector(1, 1, 1);
			Tuple b = Tuple::CreatePoint(1, 2, 3);

			Tuple c = a + b;

			bool result = (c.x == 2 && c.y == 3 && c.z == 4) && c.IsPoint();

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
			Tuple p1 = Tuple::CreatePoint(3, 2, 1);
			Tuple p2 = Tuple::CreatePoint(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 0) && c.IsVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointSubtractPoint()\n";

			return result;
		}

		bool VectorSubtractVector()
		{
			Tuple p1 = Tuple::CreateVector(3, 2, 1);
			Tuple p2 = Tuple::CreateVector(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 0) && c.IsVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorSubtractVector()\n";

			return result;
		}

		bool PointSubtractVector()
		{
			Tuple p1 = Tuple::CreatePoint(3, 2, 1);
			Tuple p2 = Tuple::CreateVector(5, 6, 7);

			Tuple c = p1 - p2;
			
			bool result = (c.x == -2 && c.y == -4 && c.z == -6 && c.w == 1) && c.IsPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "PointSubtractVector()\n";

			return result;
		}

		bool VectorSubtractPoint()
		{
			Tuple p1 = Tuple::CreateVector(3, 2, 1);
			Tuple p2 = Tuple::CreatePoint(5, 6, 7);

			Tuple c = p1 - p2;

			bool result = (c.x == -2 && c.y == -4 && c.z == -6) && !c.IsVector() && !c.IsPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "VectorSubtractPoint()\n";

			return result;
		}

		bool NegatePoint()
		{
			Tuple p = Tuple::CreatePoint(3, -2, 1);
			p = -p;
						
			bool result = (p.x == -3 && p.y == 2 && p.z == -1) && p.IsPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NegatePoint()\n";

			return result;
		}

		bool NegateVector()
		{
			Tuple p = Tuple::CreateVector(3, -2, 1);
			p = -p;

			bool result = (p.x == -3 && p.y == 2 && p.z == -1) && p.IsVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "NegateVector()\n";

			return result;
		}
	}

}
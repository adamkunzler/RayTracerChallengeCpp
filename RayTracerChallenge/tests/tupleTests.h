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

		bool TuplesAreEqual(Tuple& a, Tuple& b)
		{						
			bool result = (a == b);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTuplesAreEqual(" << a << ", " << b << ")\n";

			return result;

		}

		bool TuplesAreNotEqual(Tuple& a, Tuple& b)
		{
			bool result = (a != b);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tTuplesAreNotEqual(" << a << ", " << b << ")\n";

			return result;

		}
	}

}
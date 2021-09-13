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
		bool ColorsAreTuples()
		{
			Color data(-0.5, 0.4, 1.7);
			bool result = FloatEquals(data.red(), -0.5) && FloatEquals(data.green(), 0.4) && FloatEquals(data.blue(), 1.7);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "ColorsAreTuples()\n";

			return result;
		}

		bool AddColors1()
		{
			Color c1(0.9, 0.6, 0.75);
			Color c2(0.7, 0.1, 0.25);

			Color c3 = c1 + c2;

			bool result = FloatEquals(c3.red(), 1.6) && FloatEquals(c3.green(), 0.7) && FloatEquals(c3.blue(), 1.0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "AddColors1()\n";

			return result;
		}

		bool AddColors2()
		{
			Color c1(0.9, 0.6, 0.75);
			Color c2(0.7, 0.1, 0.25);

			c1 += c2;

			bool result = FloatEquals(c1.red(), 1.6) && FloatEquals(c1.green(), 0.7) && FloatEquals(c1.blue(), 1.0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "AddColors2()\n";

			return result;
		}

		bool SubtractColors1()
		{
			Color c1(0.9, 0.6, 0.75);
			Color c2(0.7, 0.1, 0.25);

			Color c3 = c1 - c2;

			bool result = FloatEquals(c3.red(), 0.2) && FloatEquals(c3.green(), 0.5) && FloatEquals(c3.blue(), 0.5);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "SubtractColors1()\n";

			return result;
		}

		bool SubtractColors2()
		{
			Color c1(0.9, 0.6, 0.75);
			Color c2(0.7, 0.1, 0.25);

			c1 -= c2;

			bool result = FloatEquals(c1.red(), 0.2) && FloatEquals(c1.green(), 0.5) && FloatEquals(c1.blue(), 0.5);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "SubtractColors2()\n";

			return result;
		}

		bool ColorMultipliedByScalar1()
		{
			Color c(0.2, 0.3, 0.4);

			c = c * 2;

			bool result = FloatEquals(c.red(), 0.4) && FloatEquals(c.green(), 0.6) && FloatEquals(c.blue(), 0.8);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "ColorMultipliedByScalar1()\n";

			return result;
		}

		bool ColorMultipliedByScalar2()
		{
			Color c(0.2, 0.3, 0.4);

			c *= 2.0f;

			bool result = FloatEquals(c.red(), 0.4) && FloatEquals(c.green(), 0.6) && FloatEquals(c.blue(), 0.8);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "ColorMultipliedByScalar2()\n";

			return result;
		}

		bool MultiplyingColors1()
		{
			Color c1(1, 0.2, 0.4);
			Color c2(0.9, 1, 0.1);

			c1 = c1 * c2;

			bool result = FloatEquals(c1.red(), 0.9) && FloatEquals(c1.green(), 0.2) && FloatEquals(c1.blue(), 0.04);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MultiplyingColors1()\n";

			return result;
		}

		bool MultiplyingColors2()
		{
			Color c1(1, 0.2, 0.4);
			Color c2(0.9, 1, 0.1);

			c1 *= c2;

			bool result = FloatEquals(c1.red(), 0.9) && FloatEquals(c1.green(), 0.2) && FloatEquals(c1.blue(), 0.04);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "MultiplyingColors2()\n";

			return result;
		}
	}
}
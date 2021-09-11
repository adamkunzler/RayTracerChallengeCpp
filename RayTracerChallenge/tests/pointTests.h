#pragma once

#include <iostream>
#include <string>
#include "../src/Tuple.h"
#include "../src/Point.h"

namespace RayTracer
{
	namespace Tests
	{
		bool CreatePoint()
		{
			Point p(4, -4, 3);
			bool result = p.IsPoint();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tCreatePoint()\n";

			return result;
		}
	}

}
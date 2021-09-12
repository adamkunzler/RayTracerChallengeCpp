#pragma once

#include <iostream>
#include <string>
#include "../src/Utils.h"

namespace RayTracer
{
	namespace Tests
	{
		bool Util_FloatEquals(float a, float b)
		{			
			bool result = FloatEquals(a, b);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "FloatEquals()\n";

			return result;
		}

		bool Util_FloatNotEquals(float a, float b)
		{
			bool result = !FloatEquals(a, b);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "FloatNotEquals()\n";

			return result;
		}
	}

}
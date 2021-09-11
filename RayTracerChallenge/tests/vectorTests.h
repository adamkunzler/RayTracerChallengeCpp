#pragma once

#include <iostream>
#include <string>
#include "../src/Tuple.h"
#include "../src/Vector.h"

namespace RayTracer
{
	namespace Tests
	{
		bool CreateVector()
		{
			Vector v(4, -4, 3);
			bool result = v.IsVector();

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\tCreateVector()\n";

			return result;
		}		
	}

}
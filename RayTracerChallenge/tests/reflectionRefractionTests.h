#pragma once

namespace RayTracer
{
	namespace Tests
	{
		//
		// PLANES
		//

		bool Reflection_()
		{
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "Reflection_()\n";

			return result;
		}		
	}
}
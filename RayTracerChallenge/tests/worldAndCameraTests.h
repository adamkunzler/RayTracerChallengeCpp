#pragma once

namespace RayTracer
{
	namespace Tests
	{
		bool World_Create()
		{
			World w;
			bool result = (w.lights.size() == 0) && (w.objects.size() == 0);

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_Create()\n";

			return result;
		}		
		
		bool World_RayIntersect()
		{
			World w = World::defaultWorld();
			Ray r(Point(0, 0, -5), Vector(0, 0, 1));

			
			bool result = false;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "World_RayIntersect()\n";

			return result;
		}
	}
}
#pragma once

namespace RayTracer
{
	namespace Tests
	{		
		struct TestPattern : public IPattern
		{
			TestPattern() {}
			~TestPattern() {}
			Color patternAt(const Point4& p) const { return Color(p.x, p.y, p.z); }
		};

		struct TestResults
		{
			TestResults() : numPassed(0)
			{}

			int numPassed;
			std::vector<std::string> failedTests;
		};
		
		void RunTests();

		TestResults _tests();

		World* getDefaultWorld();

		Sphere* getGlassSphere();
	} // end namespace tests
} // end namespace raytracer

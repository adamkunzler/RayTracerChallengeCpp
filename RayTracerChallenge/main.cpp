
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

#include "src/Utils.h"

#include "tests\_testHarness.h"

//#include "Exercises\Chapter1\VirtualCannon.h"
//#include "Exercises\Chapter2\ProjectilePPM.h"
//#include "Exercises\Chapter4\Clock.h"
//#include "Exercises\Chapter5\RayTraceSphere.h"
//#include "Exercises\Chapter6\RayTraceSphere.h"

void RunRayTracer();

int main()
{
	std::cout << "\nThe Ray Tracer Challenge\n\n\n";
	
	bool result = RayTracer::Tests::RunTests();

	//Exercises::Chapter1::FireCannon();
	//Exercises::Chapter2::ProjectilePPM();
	//Exercises::Chapter4::Clock();
	//Exercises::Chapter5::RayTraceSphere();
	//Exercises::Chapter6::RayTraceSphere();

	
	//if(result) RunRayTracer();

	std::cout << "\n\n\n";
	return 0;
}



void RunRayTracer()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "\n\nRunning Ray Tracer...\n\n";

	std::cout << "NOT IMPLEMENTED\n\n";

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\nRay Tracer Completed in " << duration.count() << "ms.\n";

	return;
}
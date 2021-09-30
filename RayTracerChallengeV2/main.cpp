#include <iostream>
#include <chrono>

#include "Benchmarks\benchmarks.h"

void DoSomething();

int main()
{
	std::cout << "\n\n --- Ray Tracer Challenge V2 --- \n\n";

	benchmarkVector3(10000000);

	return 0;
}

void DoSomething()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "\n\nRunning Ray Tracer...\n\n";

	std::cout << "NOT IMPLEMENTED\n\n";

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "\nRay Tracer Completed in " << duration.count() << "ms.\n";

	return;
}
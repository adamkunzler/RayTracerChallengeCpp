#pragma once

#include <iostream>
#include <chrono>

#include "../src/DataStructs/Tuple.h"
#include "../src/DataStructs/Vector.h"

void benchmarkVector(int num)
{
	std::cout << "\n Benchmark - Vector - " << num << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < num; i++)
	{
		RayTracer::Vector a(5.0f, 10.5f, 7.25f);
		RayTracer::Vector b(1.0f, 1.5f, 2.0f);
		RayTracer::Vector c(3.3f, 5.5f, 7.7f);
		float scalar1 = 2.5f;
		float scalar2 = 7.0f;

		RayTracer::Vector::dot(a, b);
		RayTracer::Vector::cross(b, c);
		RayTracer::Vector::normalize(a);

		RayTracer::Vector aa = a + b;
		RayTracer::Vector bb = b - c;
		RayTracer::Vector cc = a * scalar1;
		RayTracer::Vector dd = b / scalar1;
		RayTracer::Vector ee = a * scalar2;
		RayTracer::Vector ff = b / scalar2;
		float gg = RayTracer::Vector::dot(a, b);
		float hh = RayTracer::Vector::dot(c, a);

		RayTracer::Vector::normalize(a);
		RayTracer::Vector::normalize(b);		
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	long long ms = duration.count();
	std::cout << "Completed in " << ms << "ms (" << (ms / 1000) << "s)\n";
}
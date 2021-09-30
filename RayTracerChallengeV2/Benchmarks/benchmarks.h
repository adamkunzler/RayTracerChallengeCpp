#pragma once

#include <iostream>
#include <chrono>

#include "../src/DataStructs/Vector3.h"

void benchmarkVector3(int num)
{
	std::cout << "\n Benchmark - Vector3 - " << num << "\n";
	
	auto start = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < num; i++)
	{
		RayTracer::Vector3 a(5.0f, 10.5f, 7.25f);
		RayTracer::Vector3 b(1.0f, 1.5f, 2.0f);
		RayTracer::Vector3 c(3.3f, 5.5f, 7.7f);
		float scalar1 = 2.5f;
		float scalar2 = 7.0f;

		RayTracer::dot(a, b);
		RayTracer::cross(b, c);
		RayTracer::normalize(a);

		RayTracer::Vector3 aa = a + b;
		RayTracer::Vector3 bb = b - c;
		RayTracer::Vector3 cc = a * scalar1;
		RayTracer::Vector3 dd = b / scalar1;
		RayTracer::Vector3 ee = scalar2 * a;
		RayTracer::Vector3 ff = scalar2 * b;
		float gg = a.dot(b);
		float hh = c.dot(a);

		a.normalize();
		b.normalize();
		c.zero();
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	long long ms = duration.count();
	std::cout << "Completed in " << ms << "ms (" << (ms / 1000) << "s)\n";
}
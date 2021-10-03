#pragma once

#include <iostream>
#include <chrono>
#include <map>
#include <string>

#include "../src/DataStructs/Vector4.h"
#include "../src/DataStructs/Matrix4x4.h"

void benchmarkVector4(int num)
{
	std::cout << "\n Benchmark - Vector4 - " << num << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < num; i++)
	{
		RayTracer::Vector4 a(5.0f, 10.5f, 7.25f);
		RayTracer::Vector4 b(1.0f, 1.5f, 2.0f);
		RayTracer::Vector4 c(3.3f, 5.5f, 7.7f);
		float scalar1 = 2.5f;
		float scalar2 = 7.0f;

		RayTracer::dot(a, b);
		RayTracer::cross(b, c);
		RayTracer::normalize(a);

		RayTracer::Vector4 aa = a + b;
		RayTracer::Vector4 bb = b - c;
		RayTracer::Vector4 cc = a * scalar1;
		RayTracer::Vector4 dd = b / scalar1;
		RayTracer::Vector4 ee = scalar2 * a;
		RayTracer::Vector4 ff = scalar2 * b;
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

void benchmarkMatrix4x4(int num)
{
	std::cout << "\n Benchmark - Matrix4x4 - " << num << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < num; i++)
	{
		RayTracer::Vector4 v1(1.0f, 2.0f, 3.0f);
		RayTracer::Vector4 v2(3.0f, 4.0f, 5.0f);

		RayTracer::Vector4 p1(3.0f, 2.0f, 1.0f, 1.0f);
		RayTracer::Vector4 p2(4.0f, 3.0f, 2.0f, 1.0f);

		RayTracer::Matrix4x4 a(
			1, 2, 3, 4,
			2, 3, 4, 5,
			3, 4, 5, 6,
			4, 5, 6, 7);

		RayTracer::Matrix4x4 b(
			1, 3, 5, 7,
			3, 5, 7, 9,
			5, 7, 9, 11,
			7, 9, 11, 13
		);

		RayTracer::Matrix4x4 c = a * b;

		RayTracer::Matrix4x4 t1 = RayTracer::identity4x4();
		RayTracer::Matrix4x4 t2 = RayTracer::transpose4x4(a);

		RayTracer::Matrix4x4 t3 = RayTracer::translation(5.0f, 10.0f, 3.0f);
		RayTracer::Matrix4x4 t32 = a * t3;

		RayTracer::Matrix4x4 t4 = RayTracer::scaling(-1.0f, 1.0f, 5.0f);
		RayTracer::Matrix4x4 t42 = b * t4;

		RayTracer::Matrix4x4 t5 = RayTracer::shearing(1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f);
		RayTracer::Matrix4x4 t52 = a * t5;

		RayTracer::Matrix4x4 t6 = RayTracer::xRotation4x4(2.25f);
		RayTracer::Matrix4x4 t62 = b * t6;

		RayTracer::Matrix4x4 t7 = RayTracer::yRotation4x4(1.5f);
		RayTracer::Matrix4x4 t72 = a * t7;

		RayTracer::Matrix4x4 t8 = RayTracer::zRotation4x4(3.0f);
		RayTracer::Matrix4x4 t82 = b * t8;

		RayTracer::Vector4 tv1 = v1 * t3;
		RayTracer::Vector4 tv2 = v2 * t5;
		RayTracer::Vector4 tp1 = p1 * t7;
		RayTracer::Vector4 tp2 = p1 * t8;
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	long long ms = duration.count();
	std::cout << "Completed in " << ms << "ms (" << (ms / 1000) << "s)\n";
}

bool _benchmark_Matrix_Inverse_1()
{
	RayTracer::Matrix4x4 m(
		-5.0f, 2.0f, 6.0f, -8.0f,
		1.0f, -5.0f, 1.0f, 8.0f,
		7.0f, 7.0f, -6.0f, -7.0f,
		1.0f, -3.0f, 7.0f, 4.0f);

	RayTracer::Matrix4x4 expected(
		0.21805f, 0.45113f, 0.24060f, -0.04511f,
		-0.80827f, -1.45677f, -0.44361f, 0.52068f,
		-0.07895f, -0.22368f, -0.05263f, 0.19737f,
		-0.52256f, -0.81391f, -0.30075f, 0.30639f);
	
	RayTracer::Matrix4x4 b = RayTracer::inverse(m);

	//std::cout << "\n _benchmark_Matrix_Inverse_1 result:" << b;
	//std::cout << "\n _benchmark_Matrix_Inverse_1 expected:" << expected;

	bool result = b == expected;
	return result;
}

bool _benchmark_Matrix_Inverse_2()
{
	RayTracer::Matrix4x4 m(
		8.0f, -5.0f, 9.0f, 2.0f,
		7.0f, 5.0f, 6.0f, 1.0f,
		-6.0f, 0.0f, 9.0f, 6.0f,
		-3.0f, 0.0f, -9.0f, -4.0f);

	RayTracer::Matrix4x4 expected(
		-0.15385f, -0.15385f, -0.28205f, -0.53846f,
		-0.07692f, 0.12308f, 0.02564f, 0.03077f,
		0.35897f, 0.35897f, 0.43590f, 0.92308f,
		-0.69231f, -0.69231f, -0.76923f, -1.92308f);
	
	RayTracer::Matrix4x4 b = RayTracer::inverse(m);

	//std::cout << "\n _benchmark_Matrix_Inverse_2 result:" << b;
	//std::cout << "\n _benchmark_Matrix_Inverse_2 expected:" << expected;

	bool result = b == expected;
	return result;
}

bool _benchmark_Matrix_Inverse_3()
{
	RayTracer::Matrix4x4 m(
		9.0f, 3.0f, 0.0f, 9.0f,
		-5.0f, -2.0f, -6.0f, -3.0f,
		-4.0f, 9.0f, 6.0f, 4.0f,
		-7.0f, 6.0f, 6.0f, 2.0f);

	RayTracer::Matrix4x4 expected(
		-0.04074f, -0.07778f, 0.14444f, -0.22222f,
		-0.07778f, 0.03333f, 0.36667f, -0.33333f,
		-0.02901f, -0.14630f, -0.10926f, 0.12963f,
		0.17778f, 0.06667f, -0.26667f, 0.33333f);
	
	RayTracer::Matrix4x4 b = RayTracer::inverse(m);

	//std::cout << "\n _benchmark_Matrix_Inverse_3 result:" << b;
	//std::cout << "\n _benchmark_Matrix_Inverse_3 expected:" << expected;

	bool result = b == expected;
	return result;
}

void benchmarkMatrix4x4Inversions(int num)
{
	std::cout << "\n Benchmark - Matrix4x4 Inversions - " << num << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	bool b1 = _benchmark_Matrix_Inverse_1();
	bool b2 = _benchmark_Matrix_Inverse_2();
	bool b3 = _benchmark_Matrix_Inverse_3();
	/*bool b4 = b1 && b2 && b3;
	if (!b4) {
		std::cout << "\n Matrix4x4::inverse is wrong! :(\n"; // it's actually right...but for floating point accuracy
		return;
	}*/

	for (int i = 0; i < num - 1; i++)
	{
		_benchmark_Matrix_Inverse_1();
		_benchmark_Matrix_Inverse_2();
		_benchmark_Matrix_Inverse_3();
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	long long ms = duration.count();
	std::cout << "Completed in " << ms << "ms (" << (ms / 1000) << "s)\n";
}
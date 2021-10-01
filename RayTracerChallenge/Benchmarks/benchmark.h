#pragma once

#include <iostream>
#include <chrono>

#include "../src/DataStructs/Tuple.h"
#include "../src/DataStructs/Vector.h"
#include "../src/DataStructs/Matrix.h"

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

void benchmarkMatrix(int num)
{
	std::cout << "\n Benchmark - Matrix - " << num << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < num; i++)
	{
		RayTracer::Vector v1(1.0f, 2.0f, 3.0f);
		RayTracer::Vector v2(3.0f, 4.0f, 5.0f);

		RayTracer::Point p1(3.0f, 2.0f, 1.0f);
		RayTracer::Point p2(4.0f, 3.0f, 2.0f);

		RayTracer::Matrix a(4, 4, std::unique_ptr<float[]>(new float[16]{
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2
			}));

		RayTracer::Matrix b(4, 4, std::unique_ptr<float[]>(new float[16]{
			-2, 1, 2, 3,
			3, 2, 1, -1,
			4, 3, 6, 5,
			1, 2, 7, 8
			}));

		RayTracer::Matrix c = a * b;

		RayTracer::Matrix t1 = RayTracer::Matrix::get4x4IdentityMatrix();
		RayTracer::Matrix t2 = a.transpose();

		RayTracer::Matrix t3 = RayTracer::Matrix::get4x4TranslationMatrix(5.0f, 10.0f, 3.0f);
		RayTracer::Matrix t32 = a * t3;

		RayTracer::Matrix t4 = RayTracer::Matrix::get4x4ScalingMatrix(-1.0f, 1.0f, 5.0f);
		RayTracer::Matrix t42 = b * t4;

		RayTracer::Matrix t5 = RayTracer::Matrix::get4x4ShearingMatrix(1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f);
		RayTracer::Matrix t52 = a * t5;

		RayTracer::Matrix t6 = RayTracer::Matrix::get4x4RotationMatrix_X(2.25f);
		RayTracer::Matrix t62 = b * t6;

		RayTracer::Matrix t7 = RayTracer::Matrix::get4x4RotationMatrix_Y(1.5f);
		RayTracer::Matrix t72 = a * t7;

		RayTracer::Matrix t8 = RayTracer::Matrix::get4x4RotationMatrix_Z(3.0f);
		RayTracer::Matrix t82 = b * t8;

		RayTracer::Vector tv1 = (t3 * v1).toVector();
		RayTracer::Vector tv2 = (t5 * v2).toVector();
		RayTracer::Point tp1 = (t7 * p1).toPoint();
		RayTracer::Point tp2 = (t8 * p1).toPoint();
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	long long ms = duration.count();
	std::cout << "Completed in " << ms << "ms (" << (ms / 1000) << "s)\n";
}

bool _benchmark_Matrix_Inverse_1()
{
	Matrix m(4, 4, std::unique_ptr<float[]>(new float[16]{
		-5,2,6,-8,
		1,-5,1,8,
		7,7,-6,-7,
		1,-3,7,4
		}));

	Matrix expected(4, 4, std::unique_ptr<float[]>(new float[16]{
		0.21805f,  0.45113f, 0.24060f,-0.04511f,
		-0.80827f,-1.45677f,-0.44361f, 0.52068f,
		-0.07895f,-0.22368f,-0.05263f, 0.19737f,
		-0.52256f,-0.81391f,-0.30075f, 0.30639f
		}));

	Matrix b = m.inverse();
	
	bool result = b == expected;	
	return result;
}

bool _benchmark_Matrix_Inverse_2()
{
	Matrix m(4, 4, std::unique_ptr<float[]>(new float[16]{
		8,-5,9,2,
		7,5,6,1,
		-6,0,9,6,
		-3,0,-9,-4
		}));

	Matrix expected(4, 4, std::unique_ptr<float[]>(new float[16]{
		-0.15385f, -0.15385f, -0.28205f, -0.53846f,
		-0.07692f,  0.12308f,  0.02564f,  0.03077f,
		 0.35897f,  0.35897f,  0.43590f,  0.92308f,
		-0.69231f, -0.69231f, -0.76923f, -1.92308f
		}));

	Matrix b = m.inverse();

	bool result = b == expected;	
	return result;
}

bool _benchmark_Matrix_Inverse_3()
{
	Matrix m(4, 4, std::unique_ptr<float[]>(new float[16]{
		9,3,0,9,
		-5,-2,-6,-3,
		-4,9,6,4,
		-7,6,6,2
		}));

	Matrix expected(4, 4, std::unique_ptr<float[]>(new float[16]{
		-0.04074f, -0.07778f,  0.14444f, -0.22222f,
		-0.07778f,  0.03333f,  0.36667f, -0.33333f,
		-0.02901f, -0.14630f, -0.10926f,  0.12963f,
		 0.17778f,  0.06667f, -0.26667f,  0.33333f
		}));

	Matrix b = m.inverse();

	bool result = b == expected;
	return result;
}

void benchmarkMatrixInversions(int num)
{
	std::cout << "\n Benchmark - Matrix Inversions - " << num << "\n";

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < num; i++)
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


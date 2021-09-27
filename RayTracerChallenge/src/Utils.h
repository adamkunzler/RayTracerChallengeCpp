#pragma once

namespace RayTracer
{
	const float PI(3.14159265358979323846264338327950288419716939937510f); // 50 digits
	const float EPSILON(0.01f);
	const int MAX_RECURSION(5);

	bool FloatEquals(float a, float b)
	{
		return std::abs(a - b) < EPSILON;
	}
	
	/// <summary>
	/// Write a progress bar out to std::cout
	/// </summary>
	/// <param name="progress">a value between 0 and 1 inclusive</param>
	void showProgressBar(float progress)
	{
		//https://stackoverflow.com/a/14539953

		if (progress < 0) progress = 0;
		if (progress > 1) progress = 1;

		int barWidth = 70;

		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %\r";
		std::cout.flush();
	}
}
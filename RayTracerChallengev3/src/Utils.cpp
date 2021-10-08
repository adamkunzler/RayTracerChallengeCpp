#include "Headers.h"

const double EPSILON = 0.0001;
const double EPSILON2 = 0.0001;
const double sqrt2 = sqrt(2.0);
const double sqrt2over2 = sqrt(2.0) / 2.0;
const double PI = 3.14159265358979323846264338327950288419716939937510; // 50 digits
const int MAX_RECURSION = 5;

bool feq(const double& a, const double& b)
{
	return abs(a - b) < EPSILON;
}

/// <summary>
/// Write a progress bar out to std::cout
/// </summary>
/// <param name="progress">a value between 0 and 1 inclusive</param>
void showProgressBar(double progress)
{
	//https://stackoverflow.com/a/14539953

	if (progress < 0) progress = 0;
	if (progress > 1) progress = 1;

	int barWidth = 70;

	std::cout << "[";
	int pos = (int)(barWidth * progress);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
}


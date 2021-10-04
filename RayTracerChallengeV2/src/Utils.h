#pragma once

#include <iostream>
#include <cmath>

#include "Utils.h"

extern const float EPSILON = 0.0001f;
extern const float EPSILON2 = 0.0001f;
extern const float sqrt2 = sqrtf(2.0f);
extern const float sqrt2over2 = sqrtf(2.0f) / 2.0f;
extern const float PI = 3.14159265358979323846264338327950288419716939937510f; // 50 digits
extern const int MAX_RECURSION = 5;

bool feq(const float& a, const float& b)
{
	return fabsf(a - b) < EPSILON;
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
	int pos = (int)(barWidth * progress);
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
}
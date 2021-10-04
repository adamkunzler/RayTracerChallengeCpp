#pragma once

#include <iostream>
#include <cfloat>
#include <corecrt_math.h>

#include "Utils.h"

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
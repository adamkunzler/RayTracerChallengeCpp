#pragma once

extern const float EPSILON;
extern const float EPSILON2;
extern const float sqrt2;
extern const float sqrt2over2;
extern const float PI;
extern const int MAX_RECURSION;

bool feq(const float& a, const float& b);

/// <summary>
/// Write a progress bar out to std::cout
/// </summary>
/// <param name="progress">a value between 0 and 1 inclusive</param>
void showProgressBar(float progress);

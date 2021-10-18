#pragma once

extern const double EPSILON;
extern const double EPSILON2;
extern const double sqrt2;
extern const double sqrt2over2;
extern const double PI;
extern const int MAX_RECURSION;
extern const int MAX_SAMPLES;

bool feq(const double& a, const double& b);

/// <summary>
/// Write a progress bar out to std::cout
/// </summary>
/// <param name="progress">a value between 0 and 1 inclusive</param>
void showProgressBar(double progress);

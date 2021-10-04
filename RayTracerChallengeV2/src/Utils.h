#pragma once

const float EPSILON = 0.0001f;
const float EPSILON2 = 0.0001f;
const float sqrt2 = sqrtf(2.0f);
const float sqrt2over2 = sqrtf(2.0f) / 2.0f;
const float PI = 3.14159265358979323846264338327950288419716939937510f; // 50 digits
const int MAX_RECURSION = 5;

bool feq(const float& a, const float& b);

/// <summary>
/// Write a progress bar out to std::cout
/// </summary>
/// <param name="progress">a value between 0 and 1 inclusive</param>
void showProgressBar(float progress);
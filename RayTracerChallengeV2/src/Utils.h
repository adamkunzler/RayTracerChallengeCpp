#include <cfloat>
#include <corecrt_math.h>

extern const float EPSILON = 0.00001f;
extern const float EPSILON2 = 0.01f;
extern const float sqrt2 = sqrtf(2.0f);
extern const float sqrt2over2 = sqrtf(2.0f) / 2.0f;
extern const float PI = 3.14159265358979323846264338327950288419716939937510f; // 50 digits
extern const int MAX_RECURSION = 5;

bool feq(const float& a, const float& b)
{
	return fabsf(a - b) < EPSILON;
}
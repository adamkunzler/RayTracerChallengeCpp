#include <cfloat>
#include <corecrt_math.h>

extern const float EPSILON = 0.00001f;

bool feq(const float& a, const float& b)
{
	return fabsf(a - b) < EPSILON;
}
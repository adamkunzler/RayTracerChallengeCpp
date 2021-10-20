#ifndef HEADERS_H
#include "../Headers.h"
#endif

namespace RayTracer
{
	AreaLight::AreaLight(const Point4& lCorner,
		const Vector4& lFullUVec, const int& lUSteps,
		const Vector4& lFullVVec, const int& lVSteps,
		const Color& lIntensity)
	{
		corner = lCorner;
		usteps = lUSteps;
		vsteps = lVSteps;
		uvec = lFullUVec / usteps;
		vvec = lFullVVec / vsteps;
		samples = usteps * vsteps;

		position = corner + (lFullUVec / 2.0) + (lFullVVec / 2.0);
		position.w = 0.0;

		intensity = lIntensity;

		shouldJitter = true;

		uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); // initialize the random number generator with time-dependent seed
		std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
		rng.seed(ss);
		unif = std::uniform_real_distribution<double>(0, 1); // initialize a uniform distribution between 0 and 1
	}

	double AreaLight::intensityAt(const Point4& point, const World& world) const
	{
		double total = 0.0;

		for (int v = 0; v < vsteps; v++)
		{
			for (int u = 0; u < usteps; u++)
			{
				Point4 lightPosition = pointOnLight(u, v);
				if (!world.isShadowed(lightPosition, point))
				{
					total += 1.0;
				}
			}
		}

		return total / samples;
	}

	Point4 AreaLight::pointOnLight(const int& u, const int& v) const
	{
		if (shouldJitter)
		{
			return corner +
				uvec * (u + unif(rng)) +
				vvec * (v + unif(rng));
		}
		else
		{
			return corner +
				uvec * (u / 0.5) +
				vvec * (v / 0.5);
		}
	}
}
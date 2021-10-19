#pragma once

namespace RayTracer
{
	struct AreaLight : public ILight
	{
		Point4 corner;
		Vector4 uvec;
		int usteps;
		Vector4 vvec;
		int vsteps;
		int samples;

		AreaLight(const Point4& lCorner,
			const Vector4& lFullUVec, const int& lUSteps,
			const Vector4& lFullVVec, const int& lVSteps,
			const Color& lIntensity);

		double intensityAt(const Point4& point, const World& world) const;

		Point4 pointOnLight(const int& u, const int& v) const;
	};
}

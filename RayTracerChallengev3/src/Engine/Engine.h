#pragma once

namespace RayTracer
{					
	Color phong(const ILight* light, const Material& m, const IShape& shape, const Vector4& p, const Vector4& eye, const Vector4& normalV, double intensity);

	void renderThreadFunc(Camera& camera, World& world, int width, int startY, int endY, Color* data);

	void threadProgressBarFunc(int totalPixels, bool progressBarIsVisible);

	std::vector<Color*> renderMultiThread(Camera& camera, World& world, bool progressBarIsVisible, int numThreads);
}

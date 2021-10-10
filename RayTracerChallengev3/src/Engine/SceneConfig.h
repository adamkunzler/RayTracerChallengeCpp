#pragma once

namespace RayTracer
{
	struct SceneConfig
	{
		int width;
		int height;
		double fov;

		Vector4 from;
		Vector4 to;
		Vector4 up;

		SceneConfig() : width(320), height(240), fov(PI / 3.5) { }
	};
}

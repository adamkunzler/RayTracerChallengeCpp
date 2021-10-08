#pragma once

namespace RayTracer
{
	struct SceneConfig
	{
		int width;
		int height;
		float fov;

		Vector4 from;
		Vector4 to;
		Vector4 up;

		SceneConfig() { }
	};
}

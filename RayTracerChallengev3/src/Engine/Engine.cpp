#ifndef HEADERS_H
#include "../Headers.h"
#endif

std::atomic<int> processedPixelsCount;
std::atomic<bool> processingDone;

namespace RayTracer
{
	struct IPattern;

	Color phong(const ILight* light, const Material& m, const IShape& shape, const Vector4& p, const Vector4& eye, const Vector4& normalV, double intensity)
	{
		Color ambient;
		Color diffuse;
		Color specular;

		Color baseColor = (m.pattern) ? m.pattern->patternAt(shape, p) : m.color;
		
		// combine surface color with lights color/intensity		
		Color effectiveColor = baseColor * light->intensity;

		// compute the ambient contriubtion
		ambient = effectiveColor * m.ambient;

		// // skip diffuse and specular if in shadow
		if (intensity < EPSILON) return ambient;
		
		AreaLight* areaLight = (AreaLight*)light;

		// TODO - figure out better way to do this
		if (areaLight)
		{
			Color sum(0, 0, 0);
			for (int v = 0; v < areaLight->vsteps; v++)
			{
				for (int u = 0; u < areaLight->usteps; u++)
				{
					Point4 lightPosition = areaLight->pointOnLight(u, v);
					// find the direction to the light source
					Vector4 lightV = normalize(lightPosition - p);

					// lightDotNormal represents the cosine of the angle betwen
					// the light vector and the normal vector. A negative number 
					// means the light is on the other side of the surface
					double lightDotNormal = lightV.dot(normalV);
					if (lightDotNormal >= 0.0)
					{
						// compute the diffuse contribution
						sum += effectiveColor * m.diffuse * lightDotNormal;

						// reflectDotEye represents the cosine of the angle between the reflection
						// vector and the eye vector. A negative number means the light reflects 
						// away from the eye				
						Vector4 negLightV = -lightV;
						Vector4 reflectV = negLightV.reflect(normalV);
						double reflectDotEye = dot(reflectV, eye);
						if (reflectDotEye > 0.0)
						{
							// compute specular contribution
							double factor = std::pow(reflectDotEye, m.shininess);
							sum += light->intensity * (m.specular * factor);
						}
					}					
				}
			}
			
			return ambient + ((sum / areaLight->samples) * intensity);
		}
		else
		{
			// POINT LIGHTS
			// 
			// find the direction to the light source
			Vector4 lightV = normalize(light->position - p);

			// lightDotNormal represents the cosine of the angle betwen
			// the light vector and the normal vector. A negative number 
			// means the light is on the other side of the surface
			double lightDotNormal = lightV.dot(normalV);
			if (lightDotNormal < 0.0)
			{
				diffuse = Color(0.0, 0.0, 0.0);
				specular = Color(0.0, 0.0, 0.0);
			}
			else
			{
				// compute the diffuse contribution
				diffuse = effectiveColor * m.diffuse * lightDotNormal;

				// reflectDotEye represents the cosine of the angle between the reflection
				// vector and the eye vector. A negative number means the light reflects 
				// away from the eye				
				Vector4 negLightV = -lightV;
				Vector4 reflectV = negLightV.reflect(normalV);
				double reflectDotEye = dot(reflectV, eye);
				if (reflectDotEye <= 0.0)
				{
					specular = Color(0.0);
				}
				else
				{
					// compute specular contribution
					double factor = std::pow(reflectDotEye, m.shininess);
					specular = light->intensity * (m.specular * factor);
				}
			}

			diffuse *= intensity;
			specular *= intensity;
			
			return ambient + diffuse + specular;
		}
	}

	void renderThreadFunc(Camera& camera, World& world, int width, int startY, int endY, Color* data)
	{
		std::map<std::string, Matrix4x4&> cacheInverses;
		std::vector<std::shared_ptr<Intersection>> intersections{};
		intersections.reserve(1000);

		// setup uniform distributed random number generator
		std::mt19937_64 rng;
		uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count(); // initialize the random number generator with time-dependent seed
		std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
		rng.seed(ss);
		std::uniform_real_distribution<double> unif(0, 1); // initialize a uniform distribution between 0 and 1

		int height = endY - startY;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int yy = startY + y;

				Color c;
				if (ANTI_ALIASING)
				{
					for (int i = 0; i < MAX_SAMPLES; i++)
					{
						double sx = x + (unif(rng));
						double sy = yy + (unif(rng));

						Ray r = camera.rayForPixel(sx, sy);
						c += world.colorAt(r, MAX_RECURSION, intersections);

					}

					c /= MAX_SAMPLES;
				}
				else
				{
					Ray r = camera.rayForPixel(x, yy);
					c = world.colorAt(r, MAX_RECURSION, intersections);
				}



				data[x + y * width] = c;

				intersections.clear();

				processedPixelsCount++;
			}
		}
	}

	void threadProgressBarFunc(int totalPixels, bool progressBarIsVisible)
	{
		if (!progressBarIsVisible) return;

		while (processedPixelsCount < totalPixels && !processingDone)
		{
			showProgressBar((double)(processedPixelsCount) / (double)totalPixels);
		}

		showProgressBar(1);
	}

	std::vector<Color*> renderMultiThread(Camera& camera, World& world, bool progressBarIsVisible, int numThreads)
	{
		int totalPixels = (int)(camera.hSize * camera.vSize);

		std::vector<std::thread> threads;
		std::vector<Color*> datas;

		// set up and kick off threads
		int yStart = 0;
		int yStep = (int)camera.vSize / numThreads;
		for (int i = 0; i < numThreads; i++)
		{
			Color* data = new Color[(int)camera.hSize * yStep];
			datas.push_back(data);

			int yEnd = yStart + yStep > camera.vSize ? yEnd = camera.vSize : yStart + yStep;
			std::thread t(renderThreadFunc, std::ref(camera), std::ref(world), (int)camera.hSize, yStart, yEnd, data);

			threads.push_back(std::move(t));

			yStart += yStep;
		}

		// progress bar thread
		std::thread progBarThread(threadProgressBarFunc, totalPixels, progressBarIsVisible);

		// wait for threads to finish working			
		for (std::thread& th : threads)
		{
			if (th.joinable())
			{
				th.join();
			}
		}

		processingDone = true;
		progBarThread.join();

		processedPixelsCount = 0;
		processingDone = false;

		return datas;
	}
}
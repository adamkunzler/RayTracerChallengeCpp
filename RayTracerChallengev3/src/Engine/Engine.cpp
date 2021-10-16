#ifndef HEADERS_H
#include "../Headers.h"
#endif

std::atomic<int> processedPixelsCount;
std::atomic<bool> processingDone;

namespace RayTracer
{		
	struct IPattern;
	
	Color phong(const PointLight& light, const Material& m, const IShape& shape, const Vector4& p, const Vector4& eye, const Vector4& normalV, bool inShadow)
	{
		Color ambient;
		Color diffuse;
		Color specular;

		Color baseColor = m.color;

		if (m.pattern)
		{
			baseColor = m.pattern->patternAt(shape, p);
		}

		// combine surface color with lights color/intensity
		Color effectiveColor = light.intensity * baseColor;

		// find the direction to the light source
		Vector4 lightV = normalize(light.position - p);

		// compute the ambient contriubtion
		ambient = effectiveColor * m.ambient;
		if (inShadow)
		{
			// skip diffuse and specular if in shadow
			return ambient;
		}

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
				specular = light.intensity * (m.specular * factor);
			}
		}
		
		//return diffuse;		
		return ambient + diffuse + specular;
	}

	void renderThreadFunc(Camera& camera, World& world, int width, int startY, int endY, Color* data)
	{
		std::map<std::string, Matrix4x4&> cacheInverses;		
		std::vector<std::shared_ptr<Intersection>> intersections{};
		intersections.reserve(1000);

		int height = endY - startY;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int yy = startY + y;
				Ray r = camera.rayForPixel(x, yy);
				Color c = world.colorAt(r, MAX_RECURSION, intersections);
				data[x + y * width] = c;

				/*for (auto p : intersections) {					
					delete p;
					p = 0;
				}*/
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
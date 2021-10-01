#pragma once

#include <thread>

#include "../DataStructs/Color.h"
#include "../DataStructs/Vector4.h"
#include "Camera.h"
#include "Canvas.h"
#include "World.h"
#include "../Geometry/Material.h"
#include "../Geometry/PointLight.h"
#include "../Geometry/Ray.h"
#include "../Shapes/IShape.h"
#include "../Patterns/IPattern.h"

namespace RayTracer
{	
	// TODO - probably bad that this is global
	std::atomic<int> processedPixelsCount;
	std::atomic<bool> processingDone;

	Canvas render(const Camera& camera, const World& world)
	{
		auto start1 = std::chrono::high_resolution_clock::now();

		Canvas image((int)camera.hSize, (int)camera.vSize);

		int totalPixels = (int)(camera.vSize * camera.hSize);
		int processedPixels = 0;

		for (int y = 0; y < camera.vSize; y++)
		{
			for (int x = 0; x < camera.hSize; x++)
			{
				Ray r = camera.rayForPixel(x, y);
				Color c = world.colorAt(r, MAX_RECURSION);
				image.setPixel(x, y, c);

				processedPixels++;				
			}
			showProgressBar((float)processedPixels / (float)totalPixels);
		}
		showProgressBar(1);

		auto stop1 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
		std::cout << "\n\nrender() completed in " << duration1.count() << "ms.";

		return image;
	}

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
		float lightDotNormal = dot(lightV, normalV);
		if (lightDotNormal < 0.0f)
		{
			diffuse = Color(0.0f, 0.0f, 0.0f);
			specular = Color(0.0f, 0.0f, 0.0f);
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
			float reflectDotEye = dot(reflectV, eye);
			if (reflectDotEye <= 0.0f)
			{
				specular = Color(0.0f);
			}
			else
			{
				// compute specular contribution
				float factor = std::pow(reflectDotEye, m.shininess);
				specular = light.intensity * (m.specular * factor);
			}
		}
		
		return ambient + diffuse + specular;;
	}

	void renderThreadFunc(Camera& camera, World& world, int width, int startY, int endY, Color* data)
	{
		int height = endY - startY;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int yy = startY + y;
				Ray r = camera.rayForPixel(x, yy);
				Color c = world.colorAt(r, MAX_RECURSION);
				data[x + y * width] = c;

				processedPixelsCount++;
			}
		}
	}

	void threadProgressBarFunc(int totalPixels)
	{
		//int modVal = 100;
		while (processedPixelsCount < totalPixels && !processingDone)
		{
			//if (processedPixelsCount % modVal == 0)
			//{
			showProgressBar((float)processedPixelsCount / (float)totalPixels);
			//}
		}
		
		showProgressBar(1);
	}

	Canvas renderMultiThread(Camera& camera, World& world, int numThreads = 16)
	{
		auto start1 = std::chrono::high_resolution_clock::now();

		int totalPixels = (int)(camera.hSize * camera.vSize);

		std::vector<std::thread> threads;
		std::vector<Color*> datas;

		// set up and kick off threads
		int yStart = 0;
		int yStep = (int)camera.vSize / numThreads;
		for (int i = 0; i < numThreads; i++)
		{
			//std::cout << "\n Creating thread...\n";
			//std::cout << "\n yStart: " << yStart << "\t yStep: " << yStep
			Color* data = new Color[(int)camera.hSize * yStep];
			int yEnd = yStart + yStep > camera.vSize ? yEnd = camera.vSize : yStart + yStep;
			std::thread t(renderThreadFunc, std::ref(camera), std::ref(world), (int)camera.hSize, yStart, yEnd, data);

			threads.push_back(std::move(t));
			datas.push_back(data);

			yStart += yStep;
		}

		// progress bar thread
		std::thread progBarThread(threadProgressBarFunc, totalPixels);

		// wait for threads to finish working	
		for (std::thread& th : threads)
		{
			if (th.joinable())
				th.join();
		}
		
		processingDone = true;
		progBarThread.join();

		// concat data from each thread into single data structure
		Canvas image((int)camera.hSize, (int)camera.vSize);
		int index = 0;
		for (int i = 0; i < datas.size(); i++) // each threads data
		{
			for (int j = 0; j < camera.hSize * yStep; j++) // each color in each data
			{
				image.setPixel(index, datas[i][j]);
				index++;
			}
		}

		auto stop1 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
		std::cout << "\nrender() completed in " << duration1.count() << "ms.";

		return image;
	}
}
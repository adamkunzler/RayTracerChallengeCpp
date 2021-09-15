#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "Utils.h"
#include "Color.h"

namespace RayTracer
{
	class Canvas
	{
	public:
		Canvas(int lWidth, int lHeight) : width(lWidth), height(lHeight), maxIndex(lWidth * lHeight - 1)
		{
			pixels = new Color[width * height];
						
			// set all pixels to black
			Color black(0, 0, 0);
			fillCanvas(black);			
		}
		
		const void fillCanvas(const Color& color)
		{
			for (int i = 0; i < width * height; i++)
			{
				pixels[i] = color;
			}
		}

		const int getWidth() { return width; }
		const int getHeight() { return height; }

		const Color pixelAt(const int index)
		{
			int i = index;
			if (index < 0) i = 0;
			if (index > maxIndex) i = maxIndex;

			return pixels[i];
		}

		const Color pixelAt(const int x, const int y)
		{
			return pixelAt(x + y * getWidth());
		}

		const void setPixel(const int index, const Color& color)
		{
			int i = index;
			if (index < 0) i = 0;
			if (index > maxIndex) i = maxIndex;

			pixels[i] = color;
		}

		const void setPixel(const int x, const int y, const Color& color)
		{
			setPixel(x + y * width, color);
		}

		//
		// Write out the pixel data to a string in PPM format
		// 
		// PPM "plain"
		//
		const std::string toPPM()
		{
			std::ostringstream ss;
			
			//
			// write out the header
			//

			// P3 - magic number / identifier
			ss << "P3\n";

			// width height
			ss << width << " " << height << "\n";

			// maximum color value
			ss << "255\n";

			//
			// write out the pixel data
			//

			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					const int index = x + y * width;
					Color c = pixelAt(index);
					
					const int r = std::clamp((int)(c.r * 256.0f), 0, 255);
					const int g = std::clamp((int)(c.g * 256.0f), 0, 255);
					const int b = std::clamp((int)(c.b * 256.0f), 0, 255);

					ss << r << " " << g << " " << b << " ";
				}

				ss << "\n";
			}

			// end file with newline
			ss << "\n";

			std::string ppm = ss.str();			
			return ppm;
		}

		//
		// writes out the PPM data to a file
		//
		const void toPPM(const std::string& filename)
		{
			std::string data(toPPM());
			std::ofstream stream(filename, std::ios::out);
						
			stream << data;
			
			stream.close();
		}

	private:
		const int width;
		const int height;
		const int maxIndex;
		Color* pixels;
	};
}
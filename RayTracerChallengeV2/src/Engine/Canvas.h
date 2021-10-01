#pragma once

namespace RayTracer
{
	class Canvas
	{
	private:
		const int width;
		const int height;
		const int maxIndex;
		//Color* pixels;
		std::vector<Color> pixels;

	public:
		Canvas(int lWidth, int lHeight) : width(lWidth), height(lHeight), maxIndex(lWidth * lHeight - 1)
		{			
			pixels.reserve(width * height);
						
			// set all pixels to black
			Color black(0, 0, 0);
			fillCanvas(black);			
		}
		
		~Canvas() { }

		const void fillCanvas(const Color& color)
		{
			for (int i = 0; i < width * height; i++)
			{
				pixels.push_back(Color(color));
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
			auto start1 = std::chrono::high_resolution_clock::now();

			const std::string space = " ";

			std::ofstream ss(filename, std::ios::out);			
						
			//
			// write out the header
			//			
			ss << "P3\n";							// P3 - magic number / identifier			
			ss << width << " " << height << "\n";	// width height			
			ss << "255\n";							// maximum color value

			//
			// write out the pixel data
			//
			for (int y = 0; y < height; y++)
			{
				std::string data;
				for (int x = 0; x < width; x++)
				{
					const int index = x + y * width;
					Color c = pixelAt(index);

					const int r = std::clamp((int)(c.r * 256.0f), 0, 255);
					const int g = std::clamp((int)(c.g * 256.0f), 0, 255);
					const int b = std::clamp((int)(c.b * 256.0f), 0, 255);
										
					data.append(std::to_string(r));
					data.append(" ");
					data.append(std::to_string(g));
					data.append(" ");
					data.append(std::to_string(b));
					data.append(" ");
				}
				ss << data;

				ss << "\n";
			}

			// end file with newline
			ss << "\n";

			ss.close();

			auto stop1 = std::chrono::high_resolution_clock::now();
			auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
			std::cout << "\nPPM File Completed in " << duration1.count() << "ms.\n";
		}
	};
}
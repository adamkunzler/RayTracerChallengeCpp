#pragma once

namespace RayTracer
{
	class Canvas
	{
	private:
		const int width;
		const int height;
		const int maxIndex;		
		std::vector<Color> pixels;

	public:
		Canvas(int lWidth, int lHeight) : width(lWidth), height(lHeight), maxIndex(lWidth* lHeight - 1);
		
		~Canvas() { }

		const void fillCanvas(const Color& color);

		const int getWidth();
		const int getHeight();

		const Color pixelAt(const int index);

		const Color pixelAt(const int x, const int y);

		const void setPixel(const int index, const Color& color);

		const void setPixel(const int x, const int y, const Color& color);

		//
		// Write out the pixel data to a string in PPM format
		// 
		// PPM "plain"
		//
		const std::string toPPM();

		//
		// writes out the PPM data to a file
		//		
		const void toPPM(const std::string& filename);
	};
}
#pragma once

#include <iostream>
#include <string>
#include "../src/Tuple.h"
#include "../src/Color.h"
#include "../src/Utils.h"
#include "../src/Canvas.h"

namespace RayTracer
{
	namespace Tests
	{
		bool CreateACanvas_Big()
		{
			Canvas c(1024, 768);

			bool result = c.getWidth() == 1024 && c.getHeight() == 768;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreateACanvas_Big()\n";

			return result;
		}

		bool CreateACanvas_Dimensions()
		{			
			Canvas c(10, 20);
			
			bool result = c.getWidth() == 10 && c.getHeight() == 20;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreateACanvas_Dimensions()\n";

			return result;
		}

		bool CreateACanvas_AllBlack()
		{
			Canvas c(5, 5);

			bool result = true;
			for (int i = 0; i < c.getWidth() * c.getHeight(); i++)
			{
				Color pixel = c.pixelAt(i);
				if (!pixel.isBlack())
				{
					result = false;
					break;
				}
			}

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreateACanvas_AllBlack()\n";

			return result;
		}

		bool CanvasSetPixelByXY()
		{
			Canvas c(10, 20);
			Color red(1, 0, 0);
			
			c.setPixel(5, 3, red);

			Color p = c.pixelAt(5, 3);
			bool result = p == red;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreateACanvas_Dimensions()\n";

			return result;
		}

		bool CanvasSetPixelByIndex()
		{
			Canvas c(10, 20);
			Color red(1, 0, 0);

			c.setPixel(5, 3, red);

			Color p = c.pixelAt(5, 3);
			bool result = p == red;

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CreateACanvas_Dimensions()\n";

			return result;
		}

		bool CanvasToPPM_Header()
		{
			Canvas c(1, 1);

			std::string ppm = c.toPPM();

			bool result = ppm == "P3\n1 1\n255\n0 0 0 \n\n";

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CanvasToPPM_Header()\n";

			return result;
		}

		bool CanvasToPPM_PixelData()
		{
			Canvas c(5, 3);
			Color c1(1.5, 0, 0);
			Color c2(0, 0.5, 0);
			Color c3(-0.5, 0, 1);

			std::cout << "c2 normalize: " << c2.normalize() << std::endl;

			c.setPixel(0, 0, c1);
			c.setPixel(2, 1, c2);
			c.setPixel(4, 2, c3);

			std::string ppm = c.toPPM();
			std::cout << ppm << std::endl;

			// TODO
			// c2 should be 128
			// c3 should be 255


			bool result = ppm == "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n\n";

			std::string pf = (result) ? "PASS" : "FAIL";
			std::cout << pf << "\t" << "CanvasToPPM_PixelData()\n";

			return result;
		}
	}
}
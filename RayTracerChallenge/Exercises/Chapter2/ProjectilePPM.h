#pragma once

#include <iostream>
#include "../../src/Color.h"
#include "../../src/Canvas.h"
#include "../../src/Utils.h"
#include "../../src/Tuple.h"
#include "../../src/Point.h"
#include "../../src/Vector.h"

namespace Exercises
{
	namespace Chapter2
	{
		class Projectile
		{
		public:
			RayTracer::Point position;
			RayTracer::Vector velocity;
			RayTracer::Vector gravity;
			RayTracer::Vector wind;

		public:
			Projectile(RayTracer::Point lPosition, RayTracer::Vector lVelocity, RayTracer::Vector lGravity, RayTracer::Vector lWind)
			{
				position = lPosition;
				velocity = lVelocity;
				gravity = lGravity;
				wind = lWind;
			}

			void update()
			{
				velocity += gravity + wind;
				position += velocity;
			}
		};

		void ProjectilePPM()
		{			
			std::cout << "\nProjectile PPM\n";

			RayTracer::Canvas canvas(900, 550);

			RayTracer::Color color = RayTracer::Color::fromRGB(29,153,24);

			RayTracer::Point position(0.0f, 1.0f, 0.0f);
			RayTracer::Vector velocity(1.0f, 1.8f, 0.0f);
			RayTracer::Vector gravity(0.0f, -0.1f, 0.0f);
			RayTracer::Vector wind(-0.04f, 0.0f, 0.0f);
			
			velocity = velocity.normalize() * 11.25;

			Projectile p(
				position,
				velocity,
				gravity,
				wind
			);

			int i = 0;
			while(p.position.y > 0)
			{
				p.update();

				// get position of projectile in screen coords
				int x = (int)p.position.x;
				int y = canvas.getHeight() - (int)p.position.y;

				// make sure coords are within bounds
				if (x < 0)
				{
					x = 0;
				}
				else if (x > canvas.getWidth() - 1)
				{
					x = canvas.getWidth() - 1;
				}
				
				if (y < 0)
				{
					y = 0;
				}
				else if (y > canvas.getHeight() - 1)
				{
					y = canvas.getHeight() - 1;
				}

				canvas.setPixel(x, y, color);

				std::cout << "#" << i++ << "\t" << p.position << std::endl;
			}

			canvas.toPPM("images/chapter2.ppm");
		}
	}
}
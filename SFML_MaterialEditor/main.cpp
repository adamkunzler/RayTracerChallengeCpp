#include <SFML/Graphics.hpp>
#include "..\RayTracerChallengev3\src\Headers.h"

//int main()
//{
//	std::cout << "\n----------------- Ray Tracer Material Editor -----------------\n";
//	
//	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
//	return 0;
//}
void buildScene(const int width, const int height);

std::unique_ptr<sf::Uint8[]> pixels;

int main()
{
	std::cout << "\n----------------- Ray Tracer Material Editor -----------------\n";

	const int width = 512/4;
	const int height = 512/4;
	const float scale = 3.0f;
	
	pixels = std::unique_ptr< sf::Uint8[] >(new sf::Uint8[width * height * 4]);
	buildScene(width, height);

	sf::Texture texture;
	texture.create(width, height);	
	sf::Sprite sprite(texture);
	sprite.setScale(scale, scale);

    sf::RenderWindow window(sf::VideoMode(width * scale, height * scale), "Material Editor v1");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{				
				buildScene(width, height);
			}
        }

        window.clear();  
				
		texture.update(pixels.get());
		window.draw(sprite);
        
		window.display();
    }

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    return 0;
}

void buildScene(const int width, const int height)
{
	auto start = std::chrono::high_resolution_clock::now();

	RayTracer::SceneConfig config;

	// dimensions and fov
	config.width = width;
	config.height = height;
	config.fov = PI / 2.7;

	// camera
	config.from = RayTracer::Point4(0.0, 1.75, -2.75);
	config.to = RayTracer::Point4(0.0, 1.0, 0.0);
	config.up = RayTracer::Vector4(0.0, 1.0, 0.0);

	RayTracer::Scene scene(config);	

	// add the lights
	scene.addLight(RayTracer::PointLight(
		RayTracer::Point4(-5.0, 10.0, -5.0),
		RayTracer::Color(0.9)
	));

	{
		RayTracer::Color checkerColor1(0.99);
		RayTracer::Color checkerColor2(0.95);

		// checkered plane
		RayTracer::Plane* floor = new RayTracer::Plane();
		RayTracer::CheckerPattern* floorPattern = new RayTracer::CheckerPattern(checkerColor1, checkerColor2);
		floor->material.pattern = floorPattern;
		floor->material.ambient = 0.1f;
		scene.addShape(floor);

		RayTracer::Plane* backWall = new RayTracer::Plane();
		backWall->material.color = checkerColor2;
		backWall->material.reflective = 0.0;
		backWall->material.ambient = 0.1f;
		backWall->material.specular = 0.0f;
		backWall->setTransform(RayTracer::translation(0.0, 0.0, 7.0) * RayTracer::xRotation4x4(-PI / 2));
		scene.addShape(backWall);

		RayTracer::Sphere* sphere = new RayTracer::Sphere();
		sphere->setTransform(RayTracer::translation(0.0, 1.0, 0.0));
		sphere->material.color = RayTracer::rgb(168, 137, 201);
		sphere->material.specular = 0.3;
		sphere->material.shininess = 50.0;
		sphere->material.diffuse = 0.9;
		sphere->material.ambient = 0.1;
		scene.addShape(sphere);
	}

	// render the scene
	std::vector<RayTracer::Color> rtPixels;
	rtPixels.reserve(config.width * config.height);
	scene.render(rtPixels);
	
	//scene.renderToPPM("../_images/godDamn");

	// convert scene to array of sf:Uint8		
	unsigned int i = 0;
	for (auto &pixel : rtPixels)
	{			
		int r = std::clamp((int)(pixel.r * 256.0), 0, 255);
		int g = std::clamp((int)(pixel.g * 256.0), 0, 255);
		int b = std::clamp((int)(pixel.b * 256.0), 0, 255);
		sf::Color c(r, g, b);
		
		pixels[i] = c.r;
		pixels[i+1] = c.g;
		pixels[i+2] = c.b;
		pixels[i+3] = 255;
		i += 4;		
	}	

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	long long durationCount = duration.count();	
	std::cout << "\n scene is built\t" << durationCount << "ms";
}
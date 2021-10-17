#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "..\RayTracerChallengev3\src\Headers.h"

// for setting up IMGUI
//https://eliasdaler.github.io/using-imgui-with-sfml-pt1/

void buildScene(const int width, const int height, const double yRot);
void drawToolsWindow(sf::RenderWindow& window);

std::unique_ptr<sf::Uint8[]> pixels;
char windowTitle[255] = "Ray Tracer Material Editor";


int main()
{
	std::cout << "\n----------------- Ray Tracer Material Editor -----------------\n";

	const int width = 512;
	const int height = 512;
	const float scale = 3.0f;

	double yRot = 0.01;
	bool transformEnabled = false;
	
	pixels = std::unique_ptr< sf::Uint8[] >(new sf::Uint8[width * height * 4]);
	buildScene(width, height, yRot);

	sf::Texture texture;
	texture.create(width, height);	
	sf::Sprite sprite(texture);
	sprite.setScale(scale, scale);

    sf::RenderWindow window(sf::VideoMode(width * scale, height * scale), "Material Editor v1");
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{				
				transformEnabled = !transformEnabled;
			}
        }

		ImGui::SFML::Update(window, deltaClock.restart());

		//drawToolsWindow(window);

		ImGui::ShowDemoWindow();

        window.clear();  
		
		if (transformEnabled)
		{
			yRot += 0.05;
			if (yRot > PI * 2.0) yRot = 0.0;
		}

		buildScene(width, height, yRot);
		texture.update(pixels.get());
		window.draw(sprite);
        
		ImGui::SFML::Render(window);

		window.display();
    }

	ImGui::SFML::Shutdown();

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    return 0;
}

void buildScene(const int width, const int height, const double yRot)
{
	auto start = std::chrono::high_resolution_clock::now();

	RayTracer::SceneConfig config;

	// dimensions and fov
	config.width = width;
	config.height = height;
	config.fov = PI / 2.7;

	// camera
	config.from = RayTracer::Point4(0.0, 1.75, -3.25) * RayTracer::yRotation4x4(yRot);
	config.to = RayTracer::Point4(0.0, 1.0, 0.0);
	config.up = RayTracer::Vector4(0.0, 1.0, 0.0);

	RayTracer::Scene scene(config);	

	//scene.camera->setTransform();

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

		RayTracer::Sphere* glassSphere = new RayTracer::Sphere();
		glassSphere->setTransform(RayTracer::translation(2.0, 1.0000001, 0.0) * RayTracer::scaling(0.5, 0.5, 0.5));
		glassSphere->material = RayTracer::metal(glassSphere->material);
		scene.addShape(glassSphere);

		RayTracer::Sphere* metalSphere = new RayTracer::Sphere();
		metalSphere->setTransform(RayTracer::translation(-2.0, 1.0000001, 0.0) * RayTracer::scaling(0.5, 0.5, 0.5));
		metalSphere->material = RayTracer::metal(metalSphere->material);
		scene.addShape(metalSphere);
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
	//std::cout << "\n scene is built\t" << durationCount << "ms";
}

void drawToolsWindow(sf::RenderWindow& window)
{
	ImGui::Begin("Sample window"); // begin window

	// Window title text edit
	ImGui::InputText("Window title", windowTitle, 255);

	if (ImGui::Button("Update window title")) {
		// this code gets if user clicks on the button
		// yes, you could have written if(ImGui::InputText(...))
		// but I do this to show how buttons work :)
		window.setTitle(windowTitle);
	}
	ImGui::End(); // end window
}
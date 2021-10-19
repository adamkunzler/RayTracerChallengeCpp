#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "..\RayTracerChallengev3\src\Headers.h"

// for setting up IMGUI
//https://eliasdaler.github.io/using-imgui-with-sfml-pt1/

void buildScene(const int width, const int height);
void drawMaterialTools(sf::RenderWindow& window);
void showInfoOverlay();

std::unique_ptr<sf::Uint8[]> pixels;
long long renderTimeMs = 0;

int main()
{		
	int width = 512;
	int height = 512;
	float scale = 2.0f;
			
	pixels = std::unique_ptr< sf::Uint8[] >(new sf::Uint8[width * height * 4]);
		
	buildScene(width, height);

	sf::Texture texture;
	texture.create(width, height);	
	sf::Sprite sprite(texture);
	sprite.setScale(scale, scale);

    sf::RenderWindow window(sf::VideoMode(width * scale, height * scale), "Ray Tracer Material Editor");
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
				buildScene(width, height);
			}
        }

		ImGui::SFML::Update(window, deltaClock.restart());
		
		showInfoOverlay();
		
        window.clear();  
				
		//buildScene(width, height);
		
		texture.update(pixels.get());
		window.draw(sprite);
        
		ImGui::SFML::Render(window);

		window.display();
    }

	ImGui::SFML::Shutdown();

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    return 0;
}

void buildScene(const int width, const int height)
{
	auto start = std::chrono::high_resolution_clock::now();

	RayTracer::SceneConfig config;

	// dimensions and fov
	config.width = width; // 400
	config.height = height; // 160
	config.fov = 0.7854;

	// camera
	config.from = RayTracer::Point4(1.0, 1.0, -3.0);
	config.to = RayTracer::Point4(1.0, 0.5, 0.0);
	config.up = RayTracer::Vector4(0.0, 1.0, 0.0);

	RayTracer::Scene scene(config);	

	//scene.camera->setTransform();

	// add the lights
	/*RayTracer::PointLight* pointLight = new RayTracer::PointLight(
		RayTracer::Point4(-2.0, 2.0, -3.0),
		RayTracer::Color(1.0)
	);
	scene.addLight(pointLight);*/
	
	RayTracer::AreaLight* light = new RayTracer::AreaLight(
		RayTracer::Point4(-3, 1, -1.0),
		RayTracer::Vector4(2, 0, 0), 2,
		RayTracer::Vector4(0, 2, 0), 2,
		RayTracer::Color(1.5, 1.5, 1.5));

	scene.addLight(light);

	// corner (-1, 2, 4)
	// uvec (2, 0, 0)
	// vvec (0, 2, 0)
	// usteps 10
	// vsteps 10
	// jitter true
	// intensity (1.5, 1.5, 1.5)

	/*
	{
		RayTracer::Cube* theLight = new RayTracer::Cube();
		theLight->material.color = RayTracer::Color(1.5, 1.5, 1.5);
		theLight->material.ambient = 1;
		theLight->material.diffuse = 0;
		theLight->material.specular = 0;
		theLight->setTransform(RayTracer::translation(0, 3, 4) * RayTracer::scaling(1, 1, 0.01));
		theLight->hasShadow = false;
		scene.addShape(theLight);

		RayTracer::Plane* floor = new RayTracer::Plane();
		floor->material.color = RayTracer::Color(1, 1, 1);
		floor->material.ambient = 0.025;
		floor->material.diffuse = 0.67;
		floor->material.specular = 0;
		scene.addShape(floor);

		RayTracer::Sphere* bigSphere = new RayTracer::Sphere();
		bigSphere->material.color = RayTracer::Color(1, 0, 0);
		bigSphere->material.ambient = 0.1;
		bigSphere->material.diffuse = 0.6;
		bigSphere->material.reflective = 0.3;
		bigSphere->material.specular = 0;
		bigSphere->setTransform(RayTracer::translation(0.5, 0.5, 0) * RayTracer::scaling(0.5, 0.5, 0.5));
		scene.addShape(bigSphere);

		RayTracer::Sphere* smallSphere = new RayTracer::Sphere();
		smallSphere->material.color = RayTracer::Color(0.5, 0.5, 1);
		smallSphere->material.ambient = 0.1;
		smallSphere->material.diffuse = 0.6;
		smallSphere->material.reflective = 0.3;
		smallSphere->material.specular = 0;
		smallSphere->setTransform(RayTracer::translation(-0.25, 0.33, 0) * RayTracer::scaling(0.33, 0.33, 0.33));
		//smallSphere->hasShadow = false;
		scene.addShape(smallSphere);
	}
	*/

	{
		RayTracer::Plane* floor = new RayTracer::Plane();
		floor->material.color = RayTracer::Color(1, 1, 1);
		floor->material.ambient = 0.025;
		floor->material.diffuse = 0.67;
		floor->material.specular = 0;
		scene.addShape(floor);

		RayTracer::Sphere* bigSphere = new RayTracer::Sphere();
		bigSphere->material.color = RayTracer::Color(0.2, 0, 0.9);
		bigSphere->material.ambient = 0.1;
		bigSphere->material.diffuse = 0.8;
		bigSphere->material.reflective = 0.1;
		bigSphere->material.specular = 0.1;
		bigSphere->setTransform(RayTracer::translation(0, 0.5, 0) * RayTracer::scaling(0.5, 0.5, 0.5));		
		scene.addShape(bigSphere);
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
	renderTimeMs = duration.count();	
	//std::cout << "\n scene is built\t" << durationCount << "ms";
}


void showInfoOverlay()
{	
	
	bool p_open = true;
	static int corner = 1;
	
	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 2.5f;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
	{
		const float PAD = 10.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
		window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
		window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
		window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		window_flags |= ImGuiWindowFlags_NoMove;
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Info Overlay", &p_open, window_flags))
	{		
		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		//ImGui::Separator();
		ImGui::Text("Last Render Time %dms (%.1fs)", renderTimeMs, renderTimeMs / 1000.0f);
		//ImGui::Separator();
		/*if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) p_open = false;
			ImGui::EndPopup();
		}*/
	}
	ImGui::End();	
}

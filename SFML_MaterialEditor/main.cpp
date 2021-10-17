#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "..\RayTracerChallengev3\src\Headers.h"

// for setting up IMGUI
//https://eliasdaler.github.io/using-imgui-with-sfml-pt1/

void buildScene(const int width, const int height, const double yRot);
void drawMaterialTools(sf::RenderWindow& window);
void showInfoOverlay();

std::unique_ptr<sf::Uint8[]> pixels;
bool rotateSceneEnabled = false;

float materialAmbient = 0.1f;
float materialDiffuse = 0.9f;
float materialSpecular = 0.3f;
int materialShininess = 50;
float materialReflective = 0.0f;
float materialTransparency = 0.0f;
float materialRefractiveIndex = 0.0f;
ImVec4 materialColor(168.0f / 255.0f, 137.0f / 255.0f, 201.0f / 255.0f, 1.0f);

int main()
{
	std::cout << "\n----------------- Ray Tracer Material Editor -----------------\n";

	const int width = 512;
	const int height = 512;
	const float scale = 3.0f;

	double yRot = 0.01;
		
	pixels = std::unique_ptr< sf::Uint8[] >(new sf::Uint8[width * height * 4]);
	buildScene(width, height, yRot);

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
        }

		ImGui::SFML::Update(window, deltaClock.restart());

		drawMaterialTools(window);
		showInfoOverlay();
		ImGui::ShowDemoWindow();
		//ImGui::ShowMetricsWindow();

        window.clear();  
		
		if (rotateSceneEnabled)
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
		sphere->material.color = RayTracer::Color(materialColor.x, materialColor.y, materialColor.z);
		sphere->material.ambient = materialAmbient;
		sphere->material.diffuse = materialDiffuse;
		sphere->material.specular = materialSpecular;
		sphere->material.shininess = materialShininess;
		sphere->material.reflective = materialReflective;
		sphere->material.transparency = materialTransparency;
		sphere->material.refractiveIndex = materialRefractiveIndex;
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

void drawMaterialTools(sf::RenderWindow& window)
{
	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 2.5f;
	bool p_open = true;

	ImGui::Begin("Material Window", &p_open, ImGuiWindowFlags_AlwaysAutoResize);
	
	if (ImGui::Button("Rotate Scene")) {
		rotateSceneEnabled = !rotateSceneEnabled;
	}

	ImGuiColorEditFlags misc_flags = 0;	
	ImGui::ColorEdit3("Color", (float*)&materialColor, misc_flags);

	static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
	ImGui::SliderFloat("Ambient", &materialAmbient, 0.0f, 1.0f, "%.3f", flags);
	ImGui::SliderFloat("Diffuse", &materialDiffuse, 0.0f, 1.0f, "%.3f", flags);
	ImGui::SliderFloat("Specular", &materialSpecular, 0.0f, 1.0f, "%.3f", flags);
	ImGui::SliderInt("Shininess", &materialShininess, 10, 350, "%d", flags);
	ImGui::SliderFloat("Reflective", &materialReflective, 0.0f, 1.0f, "%.3f", flags);
	ImGui::SliderFloat("Transparency", &materialTransparency, 0.0f, 1.0f, "%.3f", flags);
	ImGui::SliderFloat("Refractive Index", &materialRefractiveIndex, 1.0f, 2.5f, "%.3f", flags);

	ImGui::End();
}

void showInfoOverlay()
{
	bool p_open = true;
	static int corner = 1;
	ImGuiIO& io = ImGui::GetIO();
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
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
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
		}
	}
	ImGui::End();	
}
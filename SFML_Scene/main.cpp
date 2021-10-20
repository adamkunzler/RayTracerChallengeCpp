#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "..\RayTracerChallengev3\src\Headers.h"
#include "scenes\scenes.h"

// for setting up IMGUI
//https://eliasdaler.github.io/using-imgui-with-sfml-pt1/

void buildScene(const int width, const int height);
void drawMaterialTools(sf::RenderWindow& window);
void showInfoOverlay();

std::unique_ptr<sf::Uint8[]> pixels;
long long renderTimeMs = 0;

int main()
{		
	int width = 320;
	int height = 240;
	float scale = 6.0f;
			
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

	//RayTracer::Scene scene = sceneSoftShadows(width, height);
	RayTracer::Scene scene = sceneBenchmark(width, height);
	
	//scene.renderToPPM("../_images/softShadows");

	// render the scene
	std::vector<RayTracer::Color> rtPixels;
	rtPixels.reserve(width * height);
	scene.render(rtPixels);
		
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
}


void showInfoOverlay()
{		
	bool p_open = true;
	static int corner = 1;
	
	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 1.5f;

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
		ImGui::Text("Last Render Time %dms (%.1fs)", renderTimeMs, renderTimeMs / 1000.0f);		
	}
	ImGui::End();	
}

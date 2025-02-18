#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "editor/EditorSettings.h"
#include "editor/ui/EditorUIComponent.h"
#include "editor/ui/MenuBar.h"
#include "editor/ui/FileBrowser.h"
#include "editor/ui/EditorConsole.h"

#include "core/Icarus.hpp"
#include "core/HeliosWindow.h"
#include "core/InputContext.h"

//editor ui instantiation
static Editor::MenuBar menuBar;
static Editor::FileBrowser fileBrowser;
static Editor::EditorConsole console;


int main(int argc, char** argv) 
{
	//
	//Editor Config
	//
	Editor::EditorSettings editor_state;
	print("Loading editor state...");
	if (editor_state.loadFromFile("engine_config.json")) {
		print("Success!");
	}
	else {
		print("Failed to load editor state. Missing engine_config.json?");

		print("Creating engine config...");

		editor_state.windowWidth = 1280;
		editor_state.windowHeight = 720;
		editor_state.fullscreen = true;

		// Save engine state
		if (editor_state.saveToFile("engine_config.json"))
		{
			print("Success!");

		}
	}
	if (argc > 1 && std::string(argv[1]) == "--editor") {
		g_IsEditor = true;
	}

	//
	//sfmc
	//
	HeliosWindow* main = new HeliosWindow(sf::Vector2<unsigned int>(editor_state.windowWidth, editor_state.windowHeight), 60);

	main->InitializeWindow();

	if (g_IsEditor)
	{
		ImGui::SFML::Init(main->GetSFWindow());
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}

	//print("loop started!");
	sf::Clock clock;
	sf::Time delta_clock_time;
	float delta_time;
	bool first_frame = true;
	while (main->GetSFWindow().isOpen())
	{
		if (first_frame)
		{
			first_frame = false;
		}

		delta_clock_time = clock.restart();
		delta_time = delta_clock_time.asSeconds();


		while (const std::optional event = main->GetSFWindow().pollEvent())
		{
			ImGui::SFML::ProcessEvent(main->GetSFWindow(), *event);

			if (event->is<sf::Event::Closed>())
			{
				main->GetSFWindow().close();
			}
		}
		//Update Keys to InputContext
		InputContext::GetInstance().Update();

		if (InputContext::GetInstance().IsKeyDown(sf::Keyboard::Key::Escape) && g_IsEditor)
		{
			main->GetSFWindow().close();
		}

		//
		//RENDER
		//
		//ImGui
		ImGui::SFML::Update(main->GetSFWindow(), clock.restart());

		//Editor UI Drawing
		Editor::EditorUIComponent::RenderComponents();
		
		main->StartDraw();
		
		ImGui::SFML::Render(main->GetSFWindow());

		main->EndDraw();
		
	}

	ImGui::SFML::Shutdown();
	delete main->p_SFWindow;
	

	return 0;
}
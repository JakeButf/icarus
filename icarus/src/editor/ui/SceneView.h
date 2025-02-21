#pragma once
#include <cstdint>

#include "editor/ui/EditorUIComponent.h"
#include "core/HeliosWindow.h"
#include "imgui.h"
#include <SFML/Graphics/Texture.hpp>

// SceneView.h
//
// Renders the game scene into an ImGui Window using an SFML render texture.
namespace Editor
{
	class SceneView : public EditorUIComponent
	{
	public:
		SceneView(HeliosWindow* window) : m_Window(window)
		{ }

        virtual void Render() override {
            ImGui::Begin("Scene View");

            if (m_Window)
            {
                const sf::Texture* texture = m_Window->GetSceneTexture();
                if (texture) 
                {
                    ImTextureID texId = (ImTextureID)(static_cast<uintptr_t>(texture->getNativeHandle()));
                    ImGui::Image(texId, ImGui::GetContentRegionAvail());
                }
                else 
                {
                    ImGui::Text("Scene texture not available.");
                }
            }
            else 
            {
                ImGui::Text("HeliosWindow pointer not set.");
            }

            ImGui::End();
        }

	private:
		HeliosWindow* m_Window;
	};
}
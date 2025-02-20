#pragma once

#include "imgui.h"

//EditorLayout.h
//
// Handles overall editor layouts, mostly related to docking imgui elements.
namespace Editor
{
	class EditorLayout
	{
	public:
		static void BeginLayout()
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoBringToFrontOnFocus |
				ImGuiWindowFlags_NoNavFocus;

			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);

			//This must be set in order to allow for a full dockspace
			window_flags != ImGuiWindowFlags_NoDocking;

			//Remove styling to give the illusion of a full window
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGui::Begin("Layout", nullptr, window_flags);

			ImGui::PopStyleVar(3);

			ImGuiID layout_id = ImGui::GetID("DockSpace");
			ImGui::DockSpace(layout_id, ImVec2(0.0f, 0.0f));
		}

		static void EndLayout()
		{
			ImGui::End();
		}
	};
}
#pragma once

#include "../core/Icarus.hpp"

#include "imgui.h"
#include "EditorUIComponent.h"
#include "FileBrowser.h"
#include "../editor/EditorSettings.h"

static Editor::FileBrowser fileDialog(Editor::FileBrowser::Mode::DIALOG, Editor::FileBrowser::SelectionType::DIRECTORY, "Open Directory");
static Editor::FileBrowser openFileDialog(Editor::FileBrowser::Mode::DIALOG, Editor::FileBrowser::SelectionType::FILE, "Open File Dialog");

// MenuBar.h
//
// Editor Class
// Renders the top menu bar to the engine.
namespace Editor 
{
	class MenuBar : public EditorUIComponent
	{
	public:
        MenuBar() = default;
		void Render() override
		{
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {

                    if (ImGui::MenuItem("New Project", "Ctrl+Shift+N")) 
                    {
                        NewProject();
                    }

                    if (ImGui::MenuItem("Save Project", "Ctrl+Shift+S")) 
                    {
                        // Handle Save action
                    }

                    if (ImGui::MenuItem("Open Project", "Ctrl+Shift+O"))
                    {
                        OpenProject();
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
                        // Handle Open action
                    }
                    
                    if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {
                        // Handle Exit action
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Edit")) {
                    if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
                        // Handle Undo action
                    }
                    if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
                        // Handle Redo action
                    }
                    ImGui::Separator();
                    if (ImGui::MenuItem("Cut", "Ctrl+X")) {
                        // Handle Cut action
                    }
                    if (ImGui::MenuItem("Copy", "Ctrl+C")) {
                        // Handle Copy action
                    }
                    if (ImGui::MenuItem("Paste", "Ctrl+V")) {
                        // Handle Paste action
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Help")) {
                    if (ImGui::MenuItem("About")) {
                        // Handle About action
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }

            if (m_NewProjectActive && fileDialog.HasResult())
            {
                EditorSettings::s_EditorState.CreateProjectDirectory(fileDialog.GetResult());
                m_NewProjectActive = false;
                fileDialog.ClearResult();
            }

            if (m_OpenProjectActive && openFileDialog.HasResult())
            {
                EditorSettings::s_EditorState.OpenProjectDirectory(openFileDialog.GetResult());
                m_OpenProjectActive = false;
                openFileDialog.ClearResult();
            }
		}

        void NewProject()
        {
            fileDialog.OpenDialog("C:\\Users\\");
            m_NewProjectActive = true;
        }

        void OpenProject()
        {
            openFileDialog.OpenDialog("C:\\Users\\");
            m_OpenProjectActive = true;
        }

        void NewScene()
        {
            fileDialog.OpenDialog(EditorSettings::s_EditorState.openProject.projectPath);
        }

    private:
        bool m_NewProjectActive;
        bool m_OpenProjectActive;
	};
}
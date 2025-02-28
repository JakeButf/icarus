#pragma once
#include "EditorUIComponent.h"
#include "ProjectSettings.h"

#include <string>
#include <filesystem>

namespace Editor
{
	class FileBrowser : public EditorUIComponent
	{
	public:
		enum class Mode
		{
			BROWSER,
			DIALOG
		};

        enum class SelectionType
        {
            FILE,
            DIRECTORY
        };

		FileBrowser(Mode mode = Mode::BROWSER, SelectionType selectionType = SelectionType::FILE, const std::string& popupName = "File Dialog") : m_Mode(mode), m_SelectionType(selectionType), m_PopupName(popupName)
		{
			m_RootPath = std::filesystem::current_path();
			m_CurrentPath = m_RootPath;
			m_IsOpen = false;
		}

        void OpenDialog(std::filesystem::path atLocation)
        {
            if (std::filesystem::exists(atLocation) && std::filesystem::is_directory(atLocation))
            {
                m_CurrentPath = atLocation;
            }
            else
            {
                print("Could find path ", atLocation, ". Instead using directory root. Is path valid?");
                m_CurrentPath = std::filesystem::current_path();
            }
            m_Result.clear();
            m_SelectedPath.clear();
            m_IsOpen = true;
        }

        bool HasResult() const
        {
            return !m_Result.empty();
        }

        std::string GetResult() const
        {
            return m_Result;
        }

        void ClearResult()
        {
            m_Result.clear();
        }

		void Render() override
		{
			if (m_Mode == Mode::BROWSER)
			{
				ImGui::Begin("File Browser");
                RenderFileBrowserContent();
				ImGui::End();
			}
            else if (m_Mode == Mode::DIALOG)
            {
                if (m_IsOpen)
                {
                    ImGui::OpenPopup(m_PopupName.c_str());
                    m_IsOpen = false;
                }
                if (ImGui::BeginPopupModal(m_PopupName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    RenderFileBrowserContent();

                    // Show selected file/path
                    if (!m_SelectedPath.empty())
                    {
                        ImGui::Text("Selected: %s", m_SelectedPath.string().c_str());
                    }

                    //Name input
                    if (m_SelectionType == SelectionType::DIRECTORY)
                    {
                        ImGui::InputText("Name", m_NameBuffer, IM_ARRAYSIZE(m_NameBuffer));
                    }

                    ImGui::Separator();

                    // Confirm Selection Button & Name
                    if (!m_SelectedPath.empty())
                    {
                        
                        if (ImGui::Button(m_SelectionType == SelectionType::DIRECTORY ? "Select Directory" : "Select File"))
                        {

                            if (std::strlen(m_NameBuffer) > 0)
                            {
                                m_Result = (m_CurrentPath / std::string(m_NameBuffer)).string();
                            }
                            else if (!m_SelectedPath.empty())
                            {
                                m_Result = m_SelectedPath.string();
                            }
                            else
                            {
                                m_Result = m_CurrentPath.string();
                            }

                            ImGui::CloseCurrentPopup();
                        }
                    }

                    ImGui::SameLine();

                    // Cancel Button
                    if (ImGui::Button("Cancel"))
                    {
                        m_Result.clear();
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }
            }
		}

	private:
        void RenderFileBrowserContent()
        {
            ImGui::Text("Current Path: %s", m_CurrentPath.string().c_str());
            ImGui::Separator();

            std::filesystem::path next_path;

            // If not at the root, display an option to go up one directory.
            if (m_CurrentPath != m_RootPath) 
            {
                if (ImGui::Selectable("..", false)) 
                {
                    m_CurrentPath = m_CurrentPath.parent_path();
                }
            }

            // List directories and files.
            for (const auto& entry : std::filesystem::directory_iterator(m_CurrentPath)) 
            {
                std::string label;
                if (entry.is_directory()) {
                    label = "[D] " + entry.path().filename().string();
                    if (ImGui::Selectable(label.c_str(), false, ImGuiSelectableFlags_DontClosePopups)) {
                        m_SelectedPath = entry.path();
                        next_path = entry.path();
                    }
                }
                else if (m_SelectionType == SelectionType::FILE && entry.is_regular_file())
                {
                    label = entry.path().filename().string();
                    if (ImGui::Selectable(label.c_str(), false, ImGuiSelectableFlags_DontClosePopups))
                    {
                        m_SelectedPath = entry.path();
                    }
                }
            }

            if (!next_path.empty())
            {
                m_CurrentPath = next_path;
            }
        }

        //TODO create success check
        bool CreateProjectDirectory(std::string directory)
        {
            std::filesystem::path fsPath(directory);
            std::string projectName = fsPath.stem().string();
            std::string projectPath = fsPath.parent_path().string();

            std::filesystem::path newProjectDir = std::filesystem::path(projectPath) / projectName;
            if (!std::filesystem::exists(newProjectDir))
            {
                std::filesystem::create_directories(newProjectDir);
            }

            CreateNewProject(projectName, projectPath);

            Editor::EditorSettings::s_EditorState.OpenProject(directory + + "\\" + projectName + ".json");
            return true;
        }

        Mode m_Mode;
        SelectionType m_SelectionType;

        bool m_IsOpen = true;
        bool m_PopupOpened = false;

        char m_NameBuffer[256] = { 0 };
        std::filesystem::path m_RootPath;
        std::filesystem::path m_CurrentPath;
        std::filesystem::path m_SelectedFile;
        std::filesystem::path m_SelectedPath;
        std::string m_Result;
        std::string m_PopupName;
	};
}
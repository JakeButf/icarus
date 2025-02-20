#pragma once
#include "EditorUIComponent.h"

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

		FileBrowser(Mode mode = Mode::BROWSER, SelectionType selectionType = SelectionType::FILE) : m_Mode(mode), m_SelectionType(selectionType)
		{
			m_RootPath = std::filesystem::current_path();
			m_CurrentPath = m_RootPath;
			m_IsOpen = false;
		}

		bool HasResult() const
		{
			return !m_Result.empty();
		}

		std::string GetResult() const
		{
			return m_Result;
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
            ImGui::OpenPopup("File Dialog");
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
                    ImGui::OpenPopup("File Dialog");
                    m_IsOpen = false;
                }
                if (ImGui::BeginPopupModal("File Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    RenderFileBrowserContent();

                    // Show selected file/path
                    if (!m_SelectedPath.empty())
                    {
                        ImGui::Text("Selected: %s", m_SelectedPath.string().c_str());
                    }

                    // Confirm Selection Button
                    if (!m_SelectedPath.empty())
                    {
                        if (ImGui::Button(m_SelectionType == SelectionType::DIRECTORY ? "Select Directory" : "Select File"))
                        {
                            m_Result = m_SelectedPath.string();
                            print("File Dialog Selection: ", m_Result);
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

        Mode m_Mode;
        SelectionType m_SelectionType;

        bool m_IsOpen = true;
        bool m_PopupOpened = false;

        std::filesystem::path m_RootPath;
        std::filesystem::path m_CurrentPath;
        std::filesystem::path m_SelectedFile;
        std::filesystem::path m_SelectedPath;
        std::string m_Result;
	};
}
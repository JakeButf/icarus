#pragma once
#include "EditorUIComponent.h"

#include <string>
#include <filesystem>

namespace Editor
{
	class FileBrowser : EditorUIComponent
	{
	public:
		enum class Mode
		{
			BROWSER,
			DIALOG
		};

		FileBrowser(Mode mode = Mode::BROWSER) : m_Mode(mode)
		{
			m_RootPath = std::filesystem::current_path();
			m_CurrentPath = m_RootPath;
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

		virtual void Render() override
		{
			if (m_Mode == Mode::BROWSER)
			{
				ImGui::Begin("File Browser", &m_IsOpen);
                RenderFileBrowserContent();
				ImGui::End();
			}
		}

	private:
        void RenderFileBrowserContent() {
            ImGui::Text("Current Path: %s", m_CurrentPath.string().c_str());
            ImGui::Separator();

            // If not at the root, display an option to go up one directory.
            if (m_CurrentPath != m_RootPath) {
                if (ImGui::Selectable("..", false)) {
                    m_CurrentPath = m_CurrentPath.parent_path();
                }
            }

            // List directories and files.
            for (const auto& entry : std::filesystem::directory_iterator(m_CurrentPath)) {
                std::string label;
                if (entry.is_directory()) {
                    label = "[D] " + entry.path().filename().string();
                    if (ImGui::Selectable(label.c_str(), false)) {
                        m_CurrentPath = entry.path();
                    }
                }
                else if (entry.is_regular_file()) {
                    label = entry.path().filename().string();
                    if (ImGui::Selectable(label.c_str(), false)) {
                        m_SelectedFile = entry.path();
                        // In dialog mode, set the result and close the popup.
                        if (m_Mode == Mode::DIALOG) {
                            m_Result = m_SelectedFile.string();
                            m_IsOpen = false;
                            ImGui::CloseCurrentPopup();
                        }
                    }
                }
            }
        }

        Mode m_Mode;
        bool m_IsOpen = true;
        bool m_PopupOpened = false;

        std::filesystem::path m_RootPath;
        std::filesystem::path m_CurrentPath;
        std::filesystem::path m_SelectedFile;
        std::string m_Result;
	};
}
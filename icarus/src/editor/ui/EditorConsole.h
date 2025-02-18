#pragma once
#include "EditorUIComponent.h"

#include <imgui.h>
#include <streambuf>
#include <string>
#include <mutex>
#include <iostream>

namespace Editor
{
	class EditorConsole : public EditorUIComponent, public std::streambuf
	{
	public:
		EditorConsole()
		{
			oldCoutBuffer = std::cout.rdbuf(this);
		}

		virtual int_type overflow(int_type ch) override
		{
			if (ch != EOF)
			{
				std::lock_guard<std::mutex> lock(mutex_);
				consoleOutput.push_back(static_cast<char>(ch));
			}

			return ch;
		}

		virtual int sync() override
		{
			return 0;
		}

		virtual void Render() override
		{
			ImGui::Begin("Console");

			ImGui::BeginChild("ScrollingRegion", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
			{
				std::lock_guard<std::mutex> lock(mutex_);
				ImGui::TextUnformatted(consoleOutput.c_str());
			}

			ImGui::EndChild();
			ImGui::End();
		}

		void ClearConsole()
		{
			std::lock_guard<std::mutex> lock(mutex_);
			consoleOutput.clear();
		}

	private:
		std::string consoleOutput;
		std::mutex mutex_;
		std::streambuf* oldCoutBuffer = nullptr;
	};
}
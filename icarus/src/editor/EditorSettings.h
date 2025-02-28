#pragma once
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <string>
#include <filesystem>

#include "ProjectSettings.h"
#include "Icarus.hpp"

using json = nlohmann::json;

namespace Editor
{
    // EditorSettings
    //
    // Contains information that needs to be saved/loaded between Icarus sessions
    struct EditorSettings
    {
        static EditorSettings s_EditorState;

        int windowWidth;
        int windowHeight;
        bool fullscreen;
        
        ProjectSettings openProject;

        bool saveToFile(const std::string& filename) {
            json j;
            j["window_width"] = windowWidth;
            j["window_height"] = windowHeight;
            j["fullscreen"] = fullscreen;

            std::ofstream file(filename);
            if (file.is_open()) {
                file << j.dump(4);  // Pretty print with 4-space indentation
                file.close();
            }
            else 
            {
                return false;
            }

            return true;
        }

        // Load state from a file
        bool loadFromFile(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open())
            {
                return false;
            }

            json j;
            file >> j;
            file.close();

            windowWidth = j.value("window_width", 1280);
            windowHeight = j.value("window_height", 720);
            fullscreen = j.value("fullscreen", false);

            return true;
        }

        bool OpenProject(std::filesystem::path projectPath)
        {
            std::ifstream file(projectPath);
            if (!file.is_open())
            {
                print("Error Opening Project.");
                return false;
            }

            json j;
            file >> j;
            file.close();

            openProject.name = j.value("name", "null");
            openProject.projectPath = j.value("projectPath", "C:\\");

            print("Project: ", openProject.name, " opened successfully!");
            
            return true;
        }

        void CreateProjectDirectory(const std::string& directory)
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
            Editor::EditorSettings::s_EditorState.OpenProject(directory + "\\" + projectName + ".json");
        }

        void OpenProjectDirectory(const std::string& fileDirectory)
        {
            Editor::EditorSettings::s_EditorState.OpenProject(fileDirectory);
        }
    };
    inline EditorSettings EditorSettings::s_EditorState{};
}

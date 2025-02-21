#pragma once
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <string>
#include <filesystem>

#include "Icarus.hpp"

using json = nlohmann::json;

namespace Editor
{
    // ProjectSettings
    //
    // Holds information for individual game projects.
    struct ProjectSettings
    {
        std::string name;
        std::string projectPath;
    };

    ProjectSettings CreateNewProject(std::string projectName, std::string path)
    {
        ProjectSettings p;
        std::filesystem::path projectDir = std::filesystem::path(path) / projectName;
        p.name = projectName;
        p.projectPath = projectDir.string();

        json j;
        j["name"] = projectName;
        j["path"] = path;

        std::filesystem::path filePath = projectDir / (projectName + ".json");

        std::ofstream file(filePath);

        if (file.is_open()) 
        {
            file << j.dump(4);  // Pretty print with 4-space indentation
            file.close();
            print("Project Saved!");
        }
        else
        {
            print("Error saving project.");
        }

        return p;
    }

    // EditorSettings
    //
    // Contains information that needs to be saved/loaded between Icarus sessions
    struct EditorSettings
    {
        static EditorSettings s_EditorState;

        int windowWidth;
        int windowHeight;
        bool fullscreen;
        
        Editor::ProjectSettings openProject;

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
    };
    inline EditorSettings EditorSettings::s_EditorState{};
}

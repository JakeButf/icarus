#pragma once
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace Editor
{
    // EditorSettings
    //
    // Contains information that needs to be saved/loaded between Icarus sessions
    struct EditorSettings
    {
        int windowWidth;
        int windowHeight;
        bool fullscreen;

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
            if (!file.is_open()) return false;

            json j;
            file >> j;
            file.close();

            windowWidth = j.value("window_width", 1280);
            windowHeight = j.value("window_height", 720);
            fullscreen = j.value("fullscreen", false);

            return true;
        }
    };

    // ProjectSettings
    //
    // Holds information for individual game projects.
    struct ProjectSettings
    {
        std::string name;
        std::string projectPath;
    };

    bool CreateNewProject(std::string projectName, std::string path)
    {
        json j;
        j['name'] = projectName;
        j['path'] = path;

        std::ofstream file(path + projectName);

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
}

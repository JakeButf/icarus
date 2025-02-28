#pragma once
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <string>
#include <filesystem>

#include "Icarus.hpp"

using json = nlohmann::json;

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
#include "scene.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

namespace Turbine {
std::vector<std::string> get_scenes_in_directory(const std::string& path);
void deserialize_scene(const std::string& path, Scene& scene);
}
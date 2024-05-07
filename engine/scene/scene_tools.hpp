#include "scene.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

namespace Turbine {
std::vector<std::string> get_scenes_in_directory(std::string path);
}
#include "scene_tools.hpp"

namespace Turbine {
std::vector<std::string> get_scenes_in_directory(const std::string& path) {
    std::vector<std::string> filenames;
    fs::path p(path);

    // add error checking
    for (const auto& entry : fs::directory_iterator(p)) {
        if (fs::is_regular_file(entry.path())) {
            filenames.push_back(entry.path().filename().string());
        }
    }

    return filenames;
}


}
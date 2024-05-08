#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include "scene/scene.hpp"
#include "components/common.hpp"

namespace Turbine {
class CameraSystem {
public:
    CameraSystem();
    ~CameraSystem();

    auto update(const std::shared_ptr<Scene>& scene) -> void;
    auto apply_mode(const std::shared_ptr<Scene>& scene) -> void;
private:

};
}

#endif
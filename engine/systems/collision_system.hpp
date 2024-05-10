#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "math/vector2.hpp"
#include "scene/scene.hpp"
#include <memory>

namespace Turbine {
class CollisionSystem {
public:
    CollisionSystem();
    ~CollisionSystem();

    auto update(const std::shared_ptr<Scene>& scene) -> void;
};
}

#endif
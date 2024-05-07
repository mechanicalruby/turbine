#ifndef SPRITE_SYSTEM_HPP
#define SPRITE_SYSTEM_HPP

#include "scene/scene.hpp"
#include "components/common.hpp"

#if !PSP
#include "renderer/shader.hpp"
#endif

namespace Turbine {
class SpriteSystem {
public:
    SpriteSystem();
    ~SpriteSystem();

    auto initialize_mesh(SpriteComponent& sprite) -> void;
    auto update(const std::shared_ptr<Scene>& scene) -> void;
private:
#if !PSP
    std::unique_ptr<Shader> sprite_shader;
#endif

};
}

#endif
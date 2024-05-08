#ifndef TURBINE_RUNTIME_HPP
#define TURBINE_RUNTIME_HPP

#include "systems/sprite_system.hpp"
#include <memory>
namespace Turbine {
class Runtime {
public:
    Runtime() = default;

private:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<SpriteSystem> sprite_system;
};
}

#endif
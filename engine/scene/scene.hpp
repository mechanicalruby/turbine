#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <entt/entt.hpp>

#include "components/common.hpp"

namespace Turbine {
class Entity;
class Scene {
public:
    Scene();
    ~Scene();

    void on_update();
    
    Entity create_entity();
    entt::registry& get_registry() {
	    return registry;
    };

    std::string& get_name() {
        return name;
    }
private:
    std::string name = "Default Scene";
    entt::registry registry;
};
}
#endif

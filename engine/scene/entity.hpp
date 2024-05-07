#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <cassert>
#include <entt/entt.hpp>

#include "scene.hpp"

namespace Turbine {
class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);

    template<typename T, typename... Args>
    T& add_component(Args&&... args) {
        // TODO: Assert, check if entity already has this component
	    return scene->get_registry().emplace<T>(entity_handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& get_component() {
        // TODO: Assert, check if component does not exist
        return scene->get_registry().get<T>(entity_handle);
    }

    template<typename T>
    bool has_component() {
	    return scene->get_registry().all_of<T>(entity_handle);
    }

    template<typename T>
    void remove_component() {
        // TODO: Assert, check if component exists
        scene->get_registry().remove<T>(entity_handle);
    }
private:
    entt::entity entity_handle{entt::null};
    // Change this to a std::weak_ptr
    Scene* scene = nullptr;
};
}
#endif

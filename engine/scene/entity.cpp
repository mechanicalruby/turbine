#include "entity.hpp"

namespace Turbine {
Entity::Entity(entt::entity handle, Scene* scene) : entity_handle(handle), scene(scene) { }
}
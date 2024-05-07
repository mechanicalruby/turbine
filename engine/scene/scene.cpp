#include "scene.hpp"
#include "entity.hpp"

namespace Turbine {
Scene::Scene(){

}

Scene::~Scene() {

}

void Scene::on_update() {

}

Entity Scene::create_entity() {
    Entity entity = { registry.create(), this };
    return entity;
}
}

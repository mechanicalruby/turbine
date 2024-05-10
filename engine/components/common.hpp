#ifndef COMMON_COMPONENTS_HPP
#define COMMON_COMPONENTS_HPP

#include <memory>

#include "math/vector2.hpp"
#include "renderer/mesh.hpp"
#include "renderer/texture.hpp"
#include "renderer/camera.hpp"

namespace Turbine {
struct TransformComponent {
    Vector2 position;
    Vector2 scale;
    float rotation;
};

struct SpriteComponent {
    std::unique_ptr<FixedMesh<Vertex, 4, 6>> mesh;
    std::shared_ptr<Texture> texture;
    TransformComponent transform;
    Rectangle region_rect;
    Vector2 offset;
    Vector2 origin;
    unsigned int color;
    bool centered;

    SpriteComponent() : color(0xFFFFFFFF) {}
};

struct CameraComponent {
    Camera camera;
    bool active;
};

/*struct AnimationControllerComponent {
    AnimationController controller;
};*/

}
    
#endif

#ifndef COMMON_COMPONENTS_HPP
#define COMMON_COMPONENTS_HPP

#include <memory>

#include "math/vector2.hpp"
#include "renderer/mesh.hpp"
#include "renderer/texture.hpp"

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
    Rectangle uv;
    Vector2 origin;
};

// struct CameraComponent {
//     OrthographicCamera camera;
//     bool active;
// };
}
    
#endif

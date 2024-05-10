#ifndef SPRITE_SYSTEM_HPP
#define SPRITE_SYSTEM_HPP

#include "renderer/varray.hpp"
#include "renderer/vbuffer.hpp"
#include "scene/scene.hpp"
#include "components/common.hpp"

#if !PSP
#include "renderer/shader.hpp"
#include "renderer/opengl/varray.hpp"
#include "renderer/opengl/vbuffer.hpp"
#endif

namespace Turbine {
class SpriteSystem {
public:
    SpriteSystem();
    ~SpriteSystem();

    auto initialize_mesh(SpriteComponent& sprite) -> void;
    auto update(const std::shared_ptr<Scene>& scene) -> void;
    auto draw(const std::shared_ptr<Scene>& scene) -> void;
private:
#if !PSP
    std::shared_ptr<Shader> sprite_shader;
    std::shared_ptr<OpenGLVertexBuffer> sprite_vbo;
    std::shared_ptr<OpenGLVertexArray> sprite_vao;
    BufferLayout vertex_layout;
#endif
};
}

#endif
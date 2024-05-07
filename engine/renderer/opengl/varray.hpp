#ifndef OPENGL_VERTEX_ARRAY_OBJECT_HPP
#define OPENGL_VERTEX_ARRAY_OBJECT_HPP

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/varray.hpp"

namespace Turbine {
class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) override;
    // virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) override;
private:
    std::uint32_t renderer_id;
    std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
    // std::shared_ptr<IndexBuffer> index_buffer;
};
}
#endif

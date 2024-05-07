#ifndef OPENGL_VERTEX_BUFFER_OBJECT_HPP
#define OPENGL_VERTEX_BUFFER_OBJECT_HPP

#include <iostream>
#include "renderer/vbuffer.hpp"
#include "renderer/mesh.hpp"

namespace Turbine {
// Vertex buffer
class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(const void* vertices, std::size_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual const BufferLayout& get_layout() const override {
        return layout;
    }
    virtual void set_layout(const BufferLayout& l) override {
        layout = l; 
    }
private:
    std::uint32_t renderer_id;
    BufferLayout layout;
};
// Index buffer
class OpenGLIndexBuffer : public IndexBuffer {
public:
    virtual ~OpenGLIndexBuffer() {};

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual std::uint32_t get_count() const = 0;
};
}
#endif

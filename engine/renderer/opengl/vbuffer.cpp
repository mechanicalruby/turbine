#include "renderer/opengl/vbuffer.hpp"
#include "renderer/opengl/varray.hpp"

namespace Turbine {
OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, std::size_t size) {
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void OpenGLVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void OpenGLVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Index buffer
// OpenGLIndexBuffer::OpenGLIndexBuffer(){}
};

#include "renderer/opengl/varray.hpp"

namespace Turbine {
    static GLenum ToBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::UInt:      return GL_UNSIGNED_BYTE;
            case ShaderDataType::UInt2:     return GL_UNSIGNED_BYTE;
            case ShaderDataType::UInt3:     return GL_UNSIGNED_BYTE;
            case ShaderDataType::UInt4:     return GL_UNSIGNED_BYTE;
            case ShaderDataType::UIntColor: return GL_UNSIGNED_BYTE;
            case ShaderDataType::Bool:     return GL_BOOL;
        }
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &renderer_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &renderer_id);
    }

    void OpenGLVertexArray::bind() const {
        glBindVertexArray(renderer_id);
    }

    void OpenGLVertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) {
	// ASSERT, CHECK IF LAYOUT EXISTS in the VBO!!!

	glBindVertexArray(renderer_id);
        vertex_buffer->bind();

        const auto& layout = vertex_buffer->get_layout();

        std::uint32_t index = 0;
        for(const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.get_component_count(),
                ToBaseType(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.get_stride(),
                (const void*)element.offset);
            index++;
        }
        vertex_buffers.push_back(vertex_buffer);
    }

    // void OpenGLVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) {

    // }
};

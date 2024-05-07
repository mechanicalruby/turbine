#ifndef VERTEX_BUFFER_OBJECT_HPP
#define VERTEX_BUFFER_OBJECT_HPP

#include <iostream>
#include <cinttypes>
#include <vector>

namespace Turbine {
enum class ShaderDataType : std::uint8_t {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    UInt,
    UInt2,
    UInt3,
    UInt4,
    UIntColor,
    Bool
};

static std::uint32_t shader_data_type_size(ShaderDataType type) {
    switch(type) {
        case ShaderDataType::Float:     return 4;
        case ShaderDataType::Float2:    return 4 * 2;
        case ShaderDataType::Float3:    return 4 * 3;
        case ShaderDataType::Float4:    return 4 * 4;
        case ShaderDataType::Mat3:      return 4 * 3 * 3;
        case ShaderDataType::Mat4:      return 4 * 4 * 4;
        case ShaderDataType::Int:       return 4;
        case ShaderDataType::Int2:      return 4 * 2;
        case ShaderDataType::Int3:      return 4 * 3;
        case ShaderDataType::Int4:      return 4 * 4;
        case ShaderDataType::UInt:      return 4;
        case ShaderDataType::UInt2:     return 4 * 2;
        case ShaderDataType::UInt3:     return 4 * 3;
        case ShaderDataType::UInt4:     return 4 * 4;
        case ShaderDataType::UIntColor: return 4;
        case ShaderDataType::Bool:      return 1;
    }
    // Assert
    return 0;
}

struct BufferElement {
    std::string name;
    ShaderDataType type;
    std::uint32_t size;
    std::size_t offset;
    bool normalized;

    BufferElement();
    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
        name(name), type(type), size(shader_data_type_size(type)), offset(0), normalized(normalized) {}

    std::uint32_t get_component_count() const {
        switch(type) {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::UInt:      return 1;
            case ShaderDataType::UInt2:     return 2;
            case ShaderDataType::UInt3:     return 3;
            case ShaderDataType::UInt4:     return 4;
            case ShaderDataType::UIntColor: return 4; // Four components for four channels
            case ShaderDataType::Bool:      return 1;
        }
        // Assert
        return 0;
    }
};

class BufferLayout {
public:
    BufferLayout() {}
    BufferLayout(const std::initializer_list<BufferElement> elements) : elements(elements) {
        calculate_offsets_and_stride();
    }

    std::uint32_t get_stride() const { return stride; }
    const std::vector<BufferElement>& get_elements() const { return elements; }

    std::vector<BufferElement>::iterator begin() { return elements.begin(); }
    std::vector<BufferElement>::iterator end() { return elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
private:
    void calculate_offsets_and_stride() {
        std::size_t offset = 0;
        stride = 0;

        for(auto &e : elements) {
            e.offset = offset;
            offset += e.size;
            stride += e.size;
        }
    }

    std::vector<BufferElement> elements;
    std::uint32_t stride = 0;
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() {}
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set_layout(const BufferLayout& layout) = 0;
    virtual const BufferLayout& get_layout() const = 0;
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() {};

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual std::uint32_t get_count() const = 0;
};
}

#endif
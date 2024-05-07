#ifndef VERTEX_ARRAY_OBJECT_HPP
#define VERTEX_ARRAY_OBJECT_HPP

#include <iostream>
#include <memory>

#include "vbuffer.hpp"

namespace Turbine {
class VertexArray {
public:
    virtual ~VertexArray() {};
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
    
};
}
#endif

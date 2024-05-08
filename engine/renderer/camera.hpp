#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"

class Camera {
public:
    Camera() = default;
    const glm::mat4& get_projection() { return projection; }

    struct ProjectionData {
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    };
private:
    glm::mat4 projection, view, mixed;
    float rotation = 0.0f;
};

#endif
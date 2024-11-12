#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace GeckoEngine
{
    class Camera3D
    {
    public:
        void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
        void setPerspectiveProjection(float fovy, float aspect, float near, float far);

        const glm::mat4 &getProjection() const { return projectionMatrix; }

    private:
        glm::mat4 projectionMatrix{1.0f};
    };
} // namespace GeckoEngine

#endif // CAMERA_H
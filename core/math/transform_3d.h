#ifndef GECKO_TRANSFORM_3D_H
#define GECKO_TRANSFORM_3D_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace GeckoEngine
{
    struct Transform3D
    {
        glm::vec3 position{};
        glm::quat rotation{};
        glm::vec3 scale{1.0f, 1.0f, 1.0f};

        glm::mat4 basis() const
        {
            glm::mat4 applyTranslation = glm::translate(glm::mat4(1.0f), position);
            glm::mat4 applyRotation = glm::mat4_cast(rotation);
            glm::mat4 applyScaling = glm::scale(glm::mat4(1.0f), scale);

            return applyTranslation * applyRotation * applyScaling;
        }
    };
} // namespace GeckoEngine

#endif // GECKO_TRANSFORM_3D_H
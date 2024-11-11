#ifndef _OBJECT_H
#define _OBJECT_H

#include "model.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace GeckoEngine
{
    struct Transform3D
    {
        glm::vec3 position{};
        glm::vec3 scale{1.0f, 1.0f, 1.0f};
        glm::vec3 rotation{};

        glm::mat4 mat4()
        {
            const float c3 = glm::cos(rotation.z);
            const float s3 = glm::sin(rotation.z);
            const float c2 = glm::cos(rotation.x);
            const float s2 = glm::sin(rotation.x);
            const float c1 = glm::cos(rotation.y);
            const float s1 = glm::sin(rotation.y);
            return glm::mat4{
                {
                    scale.x * (c1 * c3 + s1 * s2 * s3),
                    scale.x * (c2 * s3),
                    scale.x * (c1 * s2 * s3 - c3 * s1),
                    0.0f,
                },
                {
                    scale.y * (c3 * s1 * s2 - c1 * s3),
                    scale.y * (c2 * c3),
                    scale.y * (c1 * c3 * s2 + s1 * s3),
                    0.0f,
                },
                {
                    scale.z * (c2 * s1),
                    scale.z * (-s2),
                    scale.z * (c1 * c2),
                    0.0f,
                },
                {position.x, position.y, position.z, 1.0f}};
        }
    };

    class Object
    {
    public:
        using id_t = unsigned int;

        static Object createObject()
        {
            static id_t currentId = 0;
            return Object{currentId++};
        }

        Object(const Object &) = delete;
        Object &operator=(const Object &) = delete;
        Object(Object &&) = default;
        Object &operator=(Object &&) = default;

        id_t getId() { return id; }

        std::shared_ptr<Model> model{};
        glm::vec3 color{};
        Transform3D transform{};

    private:
        Object(id_t id) : id{id} {}

        id_t id;
    };
} // namespace GeckoEngine

#endif // _OBJECT_H
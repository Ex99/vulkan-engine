#ifndef _OBJECT_H
#define _OBJECT_H

#include "model.h"

#include <memory>

namespace GeckoEngine
{
    struct Transform2DComponent
    {
        glm::vec2 translation{};
        glm::vec2 scale{1.0f, 1.0f};
        float rotation;

        glm::mat2 basis()
        {
            const float sin = glm::sin(rotation);
            const float cos = glm::cos(rotation);
            glm::mat2 rotationMatrix{{cos, sin}, {-sin, cos}};

            glm::mat2 scaleMatrix{{scale.x, 0.0f}, {0.0f, scale.y}};

            return rotationMatrix * scaleMatrix;
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
        Transform2DComponent transform2D;

    private:
        Object(id_t id) : id{id} {}

        id_t id;
    };
} // namespace GeckoEngine

#endif // _OBJECT_H
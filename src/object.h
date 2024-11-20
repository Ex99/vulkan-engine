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

        glm::mat4 mat4();
        glm::mat3 normalMatrix();
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
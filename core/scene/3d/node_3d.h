#ifndef GECKO_NODE_3D
#define GECKO_NODE_3D

#include "core/math/transform_3d.h"
#include "core/scene/component/component.h"
#include "core/scene/node.h"

#include <vector>

namespace GeckoEngine
{
    class Node3D : public Node
    {
    public:
        Transform3D transform;

    private:
    };
} // namespace GeckoEngine

#endif // GECKO_NODE_3D
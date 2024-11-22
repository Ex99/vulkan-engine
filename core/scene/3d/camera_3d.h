#ifndef GECKO_CAMERA_3D_H
#define GECKO_CAMERA_3D_H

#include "core/scene/3d/node_3d.h"

namespace GeckoEngine
{
    class Camera3D : public Node3D
    {
    public:
        enum ProjectionType
        {
            ORTHOGONAL,
            PERSPECTIVE,
        };

    private:
    };
} // namespace GeckoEngine

#endif // GECKO_CAMERA_3D_H
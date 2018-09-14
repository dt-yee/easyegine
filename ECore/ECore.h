#pragma once
#include "ECommon.h"
#include "EVector.h"
#include <list>

namespace E3D
{
    //plane
    struct EPlane3D
    {
        EVector4D point;    // a point
        EVector4D normal;   //plane normal

        EPlane3D() {};
        EPlane3D(const EVector4D &p, const EVector4D &normal);
        EPlane3D& operator = (const EPlane3D &right);
    };
}
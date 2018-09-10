#pragma once
#include "ECommon.h"

namespace E3D
{
    template <class T>
    const T& Min(const T& a, const T& b) {
        return (a < b) ? a : b;
    }

    template <class T>
    const T& Max(const T& a, const T& b) {
        return (a < b) ? a : b;
    }

    template<typename T>
    const T& Clamp(const T& val, const T& minV, const T& maxV) {
        return Max(Min(maxV, val), minV);
    }

    //matrix translation
    void GetTranslateMatrix44(EMatrix44 &mat, EFloat x, EFloat y, EFloat z);

    //matrix scale
    void GetScaleMatrix44(EMatrix44 &mat, EFloat x, EFloat y, EFloat z);

    //rotate about x-axis, degree
    void GetRotateMatrix44X(EMatrix44 &mat, EFloat degree);

    //rotate about y-axis, degree
    void GetRotateMatrix44Y(EMatrix44 &mat, EFloat degree);

    //rotate about z-axis, degree
    void GetRotateMatrix44Z(EMatrix44 &mat, EFloat degree);

    //rotate about any vector, degree
    void GetRotateMatrix44(EMatrix44 &mat, const EVector4D &normal, EFloat degree);

    //vertex add vector
    void GetVertex4DAddVector4D(const EVertex4D &v, const EVector4D &p, EVertex4D &result);

    //3d vector multiply 4*4 matrix
    void GetVector3DMulMatrix44(const EVector3D& vec, const EMatrix44 &mat, EVector3D &result);

    //4d vector mul 4*4 matrix
    void GetVector4DMulMatrix44(const EVector3D &vec, const EMatrix44 &mat, EVector4D &result);
    
    //point mul 4*4 matrix
    void GetVertex4DMulMatrix44(const EVector4D& vec, const EMatrix44&mat, EVertex4D &result);
}
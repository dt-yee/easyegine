#include "EMath.h"
#include "EVector.h"
#include "EMatrix.h"
#include "ECore.h"

namespace E3D
{
    // translation
    void GetTranslateMatrix44(EMatrix44 &mat, EFloat x, EFloat y, EFloat z)
    {
        mat.m[0][0] = 1, mat.m[0][1] = 0, mat.m[0][2] = 0, mat.m[0][3] = 0;
        mat.m[1][0] = 0, mat.m[1][1] = 1, mat.m[1][2] = 0, mat.m[1][3] = 0;
        mat.m[2][0] = 0, mat.m[2][1] = 0, mat.m[2][2] = 1, mat.m[2][3] = 0;
        mat.m[3][0] = x, mat.m[3][1] = y, mat.m[3][2] = z, mat.m[3][3] = 1;
    }

    //scale
    void GetScaleMatrix44(EMatrix44 &mat, EFloat x, EFloat y, EFloat z)
    {
        mat.m[0][0] = x, mat.m[0][1] = 0, mat.m[0][2] = 0, mat.m[0][3] = 0;
        mat.m[1][0] = 0, mat.m[1][1] = y, mat.m[1][2] = 0, mat.m[1][3] = 0;
        mat.m[2][0] = 0, mat.m[2][1] = 0, mat.m[2][2] = z, mat.m[2][3] = 0;
        mat.m[3][0] = 0, mat.m[3][1] = 0, mat.m[3][2] = 0, mat.m[3][3] = 1;
    }

    //rotate x-axis
    void GetRotateMatrix44X(EMatrix44 &mat, EFloat degree)
    {
        EFloat sinA = sin(Degree_TO_Radian(degree));
        EFloat cosA = cos(Degree_TO_Radian(degree));

        mat.m[0][0] = 1, mat.m[0][1] = 0,     mat.m[0][2] = 0,    mat.m[0][3] = 0;
        mat.m[1][0] = 0, mat.m[1][1] = cosA,  mat.m[1][2] = sinA, mat.m[1][3] = 0;
        mat.m[2][0] = 0, mat.m[2][1] = -sinA, mat.m[2][2] = cosA, mat.m[2][3] = 0;
        mat.m[3][0] = 0, mat.m[3][1] = 0,     mat.m[3][2] = 0,    mat.m[3][3] = 1;
    }

    // rotate y-axis
    void GetRotateMatrix44Y(EMatrix44 &mat, EFloat degree)
    {
        EFloat sinA = sin(Degree_TO_Radian(degree));
        EFloat cosA = cos(Degree_TO_Radian(degree));

        mat.m[0][0] = cosA, mat.m[0][1] = 0, mat.m[0][2] = -sinA, mat.m[0][3] = 0;
        mat.m[1][0] = 0,    mat.m[1][1] = 0, mat.m[1][2] = 0,     mat.m[1][3] = 0;
        mat.m[2][0] = sinA, mat.m[2][1] = 0, mat.m[2][2] = cosA,  mat.m[2][3] = 0;
        mat.m[3][0] = 0,    mat.m[3][1] = 0, mat.m[3][2] = 0,     mat.m[3][3] = 1;
    }

    //rotate z-axis
    void GetRotateMatrix44Z(EMatrix44 &mat, EFloat degree)
    {
        EFloat sinA = sin(Degree_TO_Radian(degree));
        EFloat cosA = cos(Degree_TO_Radian(degree));

        mat.m[0][0] = cosA,  mat.m[0][1] = sinA,  mat.m[0][2] = 0, mat.m[0][3] = 0;
        mat.m[1][0] = -sinA, mat.m[1][1] = cosA,  mat.m[1][2] = 0, mat.m[1][3] = 0;
        mat.m[2][0] = 0,     mat.m[2][1] = 0,     mat.m[2][2] = 1, mat.m[2][3] = 0;
        mat.m[3][0] = 0,     mat.m[3][1] = 0,     mat.m[3][2] = 0, mat.m[3][3] = 1;
    }

    //rotate any vector
    void GetRotateMatrix44(EMatrix44 &mat, const EVector4D &vec, EFloat degree)
    {
        EFloat sinA = sin(Degree_TO_Radian(degree));
        EFloat cosA = cos(Degree_TO_Radian(degree));

        EFloat oneCosA = 1 - cosA;

        mat.m[0][0] = vec.x * vec.x * oneCosA + cosA,   mat.m[0][1] = vec.x * vec.y * oneCosA + vec.x * sinA,
        mat.m[0][2] = vec.x * vec.z * oneCosA - vec.y * sinA, mat.m[0][3] = 0;
        mat.m[1][0] = vec.x * vec.y * oneCosA - vec.z * sinA, mat.m[1][1] = vec.y * oneCosA + cosA, vec.y * vec.z * oneCosA + vec.x * sinA,
        mat.m[1][2] = vec.y * vec.z * oneCosA + vec.x * sinA, mat.m[1][3] = 0;
        mat.m[2][0] = vec.x * vec.z * oneCosA + vec.y * sinA, mat.m[2][1] = vec.y * vec.z * oneCosA - vec.z * sinA,
        mat.m[2][2] = vec.z * vec.z * oneCosA + cosA, mat.m[2][3] = 0;
        mat.m[3][0] = 0, mat.m[3][1] = 0, mat.m[3][2] = 0, mat.m[3][3] = 1;
    }

    void GetVector3DMulMatrix44(const EVector3D &vec, const EMatrix44 &mat, EVector3D &result)
    {
        EFloat x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat[2][0] + mat.m[3][0];
        EFloat y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat[2][1] + mat.m[3][1];
        EFloat z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat[2][2] + mat.m[3][2];

        result.x = x, result.y = y, result.z = z;
    }

    void GetVector4DMulMatrix44(const EVector4D &vec, const EMatrix44 &mat, EVector4D &result)
    {
        EFloat x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat[2][0] + mat.m[3][0];
        EFloat y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat[2][1] + mat.m[3][1];
        EFloat z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat[2][2] + mat.m[3][2];

        result.x = x, result.y = y, result.z = z, result.w = 1;
    }

    void GetVertex4DMulMatrix44(const EVector4D &vec, const EMatrix44 &mat, EVertex4D *result)
    {
        EFloat x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat[2][0] + mat.m[3][0];
        EFloat y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat[2][1] + mat.m[3][1];
        EFloat z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat[2][2] + mat.m[3][2];

        result.x = x, result.y = y, result.z = z, result.w = 1;
    }

    void GetVertex4DAddVector4D(const EVertex4D &v, const EVector4D &vec, EVertex4D &result)
    {
        EFloat x = v.x + vec.x;
        EFloat y = v.y + vec.y;
        EFloat z = v.z + vec.z;

        result.x = x, result.y = y, result.z = z, result.w = 1;
    }
}


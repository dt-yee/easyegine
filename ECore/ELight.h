#pragma once

#include "ECommon.h"
#include "EVector.h"

namespace E3D
{
    enum LIGHT_TYPE
    {
        LIGHT_AMBIENT = 0,
        LIGHT_DIRECTION = 1,
        LIGHT_POINT = 2,
    };

    struct ELight
    {
        EInt id;    //unique id
        EBool lightOn; //enable or not

        LIGHT_TYPE lightTpye;

        EFloat power;   //light strength, default 1.0f
        EFloat shadowFactor;    //back strength, default 0.5f
        EColor ambient;
        EColor diffuse;
        EColor specular;

        EVector4D position;     //world position
        EVector4D direction;    //not  for point light

        EVector4D transPosition;    //camera coordinate position
        EVector4D transDirection;   //camera direction
        
        EFloat kc, kl, kq;  //decay factor    

        EFloat spot_inner;  //spot lamp inner cone distance 
        EFloat spot_outer;  //spot lamp outer cone distance
        EFloat pf;

        ELight(EInt lightId, LIGHT_TYPE type);
    };

    //max light limit
    #define MAX_LIGHTS 8

    //global light manager
    extern std::vector<ELight*> *GLights;

    typedef std::vector<ELight*>::iterator LightItr;
    

    //create a light, success:return id, fail: return -1
    extern EInt CreateLight(LIGHT_TYPE lightType);
    extern EInt GetLightSize();

    //clear all lights
    extern void DestroyAllLights();
}
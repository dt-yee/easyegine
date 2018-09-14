#include "ELight.h"

namespace E3D
{
    ELight::ELight(EInt lightId, LIGHT_TYPE type) : id(lightId), lightOn(true), lightType(type),
        ambient(255, 255, 255), diffuse(255, 255, 255), specular(255, 255, 255),
        position(0, 0, 0), direction(0, 0, 1), kc(1.0f), kl(1.0f), kq(1.0f),
        spot_inner(45.0f), spot_outer(60.0f), power(1.0f), shadowFactor(0.05f) {}

    std::vector<ELight*> *GLights = NULL;

    //create light
    EInt CreateLight(LIGHT_TYPE lightType)
    {
        if (!GLights)
            GLights = new std::vector<ELight*>;
        if ((EInt)GLights->size() > MAX_LIGHTS)
            return -1;
        EInt id = (EInt)GLights->size();
        GLights->push_back(new ELight(id, lightType));

        return id;
    }

    //get a light
    ELight* GetLight(EInt id)
    {
        if (!GLights || (EInt)GLights->size() > MAX_LIGHTS || id < 0 || id > (EInt)GLights->size() - 1)
            return NULL;
        return GLights->at(id);
    }

    //get light size
    EInt GetLightSize()
    {
        return GLights->size();
    }

    //delete all lights
    void DestroyAllLights()
    {
        for (LightItr itr = GLights->begin(); itr != GLights->end(); ++itr) {
            SafeDelete(*itr);
        }
        GLights->clear();
        SafeDelete(GLights);
    }
}
#pragma once
#include "ECommon.h"
#include <map>
#include "EGraphics.h"

namespace E3D
{
    struct EMaterial
    {
        EString     name;
        EColor      ambient; //environment reflection
        EColor      diffuse; //diffuse reflection
        EColor      specular; // specular reflection

        EBitmap *bitmap;

        EMaterial();
        EMaterial();
        
        inline bool useTexture() { return bitmap && bitmap->isValid(); }
        EColor getPixel(EFloat u, EFloat v);
    };

    typedef std::map<EString, EMaterial*>::iterator MaterialIter;
    extern std::map<EString, EMaterial*> *GMaterials;

    extern bool SetMaterial(const EString &name, EMaterial *material);
    extern bool DestoryMaterial(const EString &name);
    extern void DestoryAllMaterials();

    //parse the material script, input the basic material and texture
    //script must have the same name as model
    extern void ParseMaterialScript(const EString &scriptName);
}
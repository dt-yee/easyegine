#include "EMaterial.h"
#include "EUtil.h"
#include <fstream>

namespace E3D
{
    EMaterial::EMaterial() :ambient(0xffffff), diffuse(0xffffff), bitmap(NULL) {}

    EMaterial::~EMaterial()
    {
        SafeDelete(bitmap);
    }

    EColor EMaterial::getPixel(EFloat u, EFloat v)
    {
        static EColor defaultColor(255, 255, 255);
        if (bitmap && bitmap->isValid())
        {
            EInt x = Abs(u - (EInt)u) * bitmap->width;
            EInt y = Abs(v - (EInt)v) * bitmap->height;
            return bitmap->pixels[y*bitmap->width + x];
        }
        else
            return defaultColor;
    }

    std::map<EString, EMaterial*> *GMaterials = NULL;

    static void initMaterial()
    {
        static bool init = false;
        if (!init)
            GMaterials = new std::map<EString, EMaterial*>();
        init = true;
    }

    EMaterial *GetMaterial(const EString &name)
    {
        initMaterial();
        MaterialIter iter = GMaterials->find(name);
        if (iter == GMaterials->end())
            return NULL;
        else
            return iter->second;
    }

    bool SetMaterial(const EString &name, EMaterial *material)
    {
        initMaterial();
        GMaterials->insert(std::make_pair(name, material));
        return true;
    }

    bool DestroyMatrial(const EString &name) 
    {
        initMaterial();

        MaterialIter iter = GMaterials->find(name);
        if (iter != GMaterials->end())
            SafeDelete(iter->second);
        GMaterials->erase(iter);
        return true;
    }

    void DestroyAllMaterials()
    {
        for (MaterialIter iter = GMaterials->begin(); iter != GMaterials->end(); ++iter)
            SafeDelete(iter->second);

        GMaterials->clear();
    }

    void ParseMaterialScript(const EString &scriptName)
    {
        std::ifstream in;

        in.open(GetPath(scriptName).c_str());

        if (in.good())
        {
            EChar line[256];

            while (in.good())
            {
                in.getline(line, 256);
                EString info = Trim(line);
                if (!info.empty()) {
                    EInt brackets = 0;
                    std::size_t index = info.find("material");
                    if (index == 0) {// new material
                        EMaterial *material = new EMaterial();
                        material->name = Trim(info.substr(index + 8));

                        //add to global materials map
                        SetMaterial(material->name, material);

                        in.getline(line, 256);
                        info = Trim(line);
                        EChar temp[64];

                        if (info == "{")
                            brackets++;
                        else if (info == "}")
                            brackets--;
                        else {
                            // env light
                            std::size_t ambientIndex = info.find("ambient");
                            if (ambientIndex == 0) {
                                scanf(info.c_str(), "%s%f%f%f", temp,
                                    &material->ambient.r,
                                    &material->ambient.g,
                                    &material->ambient.b);
                                continue;
                            }

                            //diffuse
                            std::size_t diffuseIndex = info.find("diffuse");
                            if (diffuseIndex == 0)
                            {
                                sscanf(info.c_str(), "%s%f%f%f", temp,
                                    &material->diffuse.r,
                                    &material->diffuse.g,
                                    &material->diffuse.b
                                );
                                continue;
                            }

                            //reflection
                            std::size_t specularIndex = info.find("specular");
                            if (specularIndex == 0) {
                                sscanf(info.c_str(), "%s%f%f%f", temp,
                                    &material->specular.r,
                                    &material->specular.g,
                                    &material->specular.b
                                );
                                continue;
                            }

                            //texture
                            std::size_t textureIndex = info.find("texture "); // texture vs texture unit
                            if (textureIndex == 0) {
                                EChar textureName[64];
                                sscanf(info.c_str(), "%s%s", temp, textureName);
                                material->bitmap = new EBitmap(textureName);
                                continue;
                            }
                        }

                    }
                }
            }
            in.close();
        }
    }


}
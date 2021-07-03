//
// Created by lowIQ on 2021-06-27.
//

#ifndef BOMBERMAN_ASSETMANAGER_H
#define BOMBERMAN_ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager
{
public:
    AssetManager(Manager* man);
    ~AssetManager();

    void AddTexture(std::string id, const char* path);
    SDL_Texture* getTexture(std::string id);
private:
    Manager* m_manager;
    std::map<std::string, SDL_Texture*> m_textures;

};


#endif //BOMBERMAN_ASSETMANAGER_H

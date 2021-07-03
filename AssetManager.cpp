 //
// Created by lowIQ on 2021-06-27.
//
#include "Assetmanager.h"

AssetManager::AssetManager(Manager *man) : m_manager(man)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::AddTexture(std::string id, const char *path)
{
    m_textures.emplace(id, TextureManager::LoadTexture(path));

}

SDL_Texture* AssetManager::getTexture(std::string id)
{
    return m_textures[id];
}

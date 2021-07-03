//
// Created by lowIQ on 2021-06-16.
//

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *textureSheet, int x, int y)
{
    m_objectTexture = TextureManager::LoadTexture(textureSheet);

    m_xPos = x;
    m_yPos = y;
}

GameObject::~GameObject()
{

}


void GameObject::update()
{
    m_xPos++;
    m_yPos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = m_xPos;
    destRect.y = m_yPos;

    destRect.w = srcRect.w ;
    destRect.h = srcRect.h ;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::s_renderer, m_objectTexture, &srcRect, &destRect);
}


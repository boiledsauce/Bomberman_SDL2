//
// Created by lowIQ on 2021-06-16.
//
#include "TextureManager.h"
int TextureManager::curPixelHeight = 32;
int TextureManager::curPixelWidth = 32;
double TextureManager::heightRatio = 1.0f;
double TextureManager::widthRatio = 1.0f;

SDL_Texture* TextureManager::LoadTexture(const char *fileName)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Game::s_renderer,tempSurface);
    SDL_FreeSurface(tempSurface);
    return newTexture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect &src, SDL_Rect &dest, SDL_RendererFlip flip)
{
    if (texture == nullptr)
        return;

    int w;
    int h;
    SDL_GetWindowSize(Game::s_window, &w, &h);
    int wFactor = w / 25;
    int hFactor = h / 25;

    heightRatio = static_cast<double>(hFactor) / curPixelHeight;
    widthRatio = static_cast<double>(wFactor) / curPixelWidth;

    SDL_RenderSetScale(Game::s_renderer, widthRatio, heightRatio);
    //SDL_RenderSetLogicalSize(Game::s_renderer, 800, 800);

    SDL_RenderCopyEx(Game::s_renderer, texture, &src, &dest, 0, 0, flip);
}
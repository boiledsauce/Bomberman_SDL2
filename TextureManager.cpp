//
// Created by lowIQ on 2021-06-16.
//
#include "TextureManager.h"
int TextureManager::curPixelHeight = 32;
int TextureManager::curPixelWidth = 32;
double TextureManager::heightRatio = 1.0f;
double TextureManager::widthRatio = 1.0f;
SDL_Rect TextureManager::FontNullRect = {-1,-1,-1,-1}; // as an indirect nullptr

bool TextureManager::isFontTexture(SDL_Rect& rect)
{
    return TextureManager::FontNullRect.x == rect.x &&
            TextureManager::FontNullRect.y == rect.y &&
            TextureManager::FontNullRect.w == rect.w &&
            TextureManager::FontNullRect.h == rect.h;
}


SDL_Texture* TextureManager::LoadTexture(const char *fileName)
{
    SDL_Surface* tempSurface = IMG_Load(fileName);


    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Game::s_renderer,tempSurface);
    SDL_FreeSurface(tempSurface);
    return newTexture;
}

SDL_Texture* TextureManager::LoadTTF_Texture(std::string fontName, int size, std::string displayText, SDL_Color textCol)
{
    std::string fontDir = "C:/Windows/Fonts/";
    TTF_Font* font = TTF_OpenFont((fontDir+fontName+".ttf").c_str(), size);
    SDL_Surface* fontSurface = TTF_RenderText_Solid(font, displayText.c_str(), textCol);
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(Game::s_renderer, fontSurface);
    SDL_FreeSurface(fontSurface);

    return fontTexture;
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

    SDL_RenderCopyEx(Game::s_renderer, texture, isFontTexture(src) ? nullptr :&src, &dest, 0, 0, flip);
}
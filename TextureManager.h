//
// Created by lowIQ on 2021-06-16.
//

#ifndef BOMBERMAN_TEXTUREMANAGER_H
#define BOMBERMAN_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect &src, SDL_Rect &dest, SDL_RendererFlip flip);
    static int curPixelHeight;
    static int curPixelWidth;
    static double widthRatio;
    static double heightRatio;

};

#endif //BOMBERMAN_TEXTUREMANAGER_H

//
// Created by lowIQ on 2021-06-16.
//

#ifndef BOMBERMAN_TEXTUREMANAGER_H
#define BOMBERMAN_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static SDL_Texture* LoadTTF_Texture(std::string fontName, int size, std::string displayText, SDL_Color textCol);

    static void Draw(SDL_Texture* texture, SDL_Rect &src, SDL_Rect &dest, SDL_RendererFlip flip);
    static SDL_Rect FontNullRect;
    static bool isFontTexture(SDL_Rect &rect);

    static int curPixelHeight;
    static int curPixelWidth;
    static double widthRatio;
    static double heightRatio;

};

#endif //BOMBERMAN_TEXTUREMANAGER_H

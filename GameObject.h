//
// Created by lowIQ on 2021-06-16.
//

#ifndef BOMBERMAN_GAMEOBJECT_H
#define BOMBERMAN_GAMEOBJECT_H
#include "Game.h"

class GameObject {

public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int m_xPos;
    int m_yPos;
    SDL_Texture* m_objectTexture;
    SDL_Rect srcRect, destRect;
};


#endif //BOMBERMAN_GAMEOBJECT_H

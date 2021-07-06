//
// Created by lowIQ on 2021-07-06.
//

#ifndef BOMBERMAN_EXPLOSIONCOMPONENT_H
#define BOMBERMAN_EXPLOSIONCOMPONENT_H
#include "Components.h"
#include "../Game.h"
#include "TileComponent.h"

class ExplosionComponent : public Component
{
public:
    int m_x;
    int m_y;
    int m_damage = 0;
    int m_duration = 1000;

    ExplosionComponent(int x, int y, int damage, int duration)
    {
        m_x = x;
        m_y = y;
        m_damage = damage;
    }

    void init() override
    {
     m_duration += SDL_GetTicks();
     m_entity->addComponent<TransformComponent>(m_x,m_y);
     m_entity->addComponent<SpriteComponent>("Sprites/explosion.png");
    }
    void update() override
    {
        if (m_duration <= SDL_GetTicks())
        {
            TileComponent* tile = Game::s_tiles[std::make_pair(m_x, m_y)];
            m_entity->destroy();
        }
    }

};

#endif //BOMBERMAN_EXPLOSIONCOMPONENT_H

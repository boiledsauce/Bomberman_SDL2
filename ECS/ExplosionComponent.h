//
// Created by lowIQ on 2021-07-06.
//

#ifndef BOMBERMAN_EXPLOSIONCOMPONENT_H
#define BOMBERMAN_EXPLOSIONCOMPONENT_H

#include "ECS.h"
#include "Components.h"
#include "../Game.h"

class ExplosionComponent : public Component
{
public:
    int m_x;
    int m_y;
    int m_damage = 25;
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
     m_entity->addComponent<TransformComponent>(m_x, m_y);
     m_entity->addComponent<SpriteComponent>("Sprites/explosion.png");
    }
    void update() override
    {
        if (m_duration <= SDL_GetTicks())
        {
//            auto &pos = m_entity->getComponent<TransformComponent>().m_position;
//            auto posX = static_cast<int>(pos.x);
//            auto posY = static_cast<int>(pos.y);
//
//            TileComponent* tile = Game::s_tiles[std::make_pair(posX,posY)];

            m_entity->destroy();
        }
    }

};

#endif //BOMBERMAN_EXPLOSIONCOMPONENT_H

//
// Created by lowIQ on 2021-06-27.
//

#ifndef BOMBERMAN_BOMBCOMPONENT_H
#define BOMBERMAN_BOMBCOMPONENT_H

#include "ECS.h"
#include "Components.h"



class BombComponent : public Component
{
public:
    bool m_isExploding = true;
    int m_bombTimer = 3000;
    int m_damage = 100;
    int m_curTime = 0;

    void explode()
    {
        /*int xPos = m_entity->getComponent<TransformComponent>().m_position.x;
        int yPos = m_entity->getComponent<TransformComponent>().m_position.y;*/

 /*       if (m_curTime + 1000 >= SDL_GetTicks())
            Game::ExplodeOnPos(xPos, yPos);*/
    }

    BombComponent(int timer, int damage)
    {
        m_bombTimer = timer * 1000 + SDL_GetTicks();
        m_damage = damage;
    }

    ~BombComponent()
    {}

    void init() override
    {
        if ( m_entity->hasComponent<TransformComponent>() )
        {
            std::cout << "yep it has" << std::endl;
        }
        else
        {

            std::cout << "nop it doesnt" << std::endl;
        }

        m_entity->addComponent<SpriteComponent>("Sprites/bomb.png");
        m_entity->addComponent<ColliderComponent>("bomb");
        m_entity->addGroup(groupColliders);
        m_entity->addGroup(groupBombs);

    }

    void update() override
    {
        m_curTime = SDL_GetTicks();

        if (m_curTime > m_bombTimer+m_curTime)
            explode();

    }
};

#endif //BOMBERMAN_BOMBCOMPONENT_H

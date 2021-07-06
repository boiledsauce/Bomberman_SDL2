//
// Created by lowIQ on 2021-07-05.
//

#ifndef BOMBERMAN_BLOCKCOMPONENT_H
#define BOMBERMAN_BLOCKCOMPONENT_H

#include "Components.h"
#include "ColliderComponent.h"

enum reward {SPEED_PLAYER, DAMAGE, RADIUS, SPEED_BOMB, EXTRA_BOMB};

class BlockComponent : public Component
{
public:
    int m_health = 100;
    reward m_reward;
    int m_x;
    int m_y;

    BlockComponent(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    void init() override
    {
        std::cout << "hello";
        m_entity->addComponent<TransformComponent>(m_x, m_y);
        m_entity->addComponent<SpriteComponent>("Sprites/block.png");
        m_entity->addComponent<ColliderComponent>("block");

        //m_entity->addGroup(groupColliders);
    }

    void update() override
    {
    }

    void draw() override
    {

    }


};

#endif //BOMBERMAN_BLOCKCOMPONENT_H

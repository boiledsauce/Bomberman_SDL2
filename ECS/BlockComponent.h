//
// Created by lowIQ on 2021-07-05.
//

#ifndef BOMBERMAN_BLOCKCOMPONENT_H
#define BOMBERMAN_BLOCKCOMPONENT_H

#include "Components.h"
#include "ColliderComponent.h"


class BlockComponent : public Component
{
public:
    int m_health = 100;
    int m_x;
    int m_y;

    BlockComponent(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    void init() override
    {
        m_entity->addComponent<TransformComponent>(m_x, m_y);
        m_entity->addComponent<SpriteComponent>("Sprites/block.png");
        //m_entity->addGroup(groupColliders);
    }


};

#endif //BOMBERMAN_BLOCKCOMPONENT_H

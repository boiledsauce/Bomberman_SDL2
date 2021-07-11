//
// Created by lowIQ on 2021-06-21.
//

#ifndef BOMBERMAN_COLLIDERCOMPONENT_H
#define BOMBERMAN_COLLIDERCOMPONENT_H

#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:

    SDL_Rect collider;
    std::string m_tag;
    TransformComponent* m_transform;

    ColliderComponent(std::string tag)
    {
        m_tag = tag;
    }


    void init() override
    {
        if ( ! m_entity->hasComponent<TransformComponent>() )
        {
            m_entity->addComponent<TransformComponent>();
        }
        m_transform = &m_entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        collider.x = static_cast<int>(m_transform->m_position.x);
        collider.y = static_cast<int>(m_transform->m_position.y);
        collider.w = m_transform->m_width * m_transform->m_scale;
        collider.h = m_transform->m_height * m_transform->m_scale;
    }


};

#endif //BOMBERMAN_COLLIDERCOMPONENT_H

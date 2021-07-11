//
// Created by lowIQ on 2021-06-18.
//

#ifndef BOMBERMAN_TRANSFORMCOMPONENT_H
#define BOMBERMAN_TRANSFORMCOMPONENT_H
#include "Components.h"
#include "../Vector2D.h"
#include "../Constants.h"

constexpr int DEFAULT_VELOCITY = 3;

class TransformComponent : public Component
{
public:
    Vector2D m_position;
    Vector2D m_velocity;

    double m_speed = DEFAULT_VELOCITY;
    int m_height = SPRITE_SIZE;
    int m_width = SPRITE_SIZE;
    int m_scale = SPRITE_SCALE_FACTOR;



    TransformComponent()
    {
        m_position.Zero();
    }

    TransformComponent(int scl)
    {
        m_position.Zero();
        m_scale = scl;
    }

    TransformComponent(float x, float y)
    {
      m_position.x = x;
      m_position.y = y;
    }

    TransformComponent(float x, float y, int h, int w, int scl)
    {
        m_position.x = x;
        m_position.y = y;
        m_height = h;
        m_width = w;
        m_scale = scl;
    }

    void init() override
    {
       m_velocity.Zero();
    }
    void update() override
    {
        m_position.x += m_velocity.x * m_speed;
        m_position.y += m_velocity.y * m_speed;
    }

};


#endif //BOMBERMAN_TRANSFORMCOMPONENT_H

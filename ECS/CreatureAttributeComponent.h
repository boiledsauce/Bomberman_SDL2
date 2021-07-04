//
// Created by lowIQ on 2021-07-02.
//

#ifndef BOMBERMAN_CREATUREATTRIBUTECOMPONENT_H
#define BOMBERMAN_CREATUREATTRIBUTECOMPONENT_H
#include "Components.h"

class CreatureAttributeComponent : public Component
{
public:
    int m_health = 100;
    int m_mana = 100;
    int m_bombAmount = 3;
    int m_bombTimer = 5;
    int m_explosionRadiusX = 3;
    int m_explosionRadiusY = 3;
    int m_explosionDamage = 100;

    CreatureAttributeComponent()
    {}

    CreatureAttributeComponent(int h, int m, int bA, int bT, int eRx, int eRy, int eD):
    m_health(h), m_mana(m), m_bombAmount(bA), m_bombTimer(bT),
    m_explosionRadiusX(eRx), m_explosionRadiusY(eRy), m_explosionDamage(eD)
    {}

    void update() override
    {
        if (m_health <= 0)
        {
            std::cout << "Player died: " << std::endl;
            m_entity->destroy();
        }
    }
};

#endif //BOMBERMAN_CREATUREATTRIBUTECOMPONENT_H

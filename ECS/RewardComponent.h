//
// Created by lowIQ on 2021-07-10.
//

#ifndef BOMBERMAN_REWARDCOMPONENT_H
#define BOMBERMAN_REWARDCOMPONENT_H
#include "Components.h"
#include "SDL.h"
#include "SpriteComponent.h"
#include "RandomNumber.h"

enum reward : int {NO_REWARD, SPEED_PLAYER, DAMAGE, RADIUS, SPEED_BOMB, EXTRA_BOMB, END_OF_ENUM_REWARD};

class RewardComponent : public Component
{
protected:
    std::string spritepath(int powerUp)
    {
        switch(powerUp)
        {
            case SPEED_PLAYER:
                return "speed.png";

            case RADIUS:
                return "radius.png";

            case EXTRA_BOMB:
                return "bomb.png";

            case SPEED_BOMB:
                return "bombtimer.png";

                default:
                    return "";
        }
    }

public:
    bool reward_taken = false;
    int m_powerUp;
    int m_x;
    int m_y;
    TransformComponent* m_transform = nullptr;

    int retBonus()
    {
        if (m_powerUp == SPEED_PLAYER)
        {
            return 2;
        }
        if (m_powerUp == DAMAGE)
        {
            return 20;
        }
        if (m_powerUp == EXTRA_BOMB)
        {
            return 1;
        }
        if (m_powerUp == SPEED_BOMB)
        {
            return -1;
        }

        return 0;
    }

    RewardComponent() = default;
    RewardComponent(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    void init() override
    {
        m_powerUp = RandomNumber::interval(0,END_OF_ENUM_REWARD);
        std::cout << "REWARD:" << m_powerUp << std::endl;
        m_transform = &m_entity->addComponent<TransformComponent>(m_x, m_y);
        m_entity->addComponent<SpriteComponent>( ("Sprites/powerups/"+spritepath(m_powerUp)).c_str());
    }

    void update() override
    {
        if (reward_taken)
            m_entity->destroy();
    }

};



#endif //BOMBERMAN_REWARDCOMPONENT_H
